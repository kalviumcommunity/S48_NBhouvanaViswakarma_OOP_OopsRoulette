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
    }

    void spinWheel() {
        currentNumber = rand() % 37;
        cout << "The wheel spins and lands on: " << currentNumber << endl;
        totalSpins++; 
    }

    int getNumber() const {
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
    Player(int initialBalance) : balance(initialBalance) {
        totalPlayers++; 
    }

    void placeBet(int betAmount, int number, RouletteWheel& wheel) {
        if (betAmount > balance) {
            cout << "Insufficient balance." << endl;
            return;
        }

        wheel.spinWheel();
        if (wheel.getNumber() == number) {
            int winnings = betAmount * 35;
            balance += winnings;
            cout << "You win! Your new balance is: $" << balance << endl;
        } else {
            balance -= betAmount;
            cout << "You lose! Your new balance is: $" << balance << endl;
        }
    }

    int getBalance() const {
        return balance;
    }

    static int getTotalPlayers() {
        return totalPlayers;
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

    cout << "Total number of players: " << Player::getTotalPlayers() << endl;
    cout << "Total number of spins: " << RouletteWheel::getTotalSpins() << endl;

    delete wheel;
    delete player1;
    delete player2;


    return 0;
}
