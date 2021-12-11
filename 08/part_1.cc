#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <deque>
#include <bitset>

using namespace std;

int main() {
    int how_many_unique = 0;
    string line; while (getline(cin, line)) {
        istringstream ss(line);
        bool seen_delimiter = false;
        while (ss.good()) {
            string word; ss >> word;
            if (word == "|") {
                seen_delimiter = true;
                continue;
            }
            if (seen_delimiter) {
                // Consider only the outputs.
                // Only consider 1, 4, 7, and 8.
                // These have unique segment counts 2, 4, 3, and 7.
                bitset<8> segments;
                for (auto c : word) {
                    segments.set(c - 'a', 1);
                }
                switch (segments.count()) {
                    case 2: case 4: case 3: case 7: how_many_unique++; break;
                }
            }
        }
    }
    cout << "Total count: " << how_many_unique << endl;
}
