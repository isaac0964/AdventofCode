#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <numeric>

void addInfo2Map(std::string line, std::map<std::string, std::vector<std::string>>& dirsmap, std::vector<std::string>& start_nodes) {
    // Add current line info to map and get starting nodes
    size_t pos = line.find('=');

    if (pos != std::string::npos) {
        // If direction found, separate node from LR directions
        std::string node = line.substr(0, pos-1);

        // Get starting node
        if (node[2] == 'A') start_nodes.push_back(node);

        // Separate L and R direction
        size_t pos2 = line.find(',');
        std::string dirL = line.substr(pos+3, 3);
        std::string dirR = line.substr(pos2+2, 3);

        // Store info in map
        dirsmap[node] = {dirL, dirR};
    }
}

long getPathLength(std::string node, std::string dirs, std::map<std::string, std::vector<std::string>> dirsmap) {
    // Get path length (number of steps) for given initial node
    long steps = 0;
    
    // navigate
    while (node[2] != 'Z')
    {
        for (auto c: dirs) {
            steps++;
            if (c == 'L') node = dirsmap[node][0];
            else node = dirsmap[node][1];
            if (node[2] == 'Z') break;
        }
    }
    return steps;
}

long LCM(std::vector<long> numbers) {
    // Get LCM of multiple numbers
    long lcm = numbers[0];

    for (int i = 1; i<numbers.size(); i++) {
        lcm = std::lcm(lcm, numbers[i]);
    }
    return lcm;
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
    std::vector<std::string> start_nodes;

    // Get mapping info
    while (std::getline(file, line))
    {
        addInfo2Map(line, dirsmap, start_nodes);
    }
    
    std::vector<long> lengths;

    // Get number of steps of each node
    for (auto node: start_nodes) {
        long steps = getPathLength(node, dirs, dirsmap);
        lengths.push_back(steps);
    }

    // Total number of steps is equal to LCM (Least Common Multiple) of all path lengths
    long total_steps = LCM(lengths);

    std::cout << "The total number of steps is: " << total_steps << std::endl;

    // Stop chronometer
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop_time - start_time);
    std::cout << "Total time of execution: " << duration.count() << std::endl;
}