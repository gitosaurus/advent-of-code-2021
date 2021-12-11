#include <iostream>
#include <string>
#include <deque>

using namespace std;

// Completion scoring:
// Start with a total score of 0.
// Then, for each character, multiply the total score by 5
// and then increase the total score by the point value given
// for the character in the following table:
int completion_score(char ch) {
    switch (ch) {
        case '(': return 1;
        case '[': return 2;
        case '{': return 3;
        case '<': return 4;
        default: assert(false);
    }
}

char closer(char ch) {
    switch (ch) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        default: assert(false);
    }
}

int main() {
    deque<u_long> scores;
    string line; while (getline(cin, line)) {
        deque<char> stacky;
        bool correct = true;
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
                        correct = false;
                    }
                }
                break;
                default: assert(false);
            }
        }
        if (correct) {
            u_long line_score = 0;
            while (!stacky.empty()) {
                // Finish and complete the line.
                line_score = line_score * 5 + completion_score(stacky.front());
                stacky.pop_front();
            }
            cout << "Line score: " << line_score << endl;
            scores.push_back(line_score);
        }
    }
    // Find the middle score.
    sort(scores.begin(), scores.end());
    cout << "All scores: ";
    copy(scores.begin(), scores.end(), ostream_iterator<u_long>(cout, " "));
    cout << endl;
    int middle = scores.size() / 2;
    cout << "Winning score: " << scores[middle] << endl;
}
