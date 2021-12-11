#include <iostream>
#include <vector>
#include <bitset>
#include <limits>

using namespace std;

int main() {
    int linecount = 0;
    vector<int> onesums;
    string line; while (getline(cin, line)) {
        linecount += 1;
        onesums.resize(line.size(), 0);
        for (int i = 0; i < line.size(); ++i) {
            onesums[i] += line[i] == '1';
        }
    }
    const int bitwidth = sizeof(int) * 8;
    bitset<bitwidth> gamma, epsilon;
    // Careful, the rightmost part of onesums is the least significant bit
    int bit = 0;
    for (auto s = onesums.rbegin(); s != onesums.rend(); ++s, ++bit) {
        gamma[bit] = (*s > (linecount / 2));
        epsilon[bit] = (*s < (linecount / 2));
    }
    cout << "gamma: " << gamma << "; epsilon: " << epsilon << endl;
    cout << "Answer: " << gamma.to_ulong() * epsilon.to_ulong() << endl;
}
