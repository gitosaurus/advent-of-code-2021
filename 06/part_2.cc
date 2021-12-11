#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    int days = 80;
    deque<string> args(argv + 1, argv + argc);
    if (!args.empty()) {
        days = stoi(args.front());
        args.pop_front();
    }
    cout << "Total days in simulation: " << days << endl;
    string line; getline(cin, line);
    transform(line.begin(), line.end(), line.begin(), [](char ch) {return ch == ',' ? ' ' : ch;});
    istringstream ss(line);

    // To keep computational bounds reasonable, group the fish by their
    // age.  We only require 9 bins, one for each fish age.
    // But a 32-bit int won't cut it anymore.
    vector<u_long> fish_ages(9);
    while (ss.good()) {
        int age; ss >> age;
        fish_ages[age]++;
    }
    for (int day = 0; day < days; ++day) {
        // Don't count the 8-day-aged fish when aging the previous.
        // The whole algorithm changes, now:  we're shifting counts
        // in a circle.  What is lost here is the sequence, but that
        // isn't asked for.
        //
        // The counts in the 0-bin increment the 8-bin, for new fish.
        // To reset the zero-ages, the 0-count increments the 6-count.
        u_long fish0 = fish_ages[0];
        for (int a = 1; a < 9; ++a) {
            fish_ages[a - 1] = fish_ages[a];
        }
        fish_ages[8]  = fish0;
        fish_ages[6] += fish0;
        cout << "Day " << setw(2) << day << endl;
        for (int ii = 0; ii < 9; ++ii) {
            if (!fish_ages[ii]) {
                cout << "     ";
            } else {
                cout << ii << ':' << fish_ages[ii] << "  ";
            }
        }
        cout << endl;
    }
    u_long all_fish = accumulate(fish_ages.begin(), fish_ages.end(), u_long(0));
    cout << "Total lantern fish: " << all_fish << endl;
}
