#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<int> depths;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(depths));
    int count = 0;
    // Prep two sliding windows.
    int w1 = depths[0] + depths[1] + depths[2];
    int w2 = w1 - depths[0] + depths[3];
    count += (w2 > w1);
    for (int i1 = 3, i2 = 4; i2 < depths.size(); ++i1, ++i2) {
        w1 = w1 - depths[i1 - 3] + depths[i1];
        w2 = w2 - depths[i2 - 3] + depths[i2];
        count += (w2 > w1);
    }
    cout << count << endl;
}
