#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <map>
#include <list>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    int steps = 40;
    list<string> args(argv + 1, argv + argc);
    if (!args.empty()) {
        steps = stoi(args.front());
        args.pop_front();
    }

    // Get the polymer template.
    string polymer; getline(cin, polymer);
    string line; getline(cin, line);
    assert(line.size() == 0);
    map<string, pair<string, string>> insertions;
    // Load up the insertion table.
    while (getline(cin, line) && line.find("->") != string::npos) {
        istringstream ss(line);
        string pr, arrow, sym; ss >> pr >> arrow >> sym;
        assert(arrow == "->");
        assert(pr.size() == 2);
        assert(sym.size() == 1);
        // Okay, blowing memory and burning time with the old approach.
        // Thing is, we don't have arbitrary match sequences:  only pairs,
        // and only the pairs in the insertion table matter.
        //
        // Thus, we only need pair counts, and when adding an element
        // "in between", we increase the pair count on either side.
        // In other words, CB -> H really means:
        // CB -> CH++; HB++.
        // So encode the insertion table that way.
        string lp = "XX", rp = "XX";
        lp[0] = pr[0]; lp[1] = sym[0];
        rp[0] = sym[0]; rp[1] = pr[1];
        cout << pr << " -> " << lp << ", " << rp << endl;
        insertions[pr] = make_pair(lp, rp);
    }
    // The other consequence of this counter approach is that it's hard
    // to count individual symbols.  So we'll keep that sum ourselves.
    map<char, u_long> hist;
    map<string, u_long> chain;
    hist[polymer[0]]++;
    for (int ii = 1; ii < polymer.size(); ++ii) {
        hist[polymer[ii]]++;
        string key = "XX";
        key[0] = polymer[ii - 1];
        key[1] = polymer[ii];
        cout << "Increasing pair " << key << endl;
        chain[key]++;
    }
    // Now begin to apply it.
    for (int s = 1; s <= steps; ++s) {
        cout << "STEP " << s << endl;
        // Transformation step:  walk through the chain and examine
        // each pair.  If a transformation exists in the insertions,
        // insert it before moving on.
        //
        // Now that the chain is implicit, we can't walk it directly.
        // Nor we can we display it, since we've lost the sequence.
        // Instead, we must visit all of the counted pairs.
        // But since they apply all at once, we have to update a
        // next-generation set of counts.
        auto c2 = chain;
        for (auto p : chain) {
            // See if the pair has an insertion.
            auto t = insertions.find(p.first);
            if (t != insertions.end()) {
                // Apply the insertion, which should be easy, since
                // the insertion actually tells us which pairs to
                // increment.  But it can't only be up by one:  this is
                // a count.
                //
                // There's one new symbol going in, but it's once for
                // each time the key (p.first) appears in the chain, which
                // is p.second.
                u_long productions = p.second;
                cout << "There will be " << productions << " productions of " << p.first << endl;
                c2[t->second.first] += productions;
                c2[t->second.second] += productions;
                // AND there are links that are broken!  In a sequence like NN -> C,
                // there's now NCN, so NC and CN both increment.  But NN must decrement by
                // the same number of productions.
                cout << "And losing " << productions << " instances of " << p.first << endl;
                c2[p.first] -= productions;
                // Keep up the element count, too.
                // The new insertion is the leftside of t->second.second,
                // or the rightside of t->second.first.
                assert(t->second.first[1] == t->second.second[0]);
                char new_symbol = t->second.second[0];
                // But how much to increment?  By the number of productions,
                // which will be the production count.
                hist[new_symbol] += productions;
                cout << new_symbol << " up to " << hist[new_symbol] << endl;
            }
        }
        chain = c2;
    }
    set<u_long> q; for (auto p : hist) {
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