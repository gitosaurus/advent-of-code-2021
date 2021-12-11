#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    vector<int> heights;
    int sentinel = numeric_limits<int>::max();
    int rows = 0, cols = 0;
    // A trick:  surround the whole map with a margin.
    // It will need to be the maximum size.
    string line; while(getline(cin, line)) {
        if (cols) {
            assert(cols == line.size());
        } else {
            cols = line.size();
            fill_n(back_inserter(heights), 2 + cols, sentinel);
        }
        rows++;
        heights.push_back(sentinel);
        transform(line.begin(), line.end(), back_inserter(heights), [](int c) {return c - '0';});
        heights.push_back(sentinel);
    }
    fill_n(back_inserter(heights), 2 + cols, sentinel);
    // Now we don't have to worry about bounds-checks.
    // But the indexing operation is not [r * cols + c] anymore,
    // it is [(r + 1) * (cols + 2) + (c + 1)].
    auto m = [&](int r, int c) { return heights[(r + 1) * (cols + 2) + (c + 1)]; };
    int risk_sum = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int cursor = m(r, c);
            if (
                cursor < m(r - 1, c) && cursor < m(r + 1, c) &&
                cursor < m(r, c - 1) && cursor < m(r, c + 1)
            ) {
                cout << "Low point at " << r << ", " << c << ": " << cursor << endl;
                risk_sum += cursor + 1;
            }
        }
    }
    cout << "Total risk: " << risk_sum << endl;
}
