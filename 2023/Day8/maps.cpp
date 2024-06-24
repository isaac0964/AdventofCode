#include <iostream>
#include <fstream>
#include <map>
#include <chrono>

void addInfo2Map(std::string line, std::map<std::string, std::vector<std::string>>& dirsmap) {
    // Add current line info to map
    size_t pos = line.find('=');

    if (pos != std::string::npos) {
        // If direction found, separate node from LR directions
        std::string node = line.substr(0, pos-1);

        // Separate L and R direction
        size_t pos2 = line.find(',');
        std::string dirL = line.substr(pos+3, 3);
        std::string dirR = line.substr(pos2+2, 3);

        // Store info in map
        dirsmap[node] = {dirL, dirR};
    }
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

    // Get LR directions
    std::getline(file, line);
    std::string dirs = line;


    std::map<std::string, std::vector<std::string>> dirsmap;

    // Get mapping info
    while (std::getline(file, line))
    {
        addInfo2Map(line, dirsmap);
    }

    // Current node
    std::string node = "AAA";

    int steps = 0;
    
    // navigate according to 
    while (node != "ZZZ")
    {
        for (auto c: dirs) {
            steps++;
            if (c == 'L') node = dirsmap[node][0];
            else node = dirsmap[node][1];
            if (node == "ZZZ") break;
        }
    }
    
    std::cout << "Total number of steps: " << steps << std::endl;

    // Stop chronometer
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop_time - start_time);
    std::cout << "Total time of execution: " << duration.count() << std::endl;
}