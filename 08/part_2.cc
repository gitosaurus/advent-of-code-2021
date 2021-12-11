#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <deque>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

bitset<8> word_to_bits(string word) {
    bitset<8> segments;
    for (auto c : word) {
        segments.set(c - 'a', 1);
    }
    return segments;
}

int main() {
    int all_readouts = 0;
    string line; while (getline(cin, line)) {
        istringstream ss(line);
        bool seen_delimiter = false;
        deque<u_long> p5, p6;
        vector<int> segments(10, 0);
        long total_readout = 0;
        while (ss.good()) {
            string word; ss >> word;
            if (word == "|") {
                seen_delimiter = true;
                // Time to solve the puzzle of the digits.
                // 1, 4, 7, and 8 will have been set.  All that remains are the
                // 5-segment and 6-segment groups.
                // Determine the 9 from the 3 6-segments groups, using 1 and 4.
                for (u_long b : p6) {
                    if ((segments[1] & b) != segments[1]) {
                        segments[6] = b;
                    } else if ((segments[4] & b) == segments[4]) {
                        segments[9] = b;
                    } else {
                        segments[0] = b;
                    }
                }
                // Determine the 5s group using the 1 and the 9.
                for (u_long b: p5) {
                    if ((segments[1] & b) == segments[1]) {
                        segments[3] = b;
                    } else if ((b & segments[9]) == b) {
                        segments[5] = b;
                    } else {
                        segments[2] = b;
                    }
                }
                cout << "Decoded:" << endl;
                for (int digit = 0; digit <= 9; ++digit) {
                    cout << digit << ": " << bitset<8>(segments[digit]) << endl;
                }
                continue;
            }
            if (!seen_delimiter) {
                bitset<8> bs = word_to_bits(word);
                cout << bs << ' ';
                u_long bval = bs.to_ulong();
                switch (bs.count()) {
                    case 2: segments[1] = bval; break;
                    case 4: segments[4] = bval; break;
                    case 3: segments[7] = bval; break;
                    case 7: segments[8] = bval; break;
                    case 5: p5.push_back(bval); break;
                    case 6: p6.push_back(bval); break;
                    default: assert(false);
                }
            }
            if (seen_delimiter) {
                bitset<8> bs = word_to_bits(word);
                cout << bs << ' ';
                u_long readout = bs.to_ulong();
                auto where = find(segments.begin(), segments.end(), readout);
                if (where == segments.end()) assert(false);
                int digit = distance(segments.begin(), where);
                cout << "[" << digit << "] ";
                total_readout = total_readout * 10 + digit;
            }
        }
        cout << endl;
        cout << "Readout value: " << total_readout << endl;
        all_readouts += total_readout;
    }
    cout << "Sum of all readouts: " << all_readouts << endl;
}
