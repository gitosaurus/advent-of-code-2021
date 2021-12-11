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
    string line; getline(cin, line);
    transform(line.begin(), line.end(), line.begin(), [](char ch) {return ch == ',' ? ' ' : ch;});
    istringstream ss(line);
    list<int> numbers; copy(istream_iterator<int>(ss), istream_iterator<int>(), back_inserter(numbers));

    list<BingoBoard> boards;
    while (cin) {
        BingoBoard board(cin, boards.size());
        if (board.good()) {
            boards.push_back(board);
            cout << "Board received:" << endl;
            cout << boards.back() << endl;
        }
    }

    list<BingoBoard> winners;
    int last_checksum = -1;
    while (!numbers.empty() && !boards.empty()) {
        cout << "Calling: " << numbers.front() << endl;
        int called = numbers.front();
        numbers.pop_front();
        auto ib = boards.begin();
        while (ib != boards.end()) {
            cout << *ib << endl;
            if (ib->mark_called_number(called) && ib->has_won()) {
                cout << "Board " << ib->id() << " has BINGO!" << endl;
                last_checksum = ib->score() * called;
                winners.splice(winners.end(), boards, ib++);
            } else {
                ib++;
            }
        }
    }

    cout << "No more bingo to play!" << endl;
    cout << "Now who was our last winner?" << endl;
    cout << "Last winner: " << winners.back().id() << endl;
    cout << winners.back() << endl;
    cout << "Score: " << winners.back().score() << endl;
    cout << "Checksum: " << last_checksum << endl;
}
