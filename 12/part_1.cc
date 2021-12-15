#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <map>
#include <deque>
#include <set>
#include <cctype>

using namespace std;

multimap<string, string> where_to;

bool is_small(string s) { return islower(s[0]); }

void explore(string cave, set<string>& visited, deque<string>& path, deque<string>& paths) {
    if (cave == "end") {
        // Add this path to the list of paths
        ostringstream out;
        copy(path.begin(), path.end(), ostream_iterator<string>(out, ",")); out << cave;
        paths.push_back(out.str());
        return;
    }
    // Otherwise, keep going.
    if (is_small(cave)) {
        if (visited.count(cave)) return;
        visited.insert(cave);
    }
    path.push_back(cave);
    for (auto it = where_to.lower_bound(cave); it != where_to.upper_bound(cave); ++it) {
        explore(it->second, visited, path, paths);
    }
    path.pop_back();
    auto iv = visited.find(cave);
    if (iv != visited.end()) visited.erase(iv);
}

int main() {
    string line; while (getline(cin, line)) {
        transform(line.begin(), line.end(), line.begin(),
                     [](char ch) { return ch != '-' ? ch : ' '; });
        stringstream ss(line);
        string side1, side2; ss >> side1 >> side2;
        where_to.insert(make_pair(side1, side2));
        where_to.insert(make_pair(side2, side1));
    }
    set<string> visited;
    deque<string> path; 
    deque<string> paths;
    explore("start", visited, path, paths);
    cout << "All paths:" << endl;
    copy(paths.begin(), paths.end(), ostream_iterator<string>(cout, "\n"));
    cout << "Total paths: " << paths.size() << endl;
}
