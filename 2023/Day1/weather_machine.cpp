#include <iostream>
#include <fstream>
#include <string>

void getFloor(std::string line){
    // Get the number of the given sequence of ()

    int floor = 0;
    for (char& c: line) {
        if (c == '('){
            floor += 1;
        }
        else{
            floor -= 1;
        }
    }
    std::cout << floor << std::endl;
}
    

int main () {

    // Open file in read mode
    std::ifstream file("input2.txt");

    // Check if file correctly openned
    if (!file) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }

    // Read file line by line
    std::string line;

    while (std::getline(file, line))
    {
        getFloor(line);
    }

    // Close file
    file.close();
    return 0;
}