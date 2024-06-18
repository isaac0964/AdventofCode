#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
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

std::set<std::pair<unsigned long long, unsigned long long>> getLocs(std::vector<unsigned long long> seeds, std::vector<std::vector<std::vector<unsigned long long>>> mappings){
    // Get locs for given ranges of seeds
    // Get vector of (start, end (excluding end)) pair for each seed range
    std::vector<std::pair<unsigned long long, unsigned long long>> seeds_ranges;
    for (size_t i = 0; i<seeds.size(); i+=2){
        // Add start and end of range to vector
        seeds_ranges.push_back({seeds[i], seeds[i] + seeds[i+1]});
    }   

    // Store mapped seeds here
    std::vector<std::pair<unsigned long long, unsigned long long>> processed;

    // Convert with each mapping
    for (auto map: mappings) {
        //Clear mapped seeds for new mapping
        processed.clear(); 

        // Convert each range
        while (seeds_ranges.size() > 0) {
            // Get last range in ranges vector and remove it from vector
            std::pair<unsigned long long, unsigned long long> r = seeds_ranges.back();
            seeds_ranges.pop_back();

            // Get start and end of range
            unsigned long long sStart = r.first;
            unsigned long long sEnd = r.second;

            // Bool for checking if there is conversion
            bool conv = 0;

            // for the given map, check each line if there is a mapping for the given seed
            for (auto l: map) {
                // Get destination, source and len from current line
                unsigned long long dst = l[0];
                unsigned long long src = l[1];
                unsigned long long len = l[2];

                // Get lower and upper bound of ranges (seed range and map range)
                unsigned long long lower = std::max(sStart, src);
                unsigned long long upper = std::min(sEnd, src+len);

                // Check if there is overlap
                if (lower < upper) {
                    conv = 1;
                    // If overlap convert current range
                    processed.push_back({dst + (lower - src), dst + (upper - src)});
                    // Check if there are lower/upper ranges after remaning of overlap (if true, add this to ranges that need to be processed)
                    if (sStart < lower) {
                        seeds_ranges.push_back({sStart, lower});
                    }

                    if (sEnd > upper)
                    {
                        seeds_ranges.push_back({upper, sEnd});
                    }
                    break;
                }
            }
            // If no conversion after processing all lines, keep same range
            if (!conv) {
                processed.push_back({sStart, sEnd});
            }
        }
        seeds_ranges = processed;
    }
    // Get locs in a set so they are ordered
    std::set<std::pair<unsigned long long, unsigned long long>> locs(seeds_ranges.begin(), seeds_ranges.end());
    return locs;
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
    // Get seeds (start, len)
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
        
        // Get numbers from given line (dst, src, len)
        std::vector <unsigned long long> numbers = extractNumbers(line);
        // Only store extracted if there are numbers
        if (!numbers.empty())
        {
            tempMap.push_back(numbers);
        }
    }
    mappings.push_back(tempMap);  

    std::set<std::pair<unsigned long long, unsigned long long>> locs = getLocs(seeds, mappings);
    std::cout << "Lowest location is: " << locs.begin() -> first << std::endl;

    file.close();

    return 0;
}