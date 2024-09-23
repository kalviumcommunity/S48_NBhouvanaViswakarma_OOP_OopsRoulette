#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class RouletteWheel {
private:
    int currentNumber;


public:
    RouletteWheel() {
        srand(static_cast<unsigned>(time(0)));
        currentNumber = 0;
    }

    void spinWheel() {
        currentNumber = rand() % 37;
        cout << "The wheel spins and lands on: " << currentNumber << endl;
    }

    int getNumber() const {
        return currentNumber;
    }
};

class Player {
private:
    int balance;


public:
    Player(int initialBalance) : balance(initialBalance) {}
    

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
};


int main() {
    RouletteWheel* wheel = new RouletteWheel();
    Player* player = new Player(1000);

    player->placeBet(100, 17, *wheel);

    cout << "Final Balance: $" << player->getBalance() << endl;

    delete wheel;
    delete player;

    return 0;
}
