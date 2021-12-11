#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    u_long distance = 0, depth = 0, aim = 0;
    string line; while (getline(cin, line)) {
        istringstream in(line);
        string operation;
        int units;
        in >> operation >> units;
        if (operation == "forward") {
            distance += units;
            depth += aim * units;
        } else if (operation == "down") {
            aim += units;
        } else if (operation == "up") {
            aim -= units;
        }
    }
    cout << "Final distance: " << distance << "; depth: " << depth << endl;
    cout << "Answer: " << distance * depth << endl;
}
