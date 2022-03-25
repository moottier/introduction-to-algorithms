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
#include <limits>
#include <algorithm>

std::vector<std::string> get_results(std::vector<std::string> candidate_names, std::vector<std::vector<int>> all_ballots) {
    std::vector<int> candidate_votes(candidate_names.size(), 0), eliminated, to_eliminate;
    std::vector<std::string> winners;
    int lowest_votes, highest_votes, lowest_candidate;

    for (int i = 0; i < candidate_names.size(); i++) {
        // count all i-th round votes
        std::fill(candidate_votes.begin(), candidate_votes.end(), 0);
        for (int j = 0; j < all_ballots.size(); j++) {
            candidate_votes.at(all_ballots.at(j).at(0) - 1)++;    // ballot index != ballot array index
        }

        // check for winner w/ >50
        winners.clear();
        for (int k = 0; k < candidate_votes.size(); k++) {
            if (candidate_votes.at(k) > all_ballots.size() / 2.0) {
                winners.push_back(candidate_names.at(k));
            }
        }

        // return if winner found
        if (winners.size() > 0) break;

        // get lowest votes in round
        lowest_votes = std::numeric_limits<int>::max();
        for (int j = 0; j < candidate_votes.size(); j++) {
            // don't include eliminated candidates in check for lowest
            if (find(eliminated.begin(), eliminated.end(), j) == eliminated.end() && candidate_votes.at(j) < lowest_votes) {
                lowest_votes = candidate_votes.at(j);
            }
        }

        // get candidates to eliminate
        to_eliminate.clear();
        for (int j = 0; j < candidate_votes.size(); j++) {
            if (candidate_votes.at(j) == lowest_votes) {
                to_eliminate.push_back(j);    // ballot index != ballot array index
            }
        }

        // check if we're eliminating everyone that's left
        // if we are; then they all win
        // else continue
        if (eliminated.size() + to_eliminate.size() == candidate_names.size()) {
            for (int j = 0; j < to_eliminate.size(); j++) {
                winners.push_back(candidate_names.at(to_eliminate.at(j)));
            }
        } else {
            eliminated.insert(eliminated.end(), to_eliminate.begin(), to_eliminate.end());
        }

        // return if winner found
        if (winners.size() > 0) break;

        // rotate ballot for eliminated
        // FIXME: rotate to next non-eliminated person
        for (int j = 0; j < all_ballots.size(); j++) {
            for (int k = 0; k < eliminated.size(); k++) {
                if (all_ballots.at(j).at(0) - 1 == eliminated.at(k)) {
                    while(std::find(eliminated.begin(), eliminated.end(), all_ballots.at(j).at(0) - 1) != eliminated.end()) {
                        std::rotate(all_ballots.at(j).begin(), all_ballots.at(j).begin() + 1, all_ballots.at(j).end());
                    }
                }
            }
        }
    }

    // if nobody w/ >50, then find highest %
    if (winners.size() == 0) {
        highest_votes = std::numeric_limits<int>::lowest();
        for (int j = 0; j < candidate_votes.size(); j++) {
            if (candidate_votes.at(j) <= highest_votes) {
                winners.push_back(candidate_names.at(j - 1));
            }
        }
    }

    return winners;
}


int main() {
    int scenarios, num_candidates, vote;
    std::string temp{};
    std::vector<std::string> candidate_names{}, scenario_result{};
    std::vector<std::vector<int>> votes{};
    std::vector<int> ballot{};
    std::vector<std::vector<std::string>> all_results{};
    std::istringstream iss;
    
    // get # scenarios
    getline(std::cin, temp);
    iss.str(temp);
    iss >> scenarios;
    iss.clear();
        
    // consume blank line
    getline(std::cin, temp);          

    for (int i = 0; i < scenarios; i++) {

        
        // get num candidates
        getline(std::cin, temp);
        iss.str(temp);
        iss >> num_candidates;
        iss.clear();

        // get candidate names
        while(candidate_names.size() < num_candidates) {
            getline(std::cin, temp);
            candidate_names.push_back(temp);
        }

        // get all ballots
        while(getline(std::cin, temp) && !temp.empty()) {
            // get votes from ballot
            iss.str(temp);
            while(iss >> vote) {                
                ballot.push_back(vote);
            } 
            votes.push_back(ballot);

            ballot.clear();
            iss.clear();
        }
        
        // get results
        all_results.push_back(get_results(candidate_names, votes));
        
        // clean up
        candidate_names.clear();
        votes.clear();
    }
    
    // output results
    for (int i = 0; i < all_results.size(); i++) {
        scenario_result = all_results.at(i);
        for (int j = 0; j < scenario_result.size(); j++) {
            std::cout << scenario_result.at(j) << '\n';
        }
        if (i != all_results.size() - 1) {
            std::cout << '\n';
        }
    }
    return 0;
}