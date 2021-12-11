#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<int> depths;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(depths));
    int count = 0;
    for (int i = 1; i < depths.size(); ++i) {
        if (depths[i] > depths[i - 1]) count++;
    }
    cout << count << endl;
}
