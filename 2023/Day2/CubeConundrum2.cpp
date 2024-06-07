#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <string>


int isPossibleGame(std::string line) {
    // Return the id of the game if it is possible, 0 otherwise

    // unordered map with minimum number of cubes to make gamme possible
    std::unordered_map<std::string, int> minValues = {
        {"r", 0},
        {"g", 0},
        {"b", 0},
    };

    // Expression to match to get number and color
    std::regex pattern_colors("(\\d+) (\\w)");
    
    // Use sregex_iterator to find matches
    auto begin = std::sregex_iterator(line.begin(), line.end(), pattern_colors);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; i++) {
        std::smatch match = *i;
        std::string number_str = match.str(1);
        int number = stoi(number_str);
        std::string color = match.str(2);

        // Update minimum number of cubes to make game possible
        if (number > minValues[color]){
            minValues[color] = number;
        }
    }   

    int power = 1;

    // MUltiply minimum number of cubes
    for (auto x: minValues) {
        power *= x.second;
    }
    
    return power;
}

int main(){
    // Open file in read mode
    std::ifstream file("input.txt");

    // Sum of ids
    int sum = 0;

    // Check if file correctly openned
    if (!file){
        std::cerr << "Could not open file!" << std::endl;
        return 1;
    }

    std::string line;

    // Read file line by line
    while (std::getline(file, line)) {
        // Get id if game is possible
        int power = isPossibleGame(line);
        sum += power;
    }

    std::cout << "The sum of power is: " << sum << std::endl;

    // Close file
    file.close();
    
    return 0;
}