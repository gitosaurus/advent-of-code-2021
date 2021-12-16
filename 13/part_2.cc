#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <deque>
#include <valarray>

using namespace std;

void dump(const valarray<int>& p, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cout << (p[r * cols + c] > 0 ? '#' : '.');
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int rows, cols;
    valarray<int> paper;
    // Have to collect the coordinates first to know how to size the array.
    deque<int> xpts, ypts;
    string line; while(getline(cin, line) && !line.empty()) {
        transform(line.begin(), line.end(), line.begin(), [](char ch) { return ch == ',' ? ' ' : ch; });
        istringstream ss(line);
        int x, y; ss >> x >> y; xpts.push_back(x); ypts.push_back(y);
    }
    cols = *max_element(xpts.begin(), xpts.end()) + 1;
    rows = *max_element(ypts.begin(), ypts.end()) + 1;
    cout << rows << " rows and " << cols << " cols" << endl;
    paper = valarray<int>(rows * cols);
    while (!xpts.empty() && !ypts.empty()) {
        cout << "Setting (" << xpts.front() << ", " << ypts.front() << ")" << endl;
        paper[ypts.front() * cols + xpts.front()] = 1;
        xpts.pop_front(); ypts.pop_front();
    }
    // dump(paper, rows, cols);
    // Read the fold instructions.
    while(getline(cin, line)) {
        string fold = "fold along ";
        assert(line.substr(0, fold.size()) == fold);
        string instruction = line.substr(fold.size(), string::npos);
        char axis = instruction[0];
        int where = stoi(instruction.substr(2, string::npos));
        cout << "fold along " << axis << " = " << where << endl;
        int lit = count_if(begin(paper), end(paper), [](int x) { return x > 0; });
        cout << "There are " << lit << " lit pixels" << endl;

        if (axis == 'y') {
            assert(where == rows / 2);
            valarray<int> p2(where * cols);
            // Skip the fold line itself.
            int up = where;
            int dn = where;
            while (up-- >= 0 && ++dn < rows) {
                p2[slice(up * cols, cols, 1)] =
                    valarray<int>(paper[slice(up * cols, cols, 1)]) +
                    valarray<int>(paper[slice(dn * cols, cols, 1)]);
            }
            // Now throw away everything below the original fold
            rows = where;
            paper = p2;
        } else {
            assert(where == cols / 2);
            valarray<int> p2(rows * where);
            // Skip the fold line itself.
            int left = where;
            int right = where;
            while (left-- >= 0 && ++right < cols) {
                cout << "left: " << left << "; right: " << right << endl;
                p2[slice(left, rows, where)] =
                    valarray<int>(paper[slice(left,  rows, cols)]) +
                    valarray<int>(paper[slice(right, rows, cols)]);
            }
            // Now throw away everything to the right of the original fold.
            cols = where;
            paper = p2;
        }
        cout << "Fold complete." << endl;
        // dump(paper, rows, cols);
        lit = count_if(begin(paper), end(paper), [](int x) { return x > 0; });
        cout << "There are now " << lit << " lit pixels" << endl;
    }
    dump(paper, rows, cols);
}
