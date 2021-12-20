#include <iostream>
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

    // Idea:  "ripple out" from the upper left, replacing subsections of
    // the grid with the lowest-risk paths to the edge squares.  It's a form
    // of memoizing.  And there's no recursion required or anything.  It IS
    // like CA, on an expanding edge.
    //
    // Except that each new edge is the minimum of its horizontal and vertical
    // neighbors.
    assert(rows == cols);
    for (int xr = 1, xc = 1; xr < rows && xc < cols; xr++, xc++) {
        // The outermost edges can ONLY be minimum in one direction.
        // Topmost edge extension:
        risks[m(0, xc)] = risks[m(0, xc)] + risks[m(0, xc - 1)];
        // Leftmost edge extension:
        risks[m(xr, 0)] = risks[m(xc, 0)] + risks[m(xr - 1, 0)];

        // Propagate non-top vertical edge, xc.
        for (int ir = 1; ir < xr; ir++) {
            risks[m(ir, xc)] =
                risks[m(ir, xc)] + min(risks[m(ir, xc - 1)], risks[m(ir - 1, xc)]);
        }
        // Propagate non-left horizontal edge, xr.
        for (int ic = 1; ic < xc; ic++) {
            risks[m(xr, ic)] =
                risks[m(xr, ic)] + min(risks[m(xr, ic - 1)], risks[m(xr - 1, ic)]);
        }
        // New corner:
        risks[m(xr, xc)] = risks[m(xr, xc)] + min(risks[m(xr, xc - 1)], risks[m(xr - 1, xc)]);
    }
    cout << "Lowest risk at end: " << risks[m(rows - 1, cols - 1)] - risks[m(0, 0)] << endl;
}