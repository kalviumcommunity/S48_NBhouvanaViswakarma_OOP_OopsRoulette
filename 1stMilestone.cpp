#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Abstract class for Rewards functionality
class Rewards {
public:
    virtual void earnRewards() = 0;
};

// Interface for wheel spinning functionality
class IWheel {
public:
    virtual void spin() = 0;
    virtual int getCurrentNumber() const = 0;
};

// Separate GameStats class to handle all statistics (SRP)
class GameStats {
private:
    static int totalSpins;
    static int totalPlayers;

public:
    static void incrementSpins() {
        totalSpins++;
    }

    static void incrementPlayers() {
        totalPlayers++;
    }

    static void displayStats() {
        cout << "==== Game Statistics ====" << endl;
        cout << "Total Players: " << totalPlayers << endl;
        cout << "Total Spins: " << totalSpins << endl;
        cout << "=========================" << endl;
    }
};

int GameStats::totalSpins = 0;
int GameStats::totalPlayers = 0;

// RouletteWheel class that implements IWheel for SRP and DIP compliance
class RouletteWheel : public IWheel {
private:
    int currentNumber;

public:
    RouletteWheel() {
        srand(static_cast<unsigned>(time(0)));
        currentNumber = 0;
    }

    void spin() override {
        currentNumber = rand() % 37;
        GameStats::incrementSpins();
    }

    int getCurrentNumber() const override {
        return currentNumber;
    }
};

// Base Player class to be extended for different types of players
class Player {
protected:
    int balance;

public:
    Player(int initialBalance = 1000) : balance(initialBalance) {
        GameStats::incrementPlayers();
    }

    virtual ~Player() {}

    int getBalance() const {
        return balance;
    }

    void setBalance(int newBalance) {
        balance = newBalance;
    }

    virtual void placeBet(int betAmount, int number, IWheel& wheel) = 0;
};

// VIPPlayer inherits Player and Rewards to provide bonus features (OCP, ISP)
class VIPPlayer : public Player, public Rewards {
private:
    int bonusBalance;

public:
    VIPPlayer(int initialBalance = 1500) : Player(initialBalance), bonusBalance(500) {}

    void placeBet(int betAmount, int number, IWheel& wheel) override {
        if (betAmount > balance) {
            cout << "Insufficient balance." << endl;
            return;
        }

        wheel.spin();
        if (wheel.getCurrentNumber() == number) {
            int winnings = betAmount * 35 + bonusBalance;
            setBalance(balance + winnings);
            cout << "VIP win! You earned a bonus. New balance: $" << getBalance() << endl;
        } else {
            setBalance(balance - betAmount);
            cout << "You lose! New balance: $" << getBalance() << endl;
        }
    }

    void earnRewards() override {
        cout << "VIP Player earns extra rewards after every bet!" << endl;
    }
};

// RegularPlayer class extending Player, no special rewards (OCP)
class RegularPlayer : public Player {
public:
    RegularPlayer(int initialBalance = 1000) : Player(initialBalance) {}

    void placeBet(int betAmount, int number, IWheel& wheel) override {
        if (betAmount > balance) {
            cout << "Insufficient balance." << endl;
            return;
        }

        wheel.spin();
        if (wheel.getCurrentNumber() == number) {
            int winnings = betAmount * 35;
            setBalance(balance + winnings);
            cout << "You win! New balance: $" << getBalance() << endl;
        } else {
            setBalance(balance - betAmount);
            cout << "You lose! New balance: $" << getBalance() << endl;
        }
    }
};

int main() {
    IWheel* wheel = new RouletteWheel();

    Player* player1 = new RegularPlayer(1000);
    VIPPlayer* vipPlayer = new VIPPlayer(1500);

    player1->placeBet(100, 17, *wheel);
    vipPlayer->placeBet(200, 5, *wheel);

    cout << "Player 1 Final Balance: $" << player1->getBalance() << endl;
    cout << "VIP Player Final Balance: $" << vipPlayer->getBalance() << endl;

    vipPlayer->earnRewards();
    GameStats::displayStats();

    delete wheel;
    delete player1;
    delete vipPlayer;

    return 0;
}
