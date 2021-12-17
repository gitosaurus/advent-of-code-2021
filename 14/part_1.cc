#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    int steps = 10;
    list<string> args(argv + 1, argv + argc);
    if (!args.empty()) {
        steps = stoi(args.front());
        args.pop_front();
    }

    // Get the polymer template.
    string polymer; getline(cin, polymer);
    string line; getline(cin, line);
    assert(line.size() == 0);
    map<string, char> insertions;
    // Load up the insertion table.
    while (getline(cin, line) && line.find("->") != string::npos) {
        istringstream ss(line);
        string pr, arrow, sym; ss >> pr >> arrow >> sym;
        assert(arrow == "->");
        assert(pr.size() == 2);
        assert(sym.size() == 1);
        insertions[pr] = sym[0];
    }
    // Expand the original template into a list.
    list<char> chain;
    copy(polymer.begin(), polymer.end(), back_inserter(chain));
    // Now begin to apply it.
    for (int s = 1; s <= steps; ++s) {
        // Transformation step:  walk through the chain and examine
        // each pair.  If a transformation exists in the insertions,
        // insert it before moving on.
        auto ip1 = chain.begin();
        auto ip2 = ip1;
        ip2++;
        string key = "XX";
        while (ip2 != chain.end()) {
            key[0] = *ip1; key[1] = *ip2;
            auto m = insertions.find(key);
            if (m != insertions.end()) {
                // The new one goes in between, that is, before ip2.
                chain.insert(ip2, m->second);
            }
            // If ip1 advances on its own it will walk into new
            // elements.  So instead it must track ip2's previous value.
            ip1 = ip2++;
        }
        // Display the transform.
        cout << "STEP " << s << ": ";
        copy(chain.begin(), chain.end(), ostream_iterator<char>(cout)); cout << endl;
    }
    // Histogram and find the most and least common elements.
    map<char, int> hist; for (char v : chain) { hist[v]++; }
    set<int> q; for (auto p : hist) {
        cout << p.first << ": " << p.second << endl;
        q.insert(p.second);
    }
    // Find the most and least common elements in the result.
    // What do you get if you take the quantity of the most common element
    // and subtract the quantity of the least common element?
    cout << "Most common: " << *q.rbegin() << endl;
    cout << "Least common: " << *q.begin() << endl;
    cout << "Answer: " << *q.rbegin() - *q.begin() << endl;
}