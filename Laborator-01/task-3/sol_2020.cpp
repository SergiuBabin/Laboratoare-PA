#include <bits/stdc++.h>
using namespace std;
/*
 Gigel are o tabla patratica de dimensiuni 2n∗2n. Ar vrea sa scrie pe patratelele
 tablei numere naturale cuprinse intre 1 si 2n∗2n conform unei parcurgeri mai
 deosebite pe care o numeste Z-parcurgere.

 O Z-parcurgere viziteaza recursiv cele patru cadrane ale tablei in ordinea:
 stanga-sus, dreapta-sus, stanga-jos, dreapta-jos.

 La un moment dat Gigel ar vrea sa stie ce numar de ordine trebuie sa scrie
 conform Z-parcurgerii pe anumite patratele date prin coordonatele lor (x,y).
 Gigel incepe umplerea tablei intotdeauna din coltul din stanga-sus
 */
class Task {
public:
    void solve() {
        read_input();
        print_output(get_result(n, x, y));
    }

private:
    int n, x, y;

    void read_input() {
        ifstream fin("in");
        fin >> n >> x >> y;
        fin.close();
    }

    // (x, y) in dreptunghiul [ (tlx, tly), (drx, dry) ] (top-left-* + down-right * )
    bool in_rectangle(int x, int y, int tlx, int tly, int drx, int dry) {
        return (tlx <= x && x <= drx) && // x intre cele 2 laturi verticale
               (tly <= y && y <= dry);   // y intre cele 2 laturi orizontale
    }

    // caut ce valoarea am pe (x, y), in patratul de dim D, colt stanga sus dat
    // in acest patrat a fost impratiat recursiv sirul: lower, lower + 1, ..., upper
    int helper(int x, int y, int tlx, int tly, int D, int lower, int upper) {
        if (lower == upper) { // D == 1
            return lower;
        }

        // down right
        int drx = tlx + D - 1;
        int dry = tly + D - 1;

        // middle cell
        int mx = (tlx + drx) >> 1;
        int my = (tly + dry) >> 1;

        // in care subdreptunghi se afla x, y?
        // are dimensiune de 2 ori mai mica => D / 2
        // fiecare sumatrice are 1/4 din sirul de numere
        int new_D = (D >> 1);				// D / 2
        int cnt = (upper - lower + 1) >> 2; // (...) / 4

        // 1: este in stanga-sus?
        int new_lower = lower;
        int new_upper = new_lower + cnt - 1;

        // cout << "case 1?\n";
        if (in_rectangle(x, y, tlx, tly, mx, my)) {
            return helper(x, y, tlx, tly, new_D, new_lower, new_upper);
        }

        // 2: este in dreapta-sus?
        new_lower += cnt;
        new_upper += cnt;

        // cout << "case 2?\n";
        if (in_rectangle(x, y, tlx, my + 1, mx, dry)) {
            return helper(x, y, tlx, my + 1, new_D, new_lower, new_upper);
        }

        // 3: este in stanga-jos?
        new_lower += cnt;
        new_upper += cnt;

        // cout << "case 3?\n";
        if (in_rectangle(x, y, mx + 1, tly, drx, my)) {
            return helper(x, y, mx + 1, tly, new_D, new_lower, new_upper);
        }

        // 4: este in dreapta-jos?
        new_lower += cnt;
        new_upper += cnt;

        // cout << "case 4?\n";
        if (in_rectangle(x, y, mx + 1, my + 1, drx, dry)) {
            return helper(x, y, mx + 1, my + 1, new_D, new_lower, new_upper);
        }

        // avem mereu solutie, nu se va ajunge aici
        return -1;
    }

    int solve_rec(int n, int x, int y) {
        int D = (1 << n);
        int lower = 1, upper = D * D;

        return helper(x, y, 1, 1, D, lower, upper);
    }

    int get_result(int n, int x, int y) {
        /*
        TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune
        2^n x 2^n
        */
        return solve_rec(n, x, y);
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
