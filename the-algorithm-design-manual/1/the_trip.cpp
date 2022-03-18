/////////////
//  The Trip
//  Skiena Programming Challenge 1-2
//  https://onlinejudge.org/ UVA 10137
/////////////
// A number of students are members of a club that travels annually to exotic locations. Their destinations
// in the past have included Indianapolis, Phoenix, Nashville, Philadelphia, San Jose, and Atlanta. This
// spring they are planning a trip to Eindhoven.
// The group agrees in advance to share expenses equally, but it is not practical to have them share
// every expense as it occurs. So individuals in the group pay for particular things, like meals, hotels, taxi
// rides, plane tickets, etc. After the trip, each student’s expenses are tallied and money is exchanged so
// that the net cost to each is the same, to within one cent. In the past, this money exchange has been
// tedious and time consuming. Your job is to compute, from a list of expenses, the minimum amount of
// money that must change hands in order to equalize (within a cent) all the students’ costs.
/////////////
// Input
//
// Standard input will contain the information for several trips. The information for each trip consists of
// a line containing a positive integer, n, the number of students on the trip, followed by n lines of input,
// each containing the amount, in dollars and cents, spent by a student. There are no more than 1000
// students and no student spent more than $10,000.00. A single line containing 0 follows the information
// for the last trip.
/////////////
// Output
//
// For each trip, output a line stating the total amount of money, in dollars and cents, that must be
// exchanged to equalize the students’ costs.
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

float mean(std::vector<float> costs) {
    float sum{0};
    for (int i = 0; i < costs.size(); i++) {
        sum += costs.at(i);
    }
    return sum/costs.size();
}

float get_exchanged_dollars(std::vector<float> costs) {
    float diff, avg{mean(costs)}, money_gotten{0}, money_given{0};

    for (int i = 0; i < costs.size(); i++) {
        // can't transfer fractions of a cent
        //     multipy by 100 to make 100ths place a whole #
        //     then cast to int to drop the decimal
        //     divide again to return dollars and cents
        diff = static_cast<int>((costs.at(i) - avg) * 100.00) / 100.00;
        if (diff >= 0) {
            money_gotten += diff;
        } else {
            money_given += diff;
        }
    }
    // if money_given != money_gotten 
    // it's because somebody's owed a fraction of a cent, 
    // but the problem says not to worry about that
    // in this case some folks will end up with one cent more than the avg
    // and some with one cent less
    return (money_gotten >= -money_given) ? money_gotten : -money_given;
}

int main() {
    int num_ppl;
    float cost;
    std::vector<float> costs, results;
    while((std::cin >> num_ppl) && num_ppl != 0) {
        costs.clear();
        while(costs.size() < num_ppl) {
            std::cin >> cost;
            costs.push_back(cost);
        }
        results.push_back(get_exchanged_dollars(costs));
    }
    for (int i = 0; i < results.size(); i++) {
        std::cout << std::fixed << std::setprecision(2) << "$" << results.at(i);
    }
    return 0;
}