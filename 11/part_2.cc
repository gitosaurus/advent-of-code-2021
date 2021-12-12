// Dumbo octopuses!
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <deque>
#include <valarray>

using namespace std;

const int rows = 10;
const int cols = 10;

size_t index(int r, int c) {
    return (r + 1) * (cols + 2) + c + 1;
}

void show(int step, const valarray<int>& v) {
    cout << "After step " << step << ':' << endl;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cout << v[index(r, c)] << ' ';
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    // Add a margin so that we don't have to do bounds-checking.
    valarray<int> g((rows + 2) * (cols + 2));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char ch;
            cin >> ch;
            assert(ch >= '0' && ch <= '9');
            g[index(r, c)] = ch - '0';
        }
    }
    show(0, g);

    int total_flashes = 0;
    valarray<size_t> hood(8);
    hood[0] = index(-1, -1);
    hood[1] = index(-1,  0);
    hood[2] = index(-1,  1);
    hood[3] = index( 0, -1);
    hood[4] = index( 0,  1);
    hood[5] = index( 1, -1);
    hood[6] = index( 1,  0);
    hood[7] = index( 1,  1);
    cout << "Neighborhood mask: ";
    copy(begin(hood), end(hood), ostream_iterator<int>(cout, ", ")); cout << endl;
    cout << "Initial cursor is " << index(0, 0) << endl;
    deque<int> all_flashing;
    int s = 0;
    while (all_flashing.empty()) {
        g += 1;
        s++;
        vector<size_t> flashed;
        size_t last_flashes = flashed.size();
        do {
            last_flashes = flashed.size();
            valarray<int> g1 = g;
            // Now, every octopus that went over 9 increases all the ones around it.
            // Create the indirect-index array and slide it.
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    int cursor = index(r, c);
                    if (g1[cursor] > 9) {
                        valarray<size_t> h = hood + (cursor - index(0, 0));
                        // cout << "Indexes to set for " << r << ", " << c << " --> " << cursor << ": ";
                        // copy(begin(h), end(h), ostream_iterator<int>(cout, ", ")); cout << endl;
                        g1[h] = valarray<int>(g1[h]) + 1;
                        g1[cursor] = 0;
                        flashed.push_back(cursor);
                    }
                }
            }
            g = g1;
        } while (flashed.size() > last_flashes);
        cout << flashed.size() << " flashes noted" << endl;
        if (flashed.size() == rows * cols) {
            cout << "All flashing at step " << s << endl;
            all_flashing.push_back(s);
        }
        total_flashes += flashed.size();
        valarray<size_t> tired_octopuses(&flashed[0], flashed.size());
        g[tired_octopuses] = 0;
        show(s, g);
    }
    cout << "Total flashes: " << total_flashes << endl;
    cout << "Steps when all octopuses flashed: ";
    copy(all_flashing.begin(), all_flashing.end(), ostream_iterator<int>(cout, " ")); cout << endl;
}
