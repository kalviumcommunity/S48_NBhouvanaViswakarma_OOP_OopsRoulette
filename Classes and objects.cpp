#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <path>

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
    
    Player(int balance) {
        this->balance = balance;
    }

    Player& placeBet(int betAmount, int number, RouletteWheel& wheel) {
        if (betAmount > this->balance) {
            cout << "Insufficient balance." << endl;
            return *this; 
        }

        wheel.spinWheel();
        if (wheel.getNumber() == number) {
            int winnings = betAmount * 35;
            this->balance += winnings;
            cout << "You win! Your new balance is: $" << this->balance << endl;
        } else {
            this->balance -= betAmount;
            cout << "You lose! Your new balance is: $" << this->balance << endl;
        }

        return *this; 
    }

    int getBalance() const {
        return balance;
    }
};

int main() {
    RouletteWheel wheel;

    Player players[3] = { Player(1000), Player(1500), Player(2000) };

    players[0].placeBet(100, 17, wheel);
    players[1].placeBet(200, 5, wheel);
    players[2].placeBet(300, 10, wheel);

    for (int i = 0; i < 3; ++i) {
        cout << "Player " << (i + 1) << " Final Balance: $" << players[i].getBalance() << endl;
    }

    return 0;
}
