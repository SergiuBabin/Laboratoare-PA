#include <bits/stdc++.h>
using namespace std;
/*
 Fie N si K doua numere naturale strict pozitive. Se cere afisarea tuturor
 aranjamentelor de N elemente luate cate K din multimea {1, 2, …, N}.
 */
class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, k;

    void read_input() {
        ifstream fin("in");
        fin >> n >> k;
        fin.close();
    }

    vector<vector<int> > get_result() {
        vector<vector<int> > all;

        /*
        TODO: Construiti toate aranjamentele de N luate cate K ale
        multimii {1, ..., N}.

        Pentru a adauga un nou aranjament:
            vector<int> aranjament;
            all.push_back(aranjament);
        */

        solve_bkt(all);

        return all;
    }

    void solve_bkt(vector< vector<int> > &all) {
        // vectorul in care stochez solutia (partiala) curenta
        vector<int> current;

        // used[i] = 1, daca si numai daca i este deja in solutia curenta
        vector<int> used(n + 1, 0);

        // construiesc aranjamentele prin backtracking
        bkt(current, used, all);
    }

     // Aranjamente de n luate cate k
    void bkt(vector<int> &current,
             vector<int> &used,
             vector< vector<int> > &all) {

        // daca avem o multime de dimensiune k
        if (current.size() == k) {
            // este implicit si un aranjament prin modul cum a fost generata

            // adaug la solutie
            all.push_back(current);

            // ma opresc
            return;
        }

        // current == Aranjament de n luate cate p (p == current.size(), p < k)
        // incerc sa extind (se genereaza in ordine lexico-grafica)
        for (int i = 1; i <= n; ++i) {
            // daca i a fost deja adaugat, il sar
            if (used[i]) {
                continue;
            }

            // Step 1: ADAUG elementul la solutie
            current.push_back(i);
            used[i] = 1;

            // Step 2: COMPLETEZ recursiv si solutia
            bkt(current, used, all);

            // Step 3: Scot elementul din solutie, ca sa pot pune altul in locul lui
            current.pop_back();
            used[i] = 0;
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
