#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class RouletteWheel {
private:
    int currentNumber;         // Private: internal state
    static int totalSpins;     // Private: shared by all instances

public:
    RouletteWheel() {          // Public: constructor
        srand(static_cast<unsigned>(time(0)));
        currentNumber = 0;
    }

    void spinWheel() {         // Public: action that spins the wheel
        currentNumber = rand() % 37;
        cout << "The wheel spins and lands on: " << currentNumber << endl;
        totalSpins++;        
    }

    int getCurrentNumber() const {  // Public getter for current number
        return currentNumber;       // Allows access to the current number without modifying it
    }

    static int getTotalSpins() {    // Public static method to get the total spins
        return totalSpins;
    }
};

int RouletteWheel::totalSpins = 0; 

class Player {
private:
    int balance;                // Private: player's balance
    static int totalPlayers;    // Private: shared across all players

public:
    Player(int initialBalance) : balance(initialBalance) {
        totalPlayers++;
    }

    int getBalance() const {    // Public getter for balance
        return balance;       
    }

    void setBalance(int newBalance) {   // Public setter for balance
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

    static int getTotalPlayers() {  // Public static method
        return totalPlayers;
    }

    static void displayGameStats() {  // Public static method
        cout << "==== Game Statistics ====" << endl;
        cout << "Total Players: " << getTotalPlayers() << endl;
        cout << "Total Spins: " << RouletteWheel::getTotalSpins() << endl;
        cout << "=========================" << endl;
    }
};

int Player::totalPlayers = 0; 

int main() {
    RouletteWheel* wheel = new RouletteWheel();

    Player* player1 = new Player(1000);
    Player* player2 = new Player(1200);

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
