#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int extractInt(std::string line) {
    // Extract the firt and last integers from the given string (line)

    // store the number as string
    std::string num = "";
    // Loop over every character of string
    for (char& c: line) {
        if (isdigit(c)) {
            num += c;
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

    std::cout << sum << std::endl;

    return 0;
}