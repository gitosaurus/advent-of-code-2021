#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <valarray>
#include <map>
#include <cmath>

using namespace std;

int main() {
    string line; getline(cin, line);
    transform(line.begin(), line.end(), line.begin(), [](char ch) {return ch == ',' ? ' ' : ch;});
    istringstream ss(line);
    vector<int> crab_hpos;
    copy(istream_iterator<int>(ss), istream_iterator<int>(), back_inserter(crab_hpos));

    valarray<int> orig(&crab_hpos[0], crab_hpos.size());
    int c_begin = orig.min(), c_end = orig.max();
    map<int, int> ranked;
    for (int p = c_begin; p <= c_end; ++p) {
        int diff = (orig - p).apply(abs).sum();
        ranked[diff] = p;
    }
    cout << "Winning position: " << ranked.begin()->second 
         << " using " << ranked.begin()->first << " fuel" << endl;
}
