#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Initialize random seed
    std::srand(std::time(0));

    // Generate a random number between 1 and 100
    int secretNumber = std::rand() % 100 + 1;
    int playerGuess = 0;
    int numberOfTries = 0;

    std::cout << "Welcome to the Guess the Number game!" << std::endl;
    std::cout << "I have selected a number between 1 and 100." << std::endl;

    // Game loop
    do {
        std::cout << "Enter your guess: ";
        std::cin >> playerGuess;

        numberOfTries++;

        if (playerGuess > secretNumber) {
            std::cout << "Too high! Try again." << std::endl;
        } else if (playerGuess < secretNumber) {
            std::cout << "Too low! Try again." << std::endl;
        } else {
            std::cout << "Congratulations! You guessed the number in " << numberOfTries << " tries!" << std::endl;
        }
    } while (playerGuess != secretNumber);

    return 0;
}
