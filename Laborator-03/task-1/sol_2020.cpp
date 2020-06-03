#include <bits/stdc++.h>
using namespace std;
/*
 Gigel are o colectie impresionanta de monede. El ne spune ca are n tipuri de
 monede, avand un numar nelimitat de monede din fiecare tip. Cunoscand aceasta
 informatie (data sub forma unui vector v cu n elemente), el se intreaba care
 este numarul minim de monede cu care poate plati o suma S.

 Task-uri:

 1.1 Determinati numarul minim de monede (din cele pe care le are) cu care Gigel
 poate forma suma S.
 */
class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, S;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n >> S;
        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Aflati numarul minim de monede ce poate fi folosit pentru a obtine
        suma S. Tipurile monedelor sunt stocate in vectorul v, de dimensiune n.
        */
        return coing_change();
    }

    // T = O(n * S)
    // S = O(S)
    int coing_change() {
        const int kInf = 1e9; // presupun ca nu am sume mai mari decat 10^9

        // dp[i] = numarul minim de monede cu care pot forma suma i
        vector<int> dp(S + 1, kInf); // initial am valori foarte mari in dinamica (presupun ca nu se poate forma suma S)
            // in definirea recurentei am spus practic ce mi se cerea in enunt
            // Sesizati? :p

        // cazul de baza: suma 0 nu necesita monede
        dp[0] = 0;

        // cazul general: suma s; s se poate descompune ca s = s1 + s2... cine sunt s1 si s2?
        // 		O varianta simpla: s1 = o moneda (oarecare)
        // s     = c      + (s - c)
        //        1 coin     restul
        // dp[s] =  1     + dp[s-c]
        // 		Revenind la notatii:  i  =     v[j]     + (i - v[j])
        //                         dp[i] = min( 1       + dp[i - v[j]]), j = 1:n
        for (int i = 1; i <= S; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (v[j] <= i) {
                    dp[i] = min(dp[i], dp[i - v[j]] + 1);
                }
            }
        }

        // s-a putut forma suma S? (dp[S] != kInf)
        // DA: dp[S] este numarul minim de monede cu care am format pe S
        // NU: ghinion.. nu se poate forma suma S
        return (dp[S] != kInf ? dp[S] : -1);
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
