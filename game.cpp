#include <iostream>
#include <vector>

using namespace std;

class Player {
public:
    string name;
    char symbol;

    Player(string name, char symbol) {
        this->name = name;
        this->symbol = symbol;
    }
};

class Board {
public:
    vector<  vector<char > > grid;

    Board() : grid(3, vector<char>(3, ' ')) {}

    void printBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << grid[i][j];
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "-----" << endl;
        }
    }

    bool isValidMove(int row, int col) {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ';
    }

    void makeMove(int row, int col, char symbol) {
        if (isValidMove(row, col)) {
            grid[row][col] = symbol;
        }
    }

    bool checkRowWin(char symbol) {
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) {
                return true;
            }
        }
        return false;
    }

    bool checkColWin(char symbol) {
        for (int j = 0; j < 3; j++) {
            if (grid[0][j] == symbol && grid[1][j] == symbol && grid[2][j] == symbol) {
                return true;
            }
        }
        return false;
    }

    bool checkDiagonalWin(char symbol) {
        return (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
               (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol);
    }

    bool checkWin(char symbol) {
        return checkRowWin(symbol) || checkColWin(symbol) || checkDiagonalWin(symbol);
    }

    bool isFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

class Game {
private:
    Player playerX, playerO;
    Board board;
    Player* currentPlayer;

public:
    Game(Player playerX, Player playerO)
        : playerX(playerX), playerO(playerO), currentPlayer(&this->playerX) {}

    void switchTurn() {
        currentPlayer = (currentPlayer == &playerX) ? &playerO : &playerX;
    }

    void startGame() {
        while (true) {
            board.printBoard();
            cout << currentPlayer->name << "'s turn (symbol: " << currentPlayer->symbol << ")" << endl;

            int start;
            cout << "Enter 3 to start or 4 to exit: ";
            cin >> start;

            if (start == 4) {
                break; // Exit the game
            } else if (start != 3) {
                cout << "Invalid input. Please enter either 3 to start or 4 to exit." << endl;
                continue; // Prompt again
            }

            int row, col;

            // Input for row
            cout << "Enter row (0,1,2): ";
            cin >> row;

            // Validate row input
            while (row < 0 || row > 2) {
                cout << "Invalid number. Please enter row (0,1,2): ";
                cin >> row;
            }

            // Input for column
            cout << "Enter col (0,1,2): ";
            cin >> col;

            // Validate column input
            while (col < 0 || col > 2) {
                cout << "Invalid number. Please enter col (0,1,2): ";
                cin >> col;
            }

            if (board.isValidMove(row, col)) {
                board.makeMove(row, col, currentPlayer->symbol);

                if (board.checkWin(currentPlayer->symbol)) {
                    board.printBoard();
                    cout << currentPlayer->name << " wins!" << endl;
                    break;
                }

                if (board.isFull()) {
                    board.printBoard();
                    cout << "It's a draw!" << endl;
                    break;
                }

                switchTurn();
            } else { 
                cout << "It's an invalid move, please try again." << endl;
            }
        }
    }
};

int main() {
    Player playerX("Player X", 'X');
    Player playerO("Player O", 'O');
    Game game(playerX, playerO);
    game.startGame();

    return 0;
}