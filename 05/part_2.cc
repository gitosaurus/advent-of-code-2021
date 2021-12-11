#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

typedef pair<int, int> pos;
typedef pair<pos, pos> vent;

ostream& operator<<(ostream& out, const pos& p) {
    out << p.first << ',' << p.second;
    return out;
}

ostream& operator<<(ostream& out, const vent& v) {
    out << v.first << " -> " << v.second;
    return out;
}

// via https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

pos max_pos(0, 0);

pos parse_pos(string word) {
    transform(word.begin(), word.end(), word.begin(), [](char ch) {return ch == ',' ? ' ' : ch;});
    istringstream ss(word);
    int x, y;
    ss >> x >> y;
    max_pos.first = max(max_pos.first, x);
    max_pos.second = max(max_pos.second, y);
    return pos(x, y);
}

vent parse_vent(string line) {
    istringstream ss(line);
    string sp1, arrow, sp2;
    ss >> sp1 >> arrow >> sp2;
    assert(arrow == "->");
    return vent(parse_pos(sp1), parse_pos(sp2));
}

int main() {
    // While reading lines, determine the maximum bounds
    // of the area in which to plot.
    deque<vent> vents;
    string line;
    while (getline(cin, line)) {
        vent v = parse_vent(line);
        vents.push_back(v);
    }
    int rows = max_pos.second + 1;
    int cols = max_pos.first + 1;
    vector<int> seafloor(rows * cols);
    cout << "Size of seafloor: " << max_pos << endl;
    while (!vents.empty()) {
        auto & v = vents.front();
        int xb = v.first.first, xe = v.second.first;
        int yb = v.first.second, ye = v.second.second;
        int xi = sgn(xe - xb), yi = sgn(ye - yb);
        xe += xi; ye += yi;
        // NOTE:  Using || feels odd but covers the fact that for horizontal and vertical
        // carvings, one side of the expression will always be false.
        for (int x = xb, y = yb; x != xe || y != ye; x += xi, y += yi) {
            seafloor[cols * y + x] += 1;
        }
        vents.pop_front();
    }
    cout << "Carving complete." << endl;
    for (int rr = 0; rr < rows; ++rr) {
        for (int cc = 0; cc < cols; ++cc) {
            cout << " ";
            int val = seafloor[cols * rr + cc];
            if (!val) {
                cout << ".";
            } else {
                cout << val;
            }
        }
        cout << endl;
    }
    int over_2 = count_if(seafloor.begin(), seafloor.end(), [](int c){return c >= 2;});
    cout << "Points to avoid: " << over_2 << endl;
}
