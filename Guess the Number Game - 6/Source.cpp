#include<iostream> //Include the necessary library for input/output.
#include<cstdlib> //Include the library for the random number generator functions (rand() and srand()).
#include<ctime> //Include the library for time-related functions(time()).
#include<vector> //Include the C++ Standard Template Library(STL) vector header for using the vector container.

using namespace std; //Use the standard C++ namespace to simplify the use of standard functions.

class AdvancedNumberGuesser {
private:
	int secretNumber; //Stores the secret number to be guessed.
	int previousGuess; //Stores the user's previous guess.
	int attempts; //Stores the number of attempts made by the user.
	bool hintsEnabled; //Added a flag to enable/disable hints.
	int score; //Added a score to keep track of the player's performance.
	int maxAttempts; //Added a maximum number of attempts allowed.
	vector<int> previousGuesses; //Stores the user's previous guesses in a vector.
	//Function to generate a random number within a specified range.
	int generateRandomNumber(int min, int max) {
		return rand() % (max - min + 1) + min; //0-99 + 1 -> 100. Generates a random number between specified range.
	}
	//Function to update the score based on the number of attempts.
	void updateScore() {
		if (attempts % 2 == 0) {
			score -= 50;
		}
		else {
			score -= 30;
		}
	}
public:
	//Constructor for the AdvancedNumberGuesser class.
	AdvancedNumberGuesser(){
		srand(time(0)); //Seed the random number generator with the current time to produce different random numbers each time the program runs.

		secretNumber = generateRandomNumber(1, 100); //Generate a random number between 1 and 100.

		previousGuess = 0; 
		attempts = 0;	
		hintsEnabled = true; //Hints are enabled by default.
		score = 1000; //Starting score.
		maxAttempts = 10; //Maximum attempts allowed.

		cout << "Welcome to the Advanced Number Guesser!" << endl;
		cout << "Try to guess the secret number between 1 and 100." << endl;
		cout << "You can enter '0' to get a hint" << endl;
		cout << "You can also disable hints by entering '-1'." << endl;
		cout << "Your score changes dynamically with each attempt, and there are only" << maxAttempts << " allowed." << endl;
	}
	//Function to provide hints based on the difference between the guess and the secret number.
	void provideHint() {
		//Check if hints are currenty disabled.
		if (!hintsEnabled) {
			cout << "Hints are currently disabled." << endl;
			return;
		}
		int difference = abs(previousGuess - secretNumber); //Absolute difference between the previous guess and secret number is calculated to ensure positive values.
		if (difference >= 20) {
			cout << "Hint: You are far from the secret number." << endl;
		}
		else if (difference >= 10) {
			cout << "Hint: You are getting closer to the secret number." << endl;
		}
		else {
			cout << "Hint: You are very close to the secret number." << endl;
		}
	}
	//Function to display the user's previous guesses.
	void displayPreviousGuesses() {
		cout << "Previous guesses: ";
		for (int guess : previousGuesses) {
			cout << guess << " ";
		}
		cout << endl;
	}

	//Function to play the number guessing game.
	void playGame() {
		do {
			cout << "Attempts left: " << maxAttempts - attempts << " | Score: " << score << endl;
			cout << "Enter your guess: ";

			int guess;
			cin >> guess;
			attempts++;

			previousGuesses.push_back(guess); //Store the user's guess in the vector of previous guesses.
			updateScore(); //Update the score based on the number of attempts.
			//Check if the user's guess is correct.
			if (guess == secretNumber) {
				cout << "Congratulations! You guessed the correct number in " << attempts << " attempts." << endl;

			}
			//Check if the user wants a hint.
			else if (guess == 0) {
				provideHint();
			}
			//Check if the user wants to disable hints.
			else if (guess == -1) {
				hintsEnabled = false;
				cout << "Hints are now diabled. Continue guessing." << endl;
			}
			//Check if the guess is out of the limit.
			else if (guess < 1 || guess > 100) {
				cout << "Invalid guess. Please enter a number between 1 and 100." << endl;
			}
			//Check if the guess is lower than the secret number.
			else if (guess < secretNumber) {
				cout << "Too low. Try again!" << endl;
			}
			//If none of the above conditions are met, the guess is too high.
			else {
				cout << "Too high. Try again!" << endl;
			}
			//Display the user's previous guess.
			displayPreviousGuesses();
			previousGuess = guess;
		} while (previousGuess != secretNumber && attempts < maxAttempts);
		cout << "You lost!" << endl;
	}
};

int main() {
	AdvancedNumberGuesser advancedGame; //Create an object (advancedgame) of the AdvancedNumberGuesser class.
	advancedGame.playGame(); //Call the playGame function to start the game.

	return 0; //Indicates successful program execution.

}
