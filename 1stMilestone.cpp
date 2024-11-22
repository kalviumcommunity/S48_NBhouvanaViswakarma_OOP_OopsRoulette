#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
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

// Abstract Betting Strategy Interface (OCP, Strategy Pattern)
class BettingStrategy {
public:
    virtual int calculateBet(int baseBet) const = 0;
};

// Aggressive Strategy: Bet is doubled each time
class AggressiveStrategy : public BettingStrategy {
public:
    int calculateBet(int baseBet) const override {
        return baseBet * 2;
    }
};

// Conservative Strategy: Bet is reduced to half each time
class ConservativeStrategy : public BettingStrategy {
public:
    int calculateBet(int baseBet) const override {
        return baseBet / 2;
    }
};

// Base Player class to be extended for different types of players
class Player {
protected:
    int balance;
    const BettingStrategy* strategy;

public:
    Player(int initialBalance, const BettingStrategy* strat) : balance(initialBalance), strategy(strat) {
        GameStats::incrementPlayers();
    }

    virtual ~Player() {}

    int getBalance() const {
        return balance;
    }

    void setBalance(int newBalance) {
        balance = newBalance;
    }

    virtual void placeBet(int baseBetAmount, int number, IWheel& wheel) = 0;
};

// VIPPlayer inherits Player and Rewards to provide bonus features (OCP, ISP)
class VIPPlayer : public Player, public Rewards {
private:
    int rewardPoints;

public:
    VIPPlayer(int initialBalance, const BettingStrategy* strat) 
        : Player(initialBalance, strat), rewardPoints(0) {}

    void placeBet(int baseBetAmount, int number, IWheel& wheel) override {
        int betAmount = strategy->calculateBet(baseBetAmount);
        if (betAmount > balance) {
            cout << "Insufficient balance." << endl;
            return;
        }

        wheel.spin();
        if (wheel.getCurrentNumber() == number) {
            int winnings = betAmount * 35;
            setBalance(balance + winnings);
            rewardPoints += 100;  // Earn reward points on win
            cout << "VIP win! New balance: $" << getBalance() << ", Reward Points: " << rewardPoints << endl;
        } else {
            setBalance(balance - betAmount);
            cout << "You lose! New balance: $" << getBalance() << endl;
        }
    }

    void earnRewards() override {
        cout << "VIP Player earns extra rewards after every bet!" << endl;
    }

    void redeemPointsForBalance() {
        if (rewardPoints >= 500) {
            balance += 100;
            rewardPoints -= 500;
            cout << "Redeemed 500 points for $100! New balance: $" << balance << ", Points left: " << rewardPoints << endl;
        } else {
            cout << "Not enough points to redeem." << endl;
        }
    }
};

// RegularPlayer class extending Player, no special rewards (OCP)
class RegularPlayer : public Player {
public:
    RegularPlayer(int initialBalance, const BettingStrategy* strat) : Player(initialBalance, strat) {}

    void placeBet(int baseBetAmount, int number, IWheel& wheel) override {
        int betAmount = strategy->calculateBet(baseBetAmount);
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

    // Betting strategies
    BettingStrategy* aggressive = new AggressiveStrategy();
    BettingStrategy* conservative = new ConservativeStrategy();

    // Players with different strategies
    Player* player1 = new RegularPlayer(1000, conservative);
    VIPPlayer* vipPlayer = new VIPPlayer(1500, aggressive);

    player1->placeBet(50, 17, *wheel);
    vipPlayer->placeBet(200, 5, *wheel);

    vipPlayer->earnRewards();
    vipPlayer->redeemPointsForBalance();
    GameStats::displayStats();

    delete wheel;
    delete aggressive;
    delete conservative;
    delete player1;
    delete vipPlayer;

    return 0;
}
