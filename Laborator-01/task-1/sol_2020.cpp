#include <bits/stdc++.h>
using namespace std;
 /*
 Se da un sir sortat v cu n elemente. Gasiti numarul de elemente egale cu x
 din sir.
 */
class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, x;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, e; i < n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin >> x;
        fin.close();
    }

    int find_first() {
        /*
        TODO: Cautati prima pozitie pe care se afla valoarea x
        In cazul in care x nu apare in sir, returnati -1
        */
        int left = 0, right = n - 1, mid, res = -1;
        while (left <= right) {
            mid = (left + right) / 2;
            if (v[mid] >= x) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return res;
    }

    int find_last() {
        /*
        TODO: Cautati ultima pozitie pe care se afla valoarea x
        In cazul in care x nu apare in sir, returnati -1
        */
        int left = 0, right = n - 1, mid, res = -1;
        while (left <= right) {
            mid = (left + right) / 2;
            if (v[mid] <= x) {
                res = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return res;
    }

    int get_result() {
        // TODO: Calculati numarul de aparitii ale lui x in vectorul v
        int first = find_first();
        int last = find_last();
        if (first == -1 || last == -1) {
            return 0;
        }
        return last - first + 1;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
        fout.close();
    }
};

// Please always keep this simple main function!
int main() {
    // Allocate a Task object on heap in order to be able to
    // declare huge static-allocated data structures inside the class.
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
