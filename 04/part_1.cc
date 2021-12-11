#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <set>

using namespace std;

class BingoBoard {
public:

    const int rows = 5;
    const int cols = 5;
    const int unread = -1;  // sentinel for ::good

    BingoBoard(istream& in, int id):
    id_(id),
    board_(rows * cols),
    marked_(rows * cols)
    {
        set<int> check;  // just to verify no doubled numbers
        for (int i = 0; i < rows * cols; ++i) {
            int number = unread;
            cin >> number;
            board_[i] = number;
            check.insert(number);
        }
        if (good()) {
            assert(check.size() == board_.size());
        }
    }

    int id() const { return id_; }

    bool good() const {
        return find(board_.begin(), board_.end(), unread) == board_.end();
    }

    int board(int r, int c) const { return board_[r * cols + c]; }

    bool marked(int r, int c) const { return marked_[r * cols + c]; }

    bool mark_called_number(int number) {
        auto it = find(board_.begin(), board_.end(), number);
        if (it == board_.end()) return false;
        *(marked_.begin() + distance(board_.begin(), it)) = true;
        return true;
    }

    bool has_won() const {
        // Check all the rows.
        for (int r = 0; r < rows; ++r) {
            bool m = true;
            for (int c = 0; c < cols; ++c) {
                m = m && marked(r, c);
            }
            if (m) return true;
        }
        // Check all columns.
        for (int c = 0; c < cols; ++c) {
            bool m = true;
            for (int r = 0; r < rows; ++r) {
                m = m && marked(r, c);
            }
            if (m) return true;
        }
        return false;
    }

    int score() const {
        int score = 0;
        for (int i = 0; i < rows * cols; ++i) {
            if (!marked_[i]) score += board_[i];
        }
        return score;
    }

    void write(ostream& out) const {
        out << "Board " << id_ << endl;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (marked(r, c)) {
                    out << "[" << setw(2) << board(r, c) << "] ";
                } else {
                    out << " " << setw(2) << board(r, c) << "  ";
                }
            }
            out << endl;
        }
    }

private:
    int id_;
    vector<int> board_;
    vector<bool> marked_;
};


ostream& operator<< (ostream& out, const BingoBoard& bb) {
    bb.write(out);
    return out;
}


int main() {
    string line;
    getline(cin, line);
    transform(line.begin(), line.end(), line.begin(), [](char ch) {return ch == ',' ? ' ' : ch;});
    list<int> numbers;
    istringstream ss(line);
    copy(istream_iterator<int>(ss), istream_iterator<int>(), back_inserter(numbers));

    list<BingoBoard> boards;
    while (cin) {
        BingoBoard board(cin, boards.size());
        if (board.good()) {
            boards.push_back(board);
            cout << "Board received:" << endl;
            cout << boards.back() << endl;
        }
    }

    int checksum = -1;
    bool winner = false;
    while (!winner && !numbers.empty()) {
        cout << "Calling: " << numbers.front() << endl;
        int called = numbers.front();
        numbers.pop_front();
        for (auto & b : boards) {
            if (b.mark_called_number(called) && b.has_won()) {
                cout << "Board " << b.id() << " has BINGO!" << endl;
                cout << b << endl;
                int score = b.score();
                cout << "Score is " << score << endl;
                checksum = called * score;
                winner = true;
                break;
            }
            cout << b << endl;
        }
    }
    cout << "Game is finished, and the checksum is " << checksum << endl;
}
