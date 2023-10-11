#include <iostream>
#include <string>

class Player
{
private:
    std::string playerName;
    char pieceType; // Symbol representing the player on the board

public:
    Player(const std::string &name, char piece) : playerName(name), pieceType(piece) {}

    const std::string &getPlayerName() const
    {
        return playerName;
    }

    char getPieceType() const
    {
        return pieceType;
    }
};

class Board
{
private:
    char board[3][3];

public:
    Board()
    {
        reset();
    }

    void reset()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
    }

    void display() const
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                std::cout << board[i][j];
                if (j < 2)
                    std::cout << '|';
            }
            std::cout << '\n';
            if (i < 2)
                std::cout << "-----\n";
        }
    }

    bool isCellEmpty(int row, int col) const
    {
        return board[row][col] == ' ';
    }

    bool placeSymbol(int row, int col, char symbol)
    {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || !isCellEmpty(row, col))
            return false;

        board[row][col] = symbol;
        return true;
    }

    char getSymbol(int row, int col) const
    {
        return board[row][col];
    }

    // Check for a win
    bool checkWin(char symbol) const
    {
        // Check rows
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
                return true;
        }

        // Check columns
        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
                return true;
        }

        // Check diagonals
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
            return true;

        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
            return true;

        return false;
    }
};

class Game
{
private:
    static Game *instance;
    Board board;
    Player playerX;
    Player playerO;
    Player *currentPlayer;

    Game(const std::string &playerNameX, const std::string &playerNameO)
        : playerX(playerNameX, 'X'), playerO(playerNameO, 'O'), currentPlayer(&playerX) {}

public:
    static Game *getInstance(const std::string &playerNameX, const std::string &playerNameO)
    {
        if (!instance)
            instance = new Game(playerNameX, playerNameO);
        return instance;
    }

    void reset()
    {
        board.reset();
        currentPlayer = &playerX;
    }

    void switchPlayer()
    {
        currentPlayer = (currentPlayer == &playerX) ? &playerO : &playerX;
    }

    Player *getCurrentPlayer() const
    {
        return currentPlayer;
    }

    Board *getBoard()
    {
        return &board;
    }

    const std::string &getCurrentPlayerName() const
    {
        return currentPlayer->getPlayerName();
    }

    char getCurrentPlayerPieceType() const
    {
        return currentPlayer->getPieceType();
    }

    static void destroyInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }
};

Game *Game::instance = nullptr;

int main()
{
    std::string playerNameX, playerNameO;
    std::cout << "Enter name for Player X: ";
    std::cin >> playerNameX;
    std::cout << "Enter name for Player O: ";
    std::cin >> playerNameO;

    Game *game = Game::getInstance(playerNameX, playerNameO);
    game->reset();

    std::cout << "Tic Tac Toe Game\n";
    std::cout << "Player X: " << playerNameX << ", Player O: " << playerNameO << "\n\n";

    while (true)
    {
        Board *board = game->getBoard();
        board->display();

        std::cout << "\nPlayer " << game->getCurrentPlayerName() << " (" << game->getCurrentPlayerPieceType() << "), enter your move (row[0-2] col[0-2]): ";

        int row, col;
        std::cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (!board->placeSymbol(row, col, game->getCurrentPlayerPieceType()))
        {
            std::cout << "Cell already taken. Please try again.\n";
            continue;
        }

        if (board->checkWin(game->getCurrentPlayerPieceType()))
        {
            board->display();
            std::cout << "Player " << game->getCurrentPlayerName() << " wins!\n";
            break;
        }

        // Check for a draw (all cells filled)
        bool draw = true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board->getSymbol(i, j) == ' ')
                    draw = false;
            }
        }
        if (draw)
        {
            board->display();
            std::cout << "It's a draw!\n";
            break;
        }

        game->switchPlayer();
    }

    Game::destroyInstance();
    return 0;
}