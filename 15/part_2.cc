#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#define SHOW(expr) cout << #expr << " == " << (expr) << endl

int rows = 0, cols = 0;
vector<int> risks;

int m(int r, int c) {
    return r * cols + c;
}

void dump(string message) {
    cout << message << endl;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int cursor = risks[m(r, c)];
            cout << cursor;
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // The grid must be expanded 5X in both directions, with
    // the new value of each repeated tile (in each direction) being
    // given as t2 = (t % 9) + 1.
    //
    // It may be easier to do this expansion right at the moment of reading.
    list<vector<int>> row_list;
    string line; while(getline(cin, line)) {
        if (cols) {
            assert(cols == line.size());
        } else {
            cols = line.size();
        }
        vector<int> risk_row(cols * 5);  // pre-size so iterators will be stable
        transform(begin(line), end(line), begin(risk_row), [](int c) { return c - '0'; });
        auto p_beg = begin(risk_row);
        auto p_end = p_beg + line.size();
        for (int s = 1; s < 5; s++) {
            auto next_begin = p_end;
            transform(p_beg, p_end, p_end, [](int t) { return (t % 9) + 1; });
            p_beg = next_begin;
            p_end = p_end + line.size();
        }
        row_list.push_back(risk_row);
        rows++;
    }
    cols *= 5;
    // Now, prepare the whole matrix.  We start with one copy of the rows as they are,
    // and then roll down four times, doing the mod-math to each.
    for (int rrows = 0; rrows < 5; ++rrows) {
        for (int ir = 0; ir < rows; ir++) {
            copy(row_list.front().begin(), row_list.front().end(), back_inserter(risks));
            row_list.push_back(vector<int>(cols));
            transform(row_list.front().begin(), row_list.front().end(),
                        row_list.back().begin(), [](int t) { return (t % 9) + 1; });
            row_list.pop_front();
        }
    }
    rows *= 5;
    dump("After initial input:");
    SHOW(rows);
    SHOW(cols);
    SHOW(risks.size());
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
