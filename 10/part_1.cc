#include <iostream>
#include <string>
#include <deque>

using namespace std;

int syntax_score(char ch) {
    switch (ch) {
        case ')': return 3;
        case']': return 57;
        case'}': return 1197;
        case'>': return 25137;
        default: assert(false);
    }
}

char closer(char ch) {
    switch (ch) {
        case'(': return ')';
        case'[': return ']';
        case'{': return '}';
        case'<': return '>';
        default: assert(false);
    }
}

int main() {
    int total_score = 0;
    string line; while (getline(cin, line)) {
        deque<char> stacky;
        bool found_error = false;
        for (auto ch : line) {
            switch (ch) {
                case '(' : case '{' : case '[' : case '<' :
                stacky.push_front(ch);
                break;
                case ')' : case '}' : case ']' : case '>' :
                if (!stacky.empty()) {
                    char match = stacky.front();
                    stacky.pop_front();
                    if (closer(match) != ch) {
                        cout << "Expected " << closer(match)
                            << " but found " << match << " instead." << endl;
                        total_score += syntax_score(ch);
                        found_error = true;
                    }
                }
                break;
                default: assert(false);
            }
            if (found_error) break;
        }
    }
    cout << "Total score: " << total_score << endl;
}
