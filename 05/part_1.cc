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
    // In this problem, only worry about horizontal or vertical.
    // But for simplicity later, we want the first position to be less than
    // the second.
    //
    // The ordinary sense of less-than for pairs should be fine.
    pos p1 = parse_pos(sp1);
    pos p2 = parse_pos(sp2);
    if (p1 < p2) {
        return vent(p1, p2);
    } else {
        return vent(p2, p1);
    }
}

int main() {
    // While reading lines, determine the maximum bounds
    // of the area in which to plot.
    deque<vent> vents;
    string line; while (getline(cin, line)) {
        vent v = parse_vent(line);
        vents.push_back(v);
    }
    int rows = max_pos.second + 1;
    int cols = max_pos.first + 1;
    vector<int> seafloor(rows * cols);
    cout << "Size of seafloor: " << max_pos << endl;
    while (!vents.empty()) {
        auto & v = vents.front();
        if (v.first.first == v.second.first) {
            cout << "Carving vertical: " << v << endl;
            // x's are the same, so it's vertical
            int x = v.first.first;
            for (int y = v.first.second; y <= v.second.second; ++y) {
                seafloor[y * cols + x] += 1;
            }
        } else if (v.first.second == v.second.second) {
            cout << "Carving horizontal: " << v << endl;
            // y's are the same, so it's horizontal
            int y = v.first.second;
            for (int x = v.first.first; x <= v.second.first; ++x) {
                seafloor[y * cols + x] += 1;
            }
        } else {
            cout << "Ignoring diagonal: " << v << endl;
        }
        vents.pop_front();
    }
    cout << "Carving complete." << endl;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cout << " ";
            int val = seafloor[r * cols + c];
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
