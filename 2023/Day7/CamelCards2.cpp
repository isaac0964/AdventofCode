#include <fstream>
#include <iostream>
#include <chrono>
#include <map>
#include <map>
#include <algorithm>

// Maps from card to int
std::map<char, int> cards_map;

struct Hand
{
    std::vector<int> cards;
    int type;
    int bid;
};

bool compareHands(Hand a, Hand b){
    // Function to compare hands, this function will be used to order the hands
    if (a.type > b.type)  return true;

    else if (a.type < b.type) return false;

    // If same type, check cards
    for(int i = 0; i<a.cards.size(); i++) {
        if (a.cards[i] != b.cards[i]) return a.cards[i] > b.cards[i];
    }

    return false;
}


Hand getHandInfo(std::string line) {
    // Get hand cards as integer, hand type and bid for given line

    Hand hand;

    // Position of whitespace
    size_t pos = line.find(" ");
    // Separate cards and bid
    int bid = stoi(line.substr(pos));
    std::string hand_str = line.substr(0, pos);

    std::vector<int> cards;

    // Map to get number of labels for each card
    std::vector<int> reps (13, 0);

    bool joker = 0;

    for (auto x: hand_str) {
        cards.push_back(cards_map[x]);
        // Count number of each type of card
        reps[cards_map[x]-2] += 1;
        if (x == 'J') joker = 1;
    }

    // If there is joker, use it as  wildcard to make hand stronger
    if (joker) {
        int njs = reps[0];  // Number of jokers
        reps[0] = 0;
        // Get index of element with max number of reps
        auto max = std::max_element(reps.begin(), reps.end());
        size_t argmax = std::distance(reps.begin(), max);
        reps[argmax] += njs;  // Add joker reps to get a stronger hand
    }

    

    // Get number of labels that are repeated two times
    auto it = reps.begin();
    int n2 = 0; 
    while (it != reps.end()) {
        it = std::find(it, reps.end(), 2);
        if (it != reps.end()) {
             n2 += 1;
             it++;
        }
    }
    
    // Check type of label according to number of labels
    int type;
    if (std::find(reps.begin(), reps.end(), 5) != reps.end()) {
        type = 7;  // Five of a kind
    }
    else if (std::find(reps.begin(), reps.end(), 4) != reps.end())
    {
        type = 6;  // Four of a kind
    }

    else if ((std::find(reps.begin(), reps.end(), 3) != reps.end()) && (std::find(reps.begin(), reps.end(), 2) != reps.end()))
    {
        type = 5; // Full house   
    }

    else if ((std::find(reps.begin(), reps.end(), 3) != reps.end()) && (std::find(reps.begin(), reps.end(), 2) == reps.end()))
    {
        type = 4; // Three of a kind
    }

    else if (n2 == 2) {
        type = 3; // Two pair
    }

    else if (n2 == 1) {
        type = 2; // One pair
    }

    else {
        type = 1;  // High card
    }
    
    hand.cards = cards;
    hand.type = type;
    hand.bid = bid;
    return hand;
}

int main() {

    // Start chronometer
    auto start_time = std::chrono::high_resolution_clock::now();

    // All cards
    std::vector<char> cards_names = {'J', '2','3','4','5','6','7','8','9','T', 'Q','K','A'};

    // Create mapping from cards to int (value of card)
    for (int i = 2; i<15; i++) {
        cards_map[cards_names[i-2]] = i;
    }

    // Open file in read mode
    std::ifstream file("input.txt");

    // Check if file correctly openned
    if (!file) {
        std::cerr << "Could not open file!" << std::endl;
        return -1;
    }

    // Vector to store each hand
    std::vector<Hand> hands;

    std::string line;

    while(std::getline(file, line)) {
        hands.push_back(getHandInfo(line));
    }

    std::sort(hands.begin(), hands.end(), compareHands);

    // Get total winnng multiplying each hand's rank by its bid and adding them up
    int total = 0;
    for (int i = 0; i<hands.size(); i++) {
        total += hands[i].bid * (hands.size() - i);
    }   

    std::cout << "The total winning is: " << total << std::endl;

    // Stop chronometer 
    auto stop_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop_time - start_time);

    std::cout << "Total time of execution: " << duration.count() << " microseconds" << std::endl;
}