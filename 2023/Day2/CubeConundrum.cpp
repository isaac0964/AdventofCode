#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <string>




int isPossibleGame(std::string line) {
    // Return the id of the game if it is possible, 0 otherwise
    struct 

    // unordered map with max values from config for each color
    std::unordered_map<std::string, int> maxConfig = {
        {"r", 12},
        {"g", 13},
        {"b", 14},
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
        
        if (number > maxConfig[color]){
            return 0;
        }
    }

    // Get game id
    std::regex pattern_id("(\\d+)");
    std::smatch match;

    std::regex_search(line, match, pattern_id);
    std::string id_str = match.str();  // Get id as str
    int id = stoi(id_str);  // convert id to ing
    
    return id;
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
        int id = isPossibleGame(line);
        sum += id;
    }

    std::cout << "The sum of ids is: " << sum << std::endl;

    // Close file
    file.close();
    
    return 0;
}