#include <iostream>
#include <chrono>
#include <fstream>
#include <regex>


std::vector<int> extractNumbers(std::string string) {
    // Extract numbers from a string
    std::vector<int> numbers;
    std::regex pattern ("\\d+");
    auto begin = std::sregex_iterator(string.begin(), string.end(), pattern);
    auto end = std::sregex_iterator();
    for (std::regex_iterator i = begin; i != end; i++) {
        std::smatch match = *i;
        numbers.push_back(stoi(match.str()));
    }
    return numbers;
}

std::pair<int, int> getMaxMinTimesPressed(int t, int d){
    // For the given time and distance, get the minimum and max time of button holding
    // that breaks record distance
    /*
    Distance will be given by d = tp (t-tp) using v=d/t, where tp is the time that button is pressed
    in this case, tp = v, we can rewrite this as tp^2 - t * tp + d = 0
    the roots of this equation will give the minimum and max tp that are equal to the record, we just need to 
    ceil this number to get a integer

    First we solve the given equation with given values of t and d, for this we assume that all values of t and d
    yield equations with two roots
    */

    int tp_max, tp_min;
    // Solving for tp and getting tp max and min and ceiling
    // We are accounting for the -t in -t * tp
    tp_max = std::ceil((t + std::sqrt(t*t - 4*d)) / 2);
    tp_min = std::ceil((t - std::sqrt(t*t - 4*d)) / 2);

    // if record is tied with tp_min, add 1 because record needs to be beated, not tied
    if ((tp_min * (t-tp_min)) == d) {
        tp_min++;
    }

    // Here, in the range of allowed values for beating the record, tp_max is excluded
    // So tps that beat the record are in range [tp_min, tp_max)

    std::pair<int, int>tps ({tp_min, tp_max});
    return tps;
}

int main() {

    // start chronometer
    auto start_time = std::chrono::high_resolution_clock::now();

    // Open file in read mode
    std::ifstream file("input.txt"); 

    // Check if file correctly openned
    if (!file) {
        std::cerr << "Could not open file!" << std::endl;
        return 1;
    }

    std::string line;

    // Get races times
    std::getline(file, line);
    std::vector<int> ts = extractNumbers(line);

    // Get races distanes 
    std::getline(file, line);
    std::vector<int> ds = extractNumbers(line);

    int ways = 1;

    // Get the number of ways of breaking the record for each race and multiply it
    for (int i=0; i<ts.size(); i++) {
        // Get min and max tp for given race
        std::pair<int, int>tps = getMaxMinTimesPressed(ts[i], ds[i]);
        // The number of ways of breaking record is (tp_max-tp_min)
        ways *= (tps.second - tps.first);
    }

    
    std::cout << "The total numbers of ways you can beat the record is: " << ways << std::endl;
        
    // Stop chronometer
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);  // Get chronometer duration

    std::cout << "Total time of program execution: " << duration.count() << " microseconds" << std::endl;

    return 0;
}