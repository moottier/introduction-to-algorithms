/////////////
//  Australian Voting
//  Skiena Programming Challenge 1-3
//  https://onlinejudge.org/ UVA 10142
/////////////
// Australian ballots require that the voter rank the candidates in order of choice. Initially only the first
// choices are counted and if one candidate receives more than 50% of the vote, that candidate is elected. If
// no candidate receives more than 50%, all candidates tied for the lowest number of votes are eliminated.
// Ballots ranking these candidates first are recounted in favour of their highest ranked candidate who
// has not been eliminated. This process continues [that is, the lowest candidate is eliminated and each
// ballot is counted in favour of its ranked non-eliminated candidate] until one candidate receives more
// than 50% of the vote or until all candidates are tied.
/////////////
// Input
//
// The input begins with a single positive integer on a line by itself indicating the number of the cases
// following, each of them as described below. This line is followed by a blank line, and there is also a
// blank line between two consecutive inputs.
// The first line of input is an integer n ≤ 20 indicating the number of candidates. The next n lines
// consist of the names of the candidates in order. Names may be up to 80 characters in length and may
// contain any printable characters. Up to 1000 lines follow; each contains the contents of a ballot. That
// is, each contains the numbers from 1 to n in some order. The first number indicates the candidate of
// first choice; the second number indicates candidate of second choice, and so on.
/////////////
// Output
//
// For each test case, the output must follow the description below. The outputs of two consecutive cases
// will be separated by a blank line.
// The Output consists of either a single line containing the name of the winner or several lines
// containing the names of the candidates who tied.

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <sstream>

std::vector<std::string> get_results(std::vector<std::string> candidate_names, std::vector<std::vector<int>> votes) {
    return std::vector<std::string>{"AJ", "J J"};
}


int main() {
    int scenarios, num_candidates, vote;
    std::string temp{};
    std::vector<std::string> candidate_names{}, scenario_result{};
    std::vector<std::vector<int>> votes{};
    std::vector<int> ballot{};
    std::vector<std::vector<std::string>> all_results{};
    std::istringstream iss;
    
    std::cin >> scenarios;
    getline(std::cin, temp);
    
    for (int i = 0; i < scenarios; i++) {
        // get candidate names
        std::cin >> num_candidates;
        getline(std::cin, temp);
        while(candidate_names.size() < num_candidates) {
            getline(std::cin, temp);
            candidate_names.push_back(temp);
        }
        std::cout << "Got candidates\n";

        // get votes
        while(getline(std::cin, temp) && temp != "") {
            iss.str(temp);
            while(iss >> vote) {
                ballot.push_back(vote);
            }
            votes.push_back(ballot);

            ballot.clear();
            iss.clear();
        }
        all_results.push_back(get_results(candidate_names, votes));
        
        // clean up
        // getline(std::cin, temp); // get blank line between scenarios
        candidate_names.clear();
        votes.clear();
    }
    
    // output results
    for (int i = 0; i < all_results.size(); i++) {
        scenario_result = all_results.at(i);
        for (int j = 0; j < scenario_result.size(); j++) {
            std::cout << scenario_result.at(j) << '\n';
        }
        std::cout << '\n';
    }
    return 0;
}