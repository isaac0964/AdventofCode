#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <string>

struct CubesPerColor {
    int n_red;
    int n_green;
    int n_blue;
};

CubesPerColor getCubesPerColor(std::string trial) {
    // Get the number of cubes per color for a given trial
    CubesPerColor n_cubes = {0, 0, 0};

    // Expression to match to get number and color
    std::regex pattern("(\\d+) (red|green|blue)");
    
    
    // Use sregex_iterator to find matches
    auto begin = std::sregex_iterator(trial.begin(), trial.end(), pattern);
    auto end = std::sregex_iterator();


    for (std::sregex_iterator i = begin; i != end; i++) {
        std::smatch match = *i;
        std::string number = match.str(1);
        std::string color = match.str(2);

        // Convert number to string
        int n = stoi(number);

        // Add number of cubes to the corresponding color
        if (color=="red"){
            n_cubes.n_red = n;
        }
        else if (color=="green"){
            n_cubes.n_green = n;
        }
        else{
            n_cubes.n_blue = n;
        }
    }
    return n_cubes;
}

int isPossibleGame(std::string line) {
    // Return the id of the game if it is possible, 0 otherwise

    // unordered map with max values for each colo
    std::unordered_map<std::string, int> maxValues = {
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
        
        if (number > maxValues[color]){
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

/*
    // Max number of red, green and blue cubes, respectively
    std::vector<int> config = {12, 13, 14};

    // Separate game id from game info
    size_t delimiter_pos = line.find(":");
    std::string game_id = line.substr(0, delimiter_pos);
    // Expression to match to get game id
    std::regex pattern("\\d+");
    std::smatch match;  // Match object to sture matched number
    std::regex_search(game_id, match, pattern);  // get number
    std::string id_str = match.str();  // get id as string
    
    int id_number = stoi(id_str);  // Convert game id to int
    std::string game_info = line.substr(delimiter_pos+2);


    // Get the number of cubes of each game trial
    size_t pos = 0;
    std::string token;
    std::vector<std::string> trials;  // Vector for storing each game trial
    while ((pos = game_info.find(";")) != std::string::npos) {
        token = game_info.substr(0, pos);
        trials.push_back(token);
        game_info.erase(0, pos+2);  // Deleted the substring that has already being pased
    }
    trials.push_back(game_info);

    // Add the number of cubes of each color of each trial to the total of the game
    for (auto trial: trials){
        CubesPerColor n_cubes = getCubesPerColor(trial);
        red += n_cubes.n_red;
        green += n_cubes.n_green;
        blue += n_cubes.n_blue;
        
    }

    int res = 13 <= config[1];
    std::cout << id_number<< ": " <<red << " " << green <<" " << blue << " " << res  << std::endl;
    //Check if game is possible
    int id = (red <= config[0] && green <= config[1] && blue <= config[2]) ? id_number : 0;

    return id;
    */
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