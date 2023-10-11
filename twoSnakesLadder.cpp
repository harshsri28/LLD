#include <iostream>
#include <cstdlib>
#include <ctime>

class Player {
private:
    std::string name;
    int position;

public:
    Player(const std::string& playerName) : name(playerName), position(0) {}

    const std::string& getName() const {
        return name;
    }

    int getPosition() const {
        return position;
    }

    void setPosition(int newPosition) {
        position = newPosition;
    }
};

class Dice {
public:
    int roll() const {
        return rand() % 6 + 1;  // Roll a 6-sided die
    }
};

class Board {
private:
    int boardSize;
    int* snakeLadderPositions;  // Array to store snake and ladder positions

public:
    Board(int size) : boardSize(size) {
        snakeLadderPositions = new int[size];
        for (int i = 0; i < size; ++i)
            snakeLadderPositions[i] = 0;  // Initialize all positions to 0 (no snakes or ladders)
    }

    ~Board() {
        delete[] snakeLadderPositions;
    }

    void setSnakeLadderPosition(int position, int target) {
        snakeLadderPositions[position] = target;
    }

    int getNextPosition(int currentPosition) const {
        return currentPosition + snakeLadderPositions[currentPosition];
    }

    bool isWinningPosition(int position) const {
        return position == boardSize - 1;
    }
};

class Game {
private:
    Board board;
    Player players[2];
    Dice dice;

public:
    Game(int boardSize, const std::string& player1Name, const std::string& player2Name)
        : board(boardSize), players{Player(player1Name), Player(player2Name)} {
        // Set up snakes and ladders positions
        board.setSnakeLadderPosition(3, -3);
        board.setSnakeLadderPosition(11, -6);
        board.setSnakeLadderPosition(17, -10);
        board.setSnakeLadderPosition(19, -9);
        board.setSnakeLadderPosition(27, -15);
        board.setSnakeLadderPosition(21, 5);
        board.setSnakeLadderPosition(5, 3);
        board.setSnakeLadderPosition(7, 7);
        board.setSnakeLadderPosition(9, 6);
        board.setSnakeLadderPosition(25, 8);
    }

    void play() {
        srand(time(0));  // Seed for random number generation

        while (true) {
            for (int i = 0; i < 2; ++i) {
                int roll = dice.roll();
                std::cout << players[i].getName() << " rolled a " << roll << ". ";
                int newPosition = players[i].getPosition() + roll;

                if (newPosition < boardSize) {
                    newPosition = board.getNextPosition(newPosition);
                    players[i].setPosition(newPosition);
                    std::cout << players[i].getName() << " moved to position " << newPosition << ". ";

                    if (board.isWinningPosition(newPosition)) {
                        std::cout << players[i].getName() << " wins!\n";
                        return;
                    }
                }

                std::cout << std::endl;
            }
        }
    }
};

int main() {
    Game game(30, "Player 1", "Player 2");
    game.play();

    return 0;
}
