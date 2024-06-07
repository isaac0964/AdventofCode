#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <set>
#include <tuple>

std::set<std::tuple<int, int>> getNeighCoords(std::vector<std::string> input) {
    // For the given input, return a set of coordinates of symbol neighbors where to check for numbers
    // Define regex to match anything but period and digits
    std::regex pattern_symbol("[^.\\d]");

    // Coordinates of symbol neighbors where to check for numbers
    std::set<std::tuple<int, int>> adjacents;  // Adjacent rows to symbol pos

    for (int i=0; i < input.size(); i++) {
        // Use sregex_iterator to find matches in the given line
        auto begin = std::sregex_iterator(input[i].begin(), input[i].end(), pattern_symbol);
        auto end = std::sregex_iterator();

        for (std::regex_iterator k = begin; k!=end; k++){
            std::smatch match = *k;
            size_t j = match.position();
            // Get neaigbors of symbol
            for (int r=i-1; r<=i+1; r++) {
                for (int c=j-1; c<=j+1; c++) {
                    // Add the adjacents of the pos of the found symbol to the sets
                    adjacents.insert(std::make_tuple(r, c));

                }
            }
        }
    }
    return adjacents;
}

int getSumGearParts(std::vector<std::string> input, std::set<std::tuple<int, int>> neighs) { 

    // Patter to match numbers
    std::regex pattern_numbers("\\d+");

    // Initialize sum of numbers
    int sum = 0;

    for (int i=0; i < input.size(); i++) {
        // Use sregex_iterator to find matches in the given line
        auto begin = std::sregex_iterator(input[i].begin(), input[i].end(), pattern_numbers);
        auto end = std::sregex_iterator();

        for (std::regex_iterator k = begin; k!=end; k++){
            std::smatch match = *k;
            std::string match_str = match.str();
            size_t j = match.position();
            // Check if any of the coordinates of the number is neighbor of symbol
            for (int p = j; p < j + match.length(); p++) {
                // If the number is neighbor of a symbol, add it to the sum
                std::tuple<int, int> coords_num(i, p);
                auto is_neigh = neighs.find(coords_num);
                if (is_neigh != neighs.end()) {
                    sum += stoi(match_str);
                    break;
                }
            }
        }
    }
    return sum;
}

int main() {

    std::vector<std::string> lines;

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
        lines.push_back(line);

    }
    
    // Get the coords of the neigbors for each symbol found
    std::set<std::tuple<int, int>> neighs = getNeighCoords(lines);

    int sum = getSumGearParts(lines, neighs);

    std::cout << "The sum of all part numbers in the engine schematic is: " << sum << std::endl;

    file.close();

    return 0;
}



    