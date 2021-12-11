#include <iostream>
#include <iterator>
#include <vector>
#include <bitset>
#include <limits>
#include <string>
#include <algorithm>

using namespace std;

typedef vector<string> strings;

template <typename Tin, typename Comparator>
int find_reading(Tin begin, Tin end, Comparator cmp) {
    int size_0 = begin->size();
    for (int cursor = 0; distance(begin, end) > 1 && cursor < size_0; cursor++) {
        Tin it = partition(begin, end, [cursor](string s) { return s[cursor] == '1'; });
        (cmp(distance(begin, it), distance(it, end)) ? end : begin) = it;
    }
    copy(begin, end, ostream_iterator<string>(cout, "\n"));
    // Pick only the first (assuming there's only one to pick)
    const int bitwidth = sizeof(int) * 8;
    bitset<bitwidth> reading(*begin);
    auto readout = reading.to_ulong();
    cout << "Reading: " << readout << endl;
    return readout;
}

int main() {
    // Both values are located using a similar process that involves filtering
    // out values until only one remains. Before searching for either rating value,
    // start with the full list of binary numbers from your diagnostic report
    // and consider just the first bit of those numbers.
    strings bs; copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(bs));

    auto size_0 = bs[0].size();
    for (auto i = bs.begin(); i != bs.end(); ++i) {
        assert(i->size() == size_0);
    }
    // Using `less` and not `less_equal` for the CO2 reading, since the instructions
    // are to choose `0` there in case of a tie, and `0` will be sorted to the bottom,
    // always.
    int  o2_reading = find_reading(bs.begin(), bs.end(), greater_equal<size_t>());
    int co2_reading = find_reading(bs.begin(), bs.end(), less<size_t>());
    cout << "Answer: " << o2_reading * co2_reading << endl;
}
