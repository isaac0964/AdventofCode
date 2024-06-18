#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

std::vector<unsigned long long> extractNumbers(std::string string) {
    // Extract numbers ffrom a string
    std::vector<unsigned long long> seeds;
    std::regex pattern ("\\d+");
    auto begin = std::sregex_iterator(string.begin(), string.end(), pattern);
    auto end = std::sregex_iterator();
    for (std::regex_iterator i = begin; i != end; i++) {
        std::smatch match = *i;
        seeds.push_back(stoull(match.str()));
    }
    return seeds;
}

unsigned long long getLocation(unsigned long long seed, std::vector<std::vector<std::vector<unsigned long long>>> mappings) {
    // Get location of current seed given the mappings

    // Get each mapping
    for (auto map: mappings) {
        // for the given map, check each line if there is a mapping for the given seed
        for (auto l: map) {
            // Get destination, source and len from current line
            unsigned long long dst = l[0];
            unsigned long long src = l[1];
            unsigned long long len = l[2];

            // Calculate delta for seed and src 
            unsigned long long delta = seed - src;
            // If delta is in allowed range, map seed
            if (delta >= 0 && delta < len) {
                seed = dst + delta;
                break;
            }
        }
    }
    return seed;
}

int main() {

    // vector of vectors to store mappings
    std::vector<std::vector<std::vector<unsigned long long>>> mappings;

    // Open file in read mode
    std::ifstream file("input.txt");

    if(!file) {
        std::cerr << "Could not open file!";
        return 1;
    }

    std::string line;

    // Temmporal vector to store each mapping and then add it to mappings vector
    std::vector<std::vector<unsigned long long>> tempMap;

    // First read seeds from first line 
    std::getline(file, line);
    std::string seeds_str = line;
    // Get seeds numbers 
    std::vector<unsigned long long> seeds = extractNumbers(seeds_str);
    // get line to jump first new line character and start readin from "seed-to soil map"
    getline(file, line);

    while (std::getline(file, line))
    {
        // Restart temp vector when new mapping found (empty line) and add current map to mappings vector
        if (line.empty()) {
            mappings.push_back(tempMap);
            tempMap.clear();
        }
        
        std::vector <unsigned long long> numbers = extractNumbers(line);
        if (!numbers.empty())
        {
            tempMap.push_back(numbers);
        }
    }
    mappings.push_back(tempMap);  

    // minimum location, initialize it with big value
    unsigned long long minLoc = 99999999999992;

    // For each seed, get location
    for (auto seed : seeds) {
        unsigned long long loc = getLocation(seed, mappings);

        // Check if the current seed loc is the minimun
        if (loc < minLoc) {
            minLoc = loc;
        }
    }

    std::cout << "The lowest location is: " << minLoc << std::endl;
    
    file.close();

    return 0;
}