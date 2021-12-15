#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <cctype>

using namespace std;

multimap<string, string> where_to;

bool is_small(string s) { return islower(s[0]); }

void explore(string cave, map<string, int>& visits_left, deque<string>& path, set<string>& paths) {
    if (cave == "end") {
        // Add this path to the list of paths
        ostringstream out;
        copy(path.begin(), path.end(), ostream_iterator<string>(out, ",")); out << cave;
        paths.insert(out.str());
        return;
    }
    // Otherwise, keep going.
    if (is_small(cave)) {
        if (!visits_left[cave]) return;
        visits_left[cave]--;
    }
    path.push_back(cave);
    for (auto it = where_to.lower_bound(cave); it != where_to.upper_bound(cave); ++it) {
        explore(it->second, visits_left, path, paths);
    }
    path.pop_back();
    if (is_small(cave)) {
        visits_left[cave]++;
    }
}

int main() {
    map<string, int> visits_left;
    set<string> small_caves;
    string line; while (getline(cin, line)) {
        transform(line.begin(), line.end(), line.begin(),
                     [](char ch) { return ch != '-' ? ch : ' '; });
        stringstream ss(line);
        string side1, side2; ss >> side1 >> side2;
        where_to.insert(make_pair(side1, side2));
        where_to.insert(make_pair(side2, side1));
        visits_left[side1] = 1;
        visits_left[side2] = 1;
        if (is_small(side1)) small_caves.insert(side1);
        if (is_small(side2)) small_caves.insert(side2);
    }
    deque<string> path; 
    set<string> paths;
    // Give each small cave a chance at having the extra visit.
    // But "start" and "end" can't be part of that!
    auto start = small_caves.find("start");
    auto end = small_caves.find("end");
    small_caves.erase(start);
    small_caves.erase(end);
    for (auto s : small_caves) {
        visits_left[s]++;
        explore("start", visits_left, path, paths);
        visits_left[s]--;
    }
    cout << "All paths:" << endl;
    copy(paths.begin(), paths.end(), ostream_iterator<string>(cout, "\n"));
    cout << "Total paths: " << paths.size() << endl;
}
