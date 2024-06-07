#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int extractInt(std::string line) {
    // Extract the firt and last integers from the given string (line) incluiding numbers written (one, two, etc)

    // Empty string for storing the digits
    std::string num = "";

    // Create unordered map that maps number name to digit
    std::unordered_map<std::string, int> wordDigit = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
    };

    for (int i=0; i < line.length(); i++) {
        // substring with starting in ith char to last char in string
        std::string substr = line.substr(i);

        // check if first char is digit and add it to num string
        if (isdigit(substr[0])){
            num += substr[0];
        }

        // check if it is a written number if numbers have not already been found
        else {
            // Check every written digit
            for (auto x: wordDigit) {
                // Check if string starts with written number
                size_t pos = substr.rfind(x.first, 0);
                // If written digit is found, map the string to integer and add it to num
                if (pos != std::string::npos){
                    num += std::to_string(x.second);
                }
            }
        }
    }
    
    // get first and last digits for number to form a 2 digit number
    char first = num[0];
    char last = num[num.length()-1];
    // Join the two digits 
    auto number = std::string(1, first) + last;
    
    return stoi(number);
}

int main(){
    // Open file in read mode
    std::ifstream file("input.txt");

    int sum = 0;

    // Check if file correctly openned
    if (!file) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }

    // Read file line by line
    std::string line;

    while (std::getline(file, line))
    {
        // Extract numbers from given line
        int number = extractInt(line);
        
        // Add number to total sum
        sum += number;
    }
    
    // Close file
    file.close();

    std::cout << "Calibration Value: " << sum << std::endl;
    return 0;
}