#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <regex>
#include <cmath>

// Struct two return winNumbers andmyNumbers in getNumbers function
struct Numbers
{
    std::set<int> winNumbers;
    std::vector<int> myNumbers;
};

Numbers getNumbers(std::string game) {
    // This fucntion gets the winning numbers and numbers I have for the given game
    Numbers numbers;

    std::set<int> winNumbers;
    std::vector<int> myNumbers;

    // Separate winning numbers and numbers I have

    // Get the pos of ":" and "|" to separate numbers
    size_t pos1 = game.find(":") + 2;  // Add two to get the pos of the first number in winning numbers (remove whitespace)
    size_t pos2 = game.find("|");

    // get string of winning numbers and my numbers
    std::string winNumbers_str = game.substr(pos1, (pos2 - pos1 - 1));  // Remove 1 to not take into account the whitespace before "|" 
    std::string myNumbers_str = game.substr(pos2 + 2);  // Add 2 to not take into account the whitespace after "|"  

    // Put winning numbers in set and my numbers in vector
    // Use sregex_iterator to find matched numbers
    std::regex pattern("\\d+");
    auto begin = std::sregex_iterator(winNumbers_str.begin(), winNumbers_str.end(), pattern);
    auto end = std::sregex_iterator();
    
    for(std::regex_iterator i=begin; i!=end; i++){
        std::smatch match = *i;
        winNumbers.insert(stoi(match.str()));
    }
    
    // Same for my numbers
    begin = std::sregex_iterator(myNumbers_str.begin(), myNumbers_str.end(), pattern);
    for(std::regex_iterator i=begin; i!=end; i++){
        std::smatch match = *i;
        myNumbers.push_back(stoi(match.str()));
    }

    numbers.winNumbers = winNumbers;
    numbers.myNumbers = myNumbers;

    return numbers;
}

int getNoWinners(std::string game) {
    // Get the number of winners of game

    Numbers numbers = getNumbers(game);

    std::set<int> winNubers = numbers.winNumbers;
    std::vector<int> myNumbers = numbers.myNumbers;

    // Get Number of winning numbers
    size_t count = 0;
    for (auto i : myNumbers) {
        if (winNubers.find(i) != winNubers.end()) {
            count += 1;
        }
    }

    return count;
}

int getTotalScratch(std::vector<int> winnersPerGame, std::vector<int> cardsPerId) {
    // Function to get the total number of cards

    // Iterate over each card
    for (int i=0; i<winnersPerGame.size(); i++) {
        // Iterate over each winner of current card
        for (int j=i+1; j<=winnersPerGame[i]+i; j++) {
            // Avoid getting out of bound
            if (j>=winnersPerGame.size()) {
                break;
            }
            // Add number current of cards (i) to number of cards of current winner
            cardsPerId[j] += cardsPerId[i];
        }
    }

    int total = 0;

    for (auto x: cardsPerId) {
        total += x;
    }
    return total;
}



int main() {

    // Number of winners for each card
    std::vector<int> winnersPerGame;

    // Open file in read mode
    std::ifstream file("input.txt");

    // Check if file correctly openned
    if (!file) {
        std::cerr << "Could not open file!" << std::endl;
        return 1;
    }

    // Get each game from file and get points
    std::string game;

    while(std::getline(file, game)) {
        winnersPerGame.push_back(getNoWinners(game));
    }

    // Number of scratchcards for each id (Initially each id has 1 card)
    std::vector<int> cardPerId (winnersPerGame.size(), 1);

    int total = getTotalScratch(winnersPerGame, cardPerId);

    std::cout << "The total number of scratchcards is: " << total << std::endl;

    file.close();

    return 0;
}