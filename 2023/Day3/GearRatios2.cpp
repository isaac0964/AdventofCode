#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <set>
#include <tuple>

int getSumGearRatio(std::vector<std::string> input) {
    std::regex pattern_numbers("\\d+");
    int sum = 0;
    for (int i=0; i < input.size(); i++) {

        // Look for '*' in every char
        for (int j=0; j<input[i].length(); j++) {
            if (input[i][j] != '*') {
                continue;
            }
            std::vector<int> numbers;  // Vector to store adjacent numbers to '*'
            std::set<std::tuple<int, int>> adjacents;
            // Get neighbors of current '*'
            for (int r=i-1; r<=i+1; r++) {
                for (int c=j-1; c<=j+1; c++) {
                    // Add the adjacents of the pos of the found symbol to the sets
                    adjacents.insert(std::make_tuple(r, c));
                }
            }
            
            // Look for numbers in neighbourhood of current '*'
            for (int h=i-1; h<=i+1; h++) {
                if (h < 0 || h >= input.size()) {
                    continue;
                }
                // Use sregex_iterator to find matches in the given line
                auto begin = std::sregex_iterator(input[h].begin(), input[h].end(), pattern_numbers);
                auto end = std::sregex_iterator();
                for (std::regex_iterator k = begin; k!=end; k++){
                    std::smatch match = *k;
                    std::string match_str = match.str();
                    size_t pos = match.position();
                    // Check if any of the coordinates of the number is neighbor of "*"
                    for (int p = pos; p < pos + match.length(); p++) {
                        // If the number is neighbor of "*", store it in vec of neighbors
                        std::tuple<int, int> coords_num(h, p);
                        auto is_neigh = adjacents.find(coords_num);
                        if (is_neigh != adjacents.end()) {
                            numbers.push_back(stoi(match_str));
                            break;
                        }
                    }
                }
            }
            // Check if current '*' is gear, is so compute gear ratio and add it to sum
            if (numbers.size() > 1){
                sum += numbers[0] * numbers[1];
            }
        }
    }
    return sum;
}

int main() {

    std::vector<std::string> input;

    // Open file in read mode
    std::ifstream file("input.txt");

    // Check if file opennded correctly
    if (!file) {
        std::cerr << "Could not open file!" << std::endl;
        return 1;
    }

    std::string line;

    // Get line by line and store it in lines vector
    while (std::getline(file, line)) {
        input.push_back(line);

    }
            
    int sum = getSumGearRatio(input);

    std::cout << "The sum of gear ratios is: " << sum << std::endl;
    
    
    file.close();

    return 0;
}
