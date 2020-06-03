#include <bits/stdc++.h>
using namespace std;
/*
 Consideram 2 localitati A si B aflate la distanta D. Intre cele 2 localitati
 avem un numar de n benzinarii, date prin distanta fata de localitatea A. Masina
 cu care se efectueaza deplasarea intre cele 2 localitati poate parcurge maxim m
 kilometri avand rezervorul plin la inceput. Se doreste parcurgerea drumului cu
 un numar minim de opriri la benzinarii pentru realimentare (dupa fiecare oprire
 la o benzinarie, masina pleaca cu rezervorul plin).

 Distantele catre benzinarii se reprezinta printr-o lista de forma 0<d1<d2<...<dn,
 unde di (1<=i<=n) reprezinta distanta de la A la benzinaria i. Pentru simplitate,
 se considera ca localitatea A se afla la 0, iar dn=D (localitatea B se afla in
 acelasi loc cu ultima benzinarie).

 Se garanteaza ca exista o planificare valida a opririlor astfel incat sa se
 poata ajunge la localitatea B.
 */
class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m;
    vector<int> dist;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;

        dist.push_back(0); // indexare de la 1 => dist[0] == 0 (locatia A)
        for (int i = 1, d; i <= n; i++) {
            fin >> d;
            dist.push_back(d);
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Aflati numarul minim de opriri necesare pentru a ajunge
        la destinatie.
        */

        return gas_station();
    }

    // T = O(n)
    // S = O(1)
    int gas_station() {
        int sol = 0;  // numar minim de opriri
        int fuel = m; // fuel este cantitatea curenta de combustibil din rezervor (a.k.a cat a ramas)

        for (int i = 1; i <= n; ++i) {
            fuel -= (dist[i] - dist[i - 1]); // ma deplasez de la locatia anterioara la cea curenta
                                             // intotdeauna cand ajung intr-o benzinarie ma asigur am suficient
                                             // combustibil sa ajung la urmatoarea - initial pot sa ajung de la A la dist[1]

            // daca nu am ajuns in ultima benziarie
            // verifica daca trebuie sa reincarc (rezervor gol sau cantitate insuficienta pentru a ajunge la benzinaria urmatoare)
            if (i < n && (fuel == 0 || dist[i+1] - dist[i] > fuel)) {
                ++sol;
                fuel = m;
            }
        }

        return sol;
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
