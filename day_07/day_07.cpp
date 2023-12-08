#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


std::vector<char> cardTypes = {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};


int getHandPrimaryScore(const std::string& hand) {

    std::vector<int> cardCount(13, 0);
    for (std::vector<char>::size_type i = 0; i < cardTypes.size(); i++) {
        auto count = std::ranges::count(hand, cardTypes[i]);
        cardCount[i] = count;
    }

    if (std::ranges::count(cardCount, 5) == 1) {
        return 7;
    } else if (std::ranges::count(cardCount, 4) == 1) {
        return 6;
    } else if (std::ranges::count(cardCount, 3) == 1 && std::ranges::count(cardCount, 2) == 1) {
        return 5;
    } else if (std::ranges::count(cardCount, 3) == 1) {
        return 4;
    } else if (std::ranges::count(cardCount, 2) == 2) {
        return 3;
    } else if (std::ranges::count(cardCount, 2) == 1) {
        return 2;
    } else {
        return 1;
    }
}


int getJokerHandScore(const std::string& hand) {

    int score = 0;
    for (std::vector<char>::size_type i = 1; i < cardTypes.size(); i++) {
        std::string jokerHand = hand;
        std::replace(jokerHand.begin(), jokerHand.end(), 'J', cardTypes[i]);
        int s = getHandPrimaryScore(jokerHand);
        if (s > score) score = s;
    }
    return score;
}


long int totalCamelCardWinnings(const std::string& file_name) {

    std::ifstream f (file_name);
    if (!f.is_open()) {
        perror("Error opening file");
    }

    std::string line;
    std::vector<long int> sortedScores;
    std::vector<long int> sortedBids;
    while (getline(f, line)) {

        std::string hand = line.substr(0, 5);
        long int bid = std::stol(line.substr(5));

        // Base 13 addition :/
        long int handScore = 0;
        int thirteensCol = 6;
        handScore += getJokerHandScore(hand) * pow(13, thirteensCol);
        for (std::string::size_type i = 0; i < hand.size(); i++) {
            thirteensCol -= 1;
            std::ptrdiff_t pos = std::find(cardTypes.begin(), cardTypes.end(), line[i]) - cardTypes.begin() + 1;
            handScore += pos * pow(13, thirteensCol);
        }

        auto it = std::lower_bound(sortedScores.begin(), sortedScores.end(), handScore);
        sortedScores.insert(it, handScore);
        it = std::lower_bound(sortedScores.begin(), sortedScores.end(), handScore);
        sortedBids.insert(sortedBids.begin() + std::distance(sortedScores.begin(), it), bid);
    }

    long int winnings = 0;
    for (std::vector<long int>::size_type i = 0; i < sortedBids.size(); i++) {
        winnings += (i + 1) * sortedBids[i];
    }

    return winnings;
}


int main() {
    long int result = totalCamelCardWinnings("data_real.txt");
    std::cout << "Camel card winnings = " << result << std::endl;
    return 0;
}
