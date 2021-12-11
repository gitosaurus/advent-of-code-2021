#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <list>
#include <deque>
#include <string>
#include <algorithm>

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
    list<int> fish, newfish;
    copy(istream_iterator<int>(ss), istream_iterator<int>(), back_inserter(fish));

    for (int day = 0; day < days; ++day) {
        for (auto f = fish.begin(); f != fish.end(); ++f) {
            if ((*f)-- == 0) {
                *f = 6;
                newfish.push_back(8);
            }
        }
        fish.splice(fish.end(), newfish);
        cout << "Day " << setw(2) << day << endl;
        copy(fish.begin(), fish.end(), ostream_iterator<int>(cout, ",")); cout << endl;
    }
    // Beware, this is O(N) for list.
    cout << "Total lantern fish: " << fish.size() << endl;
}
