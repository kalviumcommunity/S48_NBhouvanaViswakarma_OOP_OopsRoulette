#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class RouletteWheel {
private:
    int currentNumber;
    static int totalSpins;

public:
    RouletteWheel() {
        srand(static_cast<unsigned>(time(0)));
        currentNumber = 0;
        cout << "RouletteWheel created with default constructor." << endl;
    }

    ~RouletteWheel() {
        cout << "RouletteWheel destroyed." << endl;
    }

    void spinWheel() {
        currentNumber = rand() % 37;
        cout << "The wheel spins and lands on: " << currentNumber << endl;
        totalSpins++;
    }

    int getCurrentNumber() const {
        return currentNumber;
    }

    static int getTotalSpins() {
        return totalSpins;
    }
};

int RouletteWheel::totalSpins = 0;

class Player {
private:
    int balance;
    static int totalPlayers;

public:
    Player() {
        balance = 1000;  // Default balance
        totalPlayers++;
        cout << "Player created with default constructor. Initial balance: $" << balance << endl;
    }

    Player(int initialBalance) : balance(initialBalance) {
        totalPlayers++;
        cout << "Player created with parameterized constructor. Initial balance: $" << balance << endl;
    }

    ~Player() {
        cout << "Player destroyed. Final balance: $" << balance << endl;
    }

    int getBalance() const {
        return balance;
    }

    void setBalance(int newBalance) {
        balance = newBalance;
    }

    void placeBet(int betAmount, int number, RouletteWheel& wheel) {
        if (betAmount > balance) {
            cout << "Insufficient balance." << endl;
            return;
        }

        wheel.spinWheel();
        if (wheel.getCurrentNumber() == number) {
            int winnings = betAmount * 35;
            setBalance(balance + winnings);
            cout << "You win! Your new balance is: $" << getBalance() << endl;
        } else {
            setBalance(balance - betAmount);
            cout << "You lose! Your new balance is: $" << getBalance() << endl;
        }
    }

    static int getTotalPlayers() {
        return totalPlayers;
    }

    static void displayGameStats() {
        cout << "==== Game Statistics ====" << endl;
        cout << "Total Players: " << getTotalPlayers() << endl;
        cout << "Total Spins: " << RouletteWheel::getTotalSpins() << endl;
        cout << "=========================" << endl;
    }
};

int Player::totalPlayers = 0;

int main() {
    RouletteWheel* wheel = new RouletteWheel();

    Player* player1 = new Player();             // default constructor
    Player* player2 = new Player(1500);         // parameterized constructor

    player1->placeBet(100, 17, *wheel);
    player2->placeBet(200, 25, *wheel);

    cout << "Player 1 Final Balance: $" << player1->getBalance() << endl;
    cout << "Player 2 Final Balance: $" << player2->getBalance() << endl;

    Player::displayGameStats();

    delete wheel;
    delete player1;
    delete player2;

    return 0;
}
