#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <regex>
#include <set>

bool isAllZeros(std::vector<long> vec) {
    // Check if all elements in vector are zero
    bool zeros = 1;

    for (int i = 0; i<vec.size(); i++) {
        if (vec[i] != 0) {
            zeros = 0;
            break;
        }
    }
    return zeros;
}

std::vector<long> getNumbers(std::string line) {
    // Get numbers in a vector from a string

    std::vector<long> numbers;

    // Numbers pattern including optional minus sign
    std::regex pattern("[-]?\\d+");
    auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);

    // Get each match
    for (std::regex_iterator i=begin; i != std::sregex_iterator(); i++) {
        std::smatch match = *i;
        numbers.push_back(stol(match.str()));
    }
    return numbers;
}

std::vector<long> computeDifference(std::vector<long> sequence) {
    // Compute difference of adjacent elements in sequence
    // For a sequence of length n, this will result in a sequence of length n-1
    std::vector<long> diff;
    for (int i=1; i<sequence.size(); i++) {
        diff.push_back(sequence[i] - sequence[i-1]);
    }
    return diff;
}

long getNextValue(std::vector<long> sequence) {
    // Get next value of given sequence

    // Next value will be the sum of last element in all sequences (original sequence and sequence generated from differences)
    long nextVal = 0;

    int idx = 1;  // To check whether to add or substract value
    // Calculate differences until we reach 0 sequence (sequence with all zeros)
    while (!isAllZeros(sequence))
    {   
        if (idx%2 != 0) {  // idx odd, +
        nextVal += sequence[0];
        
        }
        else {  // idx even, -
            nextVal -= sequence[0];
        }
        sequence = computeDifference(sequence);
        idx++;
    }
    return nextVal;
}

int main() {
    
    // Start chronometer 
    auto start_time = std::chrono::high_resolution_clock::now();

    // Open file in read mode
    std::ifstream file("input.txt");

    // Check if file correctly openned
    if (!file) {
        std::cerr << "Could not open file!" << std::endl;
        return -1;
    }

    std::string line;
    long sum = 0;  // Sum of next values
    
    while (std::getline(file, line))
    {
        std::vector<long> numbers = getNumbers(line);
        sum += getNextValue(numbers);  // Get next value of current sequence and add it to the sum
    }
    
    std::cout << "The sum of extrapolated values is: " << sum << std::endl;

    // Stop chronometer 
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop_time - start_time);
    std::cout << "Time of execution: " << duration.count() << std::endl;
}