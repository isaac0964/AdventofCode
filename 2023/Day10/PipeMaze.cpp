// Based on: https://github.com/tsoli/advent-of-code/blob/main/2023/day10a/solution.cpp

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <map>

// Mapping from char to dirs that are neigbors of given pipe
std::map<char, std::pair<std::pair<int, int>, std::pair<int, int>>> mapChar{
    {'|', {{0, -1}, {0, 1}}}, {'-', {{-1, 0}, {1, 0}}}, {'L', {{0, -1}, {1, 0}}},
    {'J', {{0, -1}, {-1, 0}}}, {'7', {{0, 1}, {-1, 0}}}, {'F', {{0, 1}, {1, 0}}}
    };

// Directions (Left, Up, Down, Right)
std::vector<std::pair<int, int>> dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

std::pair<int, int> startPos = {-1, -1};  // Starting position

void replaceStart(std::vector<std::string>& maze) {
    // Replace "S" with valid pipe
    std::vector<std::pair<int, int>> connections;  // Connections with s

    // Check where "S connects with pipes"
    for (auto dir: dirs) {
        std::pair<int, int> newPos = {startPos.first + dir.first, startPos.second + dir.second};
        // Check out of bound idxs
        if (newPos.first < 0 || newPos.second < 0) continue;

        // Get tipe of ground or pipe
        char ground = maze[newPos.second][newPos.first];

        // Do not check for pipes if next pos type is a dot (ground)
        if (ground == '.') continue;

        // The required connection to current pipe will be the opposite to dir
        // e.g. if foud pipe at left dir, required connection will be left
        std::pair<int, int> reqCon = {-dir.first, -dir.second};
        // Check if pipe connects to any of required connections and add this dir to connections 
        if (mapChar.at(ground).first == reqCon || mapChar.at(ground).second == reqCon) connections.push_back(dir);
    }

    // Get pipe that is viable for given connection
    std::pair<std::pair<int, int>, std::pair<int, int>> allCons = {connections[0], connections[1]};  // All conections required
    for (auto& pair: mapChar) {
        if (pair.second == allCons) maze[startPos.second][startPos.first] = pair.first;
    }
}

int getStepsFarthest(std::vector<std::string> maze) {
    // Get farthest position (Assuming only two neighbors, so 2 paths)
    int l = 0;  // Length of cycle

    std::pair<int, int> currPos = startPos;
    std::pair<int, int> lastPos = {-1, -1};

    do {
        char ground = maze[currPos.second][currPos.first];

        // Get connections
        std::pair<std::pair<int, int>, std::pair<int, int>> connections = mapChar[ground];

        // Each pipe has two connections, one can take us back to last pos and the other takes us
        // to a new pos, check this using if and position after step
        std::pair<int, int> stepPos = {currPos.first + connections.first.first, currPos.second + connections.first.second};

        // If first connection takes us to different place, take first connection
        if (stepPos != lastPos) {
            // Update last position
            lastPos = currPos;

            // Update current pos
            currPos = stepPos;
        }

        // If first connection takes us to same last place, take second connection
        else {
            // Update last position
            lastPos = currPos;

            // Update current pos
            currPos.first += connections.second.first;
            currPos.second += connections.second.second;
        }
        l++;
    }
    while (currPos != startPos);

    // Assuming only two paths, steps to farthest position will be half of cycle length
    return l/2;
}

int main() {
    
    auto start_time = std::chrono::high_resolution_clock::now();

    // Open file in read mode
    std::ifstream file("input.txt");

    // Check if file correctly openned
    if (!file){
        std::cerr << "Could not open file" << std::endl;
        return -1;
    }

    std::vector<std::string> maze;
    std::string line;

    int y = 0;  // row of start pos
    while (std::getline(file, line))
    {
        // Look for starting pos
        size_t x = line.find("S");
        if (x != std::string::npos) {
            // If S found, save current pos
            startPos = {x, y};
        }
        y++;
        maze.push_back(line);
    }

    replaceStart(maze);
    
    int steps = getStepsFarthest(maze);

    std::cout << steps << std::endl;
    
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop_time - start_time);
    std::cout << "Total execution time: " << duration.count() << " microseconds" << std::endl; 
}