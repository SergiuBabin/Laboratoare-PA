#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    vector<vector<int> > get_result() {
        vector<vector<int> > all;

        /*
        TODO: Construiti toate submultimile multimii {1, ..., N}.

        Pentru a adauga o noua submultime:
            vector<int> submultime;
            all.push_back(submultime);
        */

        solve_sets(all);

        return all;
    }

    void solve_sets(vector< vector<int> > &all) {
        // vectorul in care stochez solutia (partiala) curenta
        vector<int> current;

        // construiesc submultimile prin backtracking
        bkt(current, all);
    }

    // Submultimile unei multimi cu n elemente
    void bkt(vector<int> &current,
             vector< vector<int> > &all) {

        // Orice current este implicit si o submultime prin modul cum a fost generat

        // adaug la solutie
        all.push_back(current);

        // ma opresc daca am ajung la lungime maxima
        if (current.size() == n) {
            return;
        }

        // current == Submultime
        // incerc sa extind (se genereaza in ordine lexico-grafica)
        int i_min = (current.size() == 0 ? 0 : current.back());
        for (int i = i_min + 1; i <= n; ++i) {
            // Step 1: ADAUG elementul la solutie
            current.push_back(i);

            // Step 2: COMPLETEZ recursiv si solutia
            bkt(current, all);

            // Step 3: Scot elementul din solutie, ca sa pot pune altul in locul lui
            current.pop_back();
        }
    }

    void print_output(vector<vector<int> > result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (int i = 0; i < (int)result.size(); i++) {
            for (int j = 0; j < (int)result[i].size(); j++) {
                fout << result[i][j] <<
                    (j + 1 != result[i].size() ? ' ' : '\n');
            }
        }
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
