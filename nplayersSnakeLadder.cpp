#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

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
    std::vector<Player> players;
    Dice dice;

public:
    Game(int boardSize, int numPlayers, const std::vector<std::string>& playerNames)
        : board(boardSize) {
        for (int i = 0; i < numPlayers; ++i) {
            players.emplace_back(playerNames[i]);
        }

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
            for (int i = 0; i < players.size(); ++i) {
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
    int boardSize = 30;
    int numPlayers;

    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;

    std::vector<std::string> playerNames(numPlayers);
    for (int i = 0; i < numPlayers; ++i) {
        std::cout << "Enter name for Player " << i + 1 << ": ";
        std::cin >> playerNames[i];
    }

    Game game(boardSize, numPlayers, playerNames);
    game.play();

    return 0;
}
