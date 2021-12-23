#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define SHOW(expr) cout << #expr << " == " << (expr) << endl

int rows = 0, cols = 0;
vector<int> risks;

int m(int r, int c) {
    return r * cols + c;
}

int main() {
    string line; while(getline(cin, line)) {
        if (cols) {
            assert(cols == line.size());
        } else {
            cols = line.size();
        }
        rows++;
        transform(line.begin(), line.end(), back_inserter(risks), [](int c) {return c - '0';});
    }
    SHOW(rows);
    SHOW(cols);
    assert(rows == cols);
    vector<int> nr = risks;
    int iteration = 0;
    bool changed; do {
        changed = false;
        for (int xr = 0; xr < rows; xr++) {
            for (int xc = 0; xc < cols; xc++) {
                if (xr == 0  &&  xc == 0) continue;
                int least_next = numeric_limits<int>::max();
                if (xr > 0) least_next = min(least_next, nr[m(xr - 1, xc)]);
                if (xc > 0) least_next = min(least_next, nr[m(xr, xc - 1)]);
                if (xr < rows - 1) least_next = min(least_next, nr[m(xr + 1, xc)]);
                if (xc < cols - 1) least_next = min(least_next, nr[m(xr, xc + 1)]);
                int next_value = risks[m(xr, xc)] + least_next;
                if (next_value != nr[m(xr, xc)]) {
                    nr[m(xr, xc)] = next_value;
                    changed = true;
                }
            }
        }
        cout << "Completed iteration " << ++iteration << endl;
    } while (changed);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << setw(3) << nr[m(r, c)];
        }
        cout << endl;
    }
    cout << endl;
    cout << "Lowest risk at end: " << nr[m(rows - 1, cols - 1)] - risks[m(0, 0)] << endl;
}