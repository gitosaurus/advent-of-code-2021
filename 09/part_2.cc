#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>

using namespace std;

// Locations of height 9 do not count as being in any basin, and all
// other locations will always be part of exactly one basin.  The size
// of a basin is the number of locations within the basin, including
// the low point.

int sentinel = 9;  // big enough, since 9 is never part of a basin.
int rows = 0, cols = 0;
vector<int> heights;

// Now we don't have to worry about bounds-checks.
// But the indexing operation is not [r * cols + c] anymore,
// it is [(r + 1) * (cols + 2) + (c + 1)].
int m(int r, int c) {
    return heights[(r + 1) * (cols + 2) + (c + 1)];
}

void m_set(int r, int c, int value) {
    heights[(r + 1) * (cols + 2) + (c + 1)] = value;
}

// Function to count up all the steps in a given direction, as long as
// they're rising.
int path(int r, int c) {
    int cursor = m(r, c);
    if (cursor == sentinel) return 0;
    int sum = 1;            // count ourselves
    m_set(r, c, sentinel);  // and don't double-count!
    // Check all four directions.
    if (m(r - 1, c) > cursor) sum += path(r - 1, c);
    if (m(r + 1, c) > cursor) sum += path(r + 1, c);
    if (m(r, c - 1) > cursor) sum += path(r, c - 1);
    if (m(r, c + 1) > cursor) sum += path(r, c + 1);
    return sum;
};

int main() {
    // A trick:  surround the whole map with a margin.
    // It will need to be the sentinel.
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
    multiset<int> basins;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int cursor = m(r, c);
            if (
                cursor < m(r - 1, c) && cursor < m(r + 1, c) &&
                cursor < m(r, c - 1) && cursor < m(r, c + 1)
            ) {
                cout << "Low point at " << r << ", " << c << ": " << cursor << endl;
                basins.insert(path(r, c));
            }
        }
    }
    // Multiply the size of the three largest basins.
    cout << "All the basins: ";
    copy(basins.begin(), basins.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // multiset is sorted, so the largest are at the end.
    auto b_end = basins.rbegin(); advance(b_end, 3);
    int answer = accumulate(basins.rbegin(), b_end, 1, multiplies<int>());
    cout << "Answer: " << answer << endl;
}
