#include <bits/stdc++.h>
using namespace std;
/*
 Se da un graf neorientat conex cu n noduri si m muchii. Se cere sa se gaseaca
 toate muchiile critice.
 
 Like Algoritmul lui Tarjan
 */
const int kNmax = 100005;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    struct Edge {
        int x;
        int y;

        Edge() {}
        Edge(int x, int y) : x(x), y(y) {}
    };


    // n = numar de noduri, m = numar de muchii
    int n, m;

    // adj[node] lista de adiacenta a nodului node pentru graful initial
    vector<int> adj[kNmax];

    // ordinea de vizitare
    // found[node] = timpul de start a lui node in parcurgerea DFS
    // in laborator found se numeste idx
    vector<int> found;

    // low_link[node] = min { found[x] | x este accesibil din node }
    // adica timpul minim al unui nou
    vector<int> low_link;

    // vector in care retin muchiile critice (puntile)
    vector<Edge> critical_edges;

    // parent[i] = parintele nodului i
    vector<int> parent;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    vector<Edge> get_result() {
        /*
        TODO: Gasiti muchiile critice ale grafului neorientat stocat cu liste
        de adiacenta in adj.
        */

        tarjan();

        return critical_edges;
    }

    void tarjan() {
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, 0);
        parent = vector<int>(n + 1, 0);

        // momentul curent de start
        // pe masura ce vizita nodurile el va creste (++)
        int current_start = 0;

        for (int i = 1; i <= n; ++i) {
            if (found[i] == -1) {
                // acest nod nu a fost descoperit, deci il putem folosi
                // marcam nodul i ca fiind radacina
                parent[i] = 0;

                // pornim o noua cautare din nodul respectiv
                dfs(i, current_start);
            }
        }
    }

      void dfs(int node, int &current_start) {
        // incep un nou nod, deci un nod timp de start
        ++current_start;

        // atat found, cat si low_link vor primi valoarea lui current_start
        found[node] = current_start;
        low_link[node] = current_start;

        // initializez numarul de copii al nodului curent cu 0
        int children = 0;

        for (auto &vecin : adj[node]) {
            if (found[vecin] == -1) { // deci il pot vizita
                // parintele nodului in care ma duc este chiar nodul curent
                parent[vecin] = node;

                // cresc numarul de copii
                ++children;

                // pornesc un nou dfs
                dfs(vecin, current_start);

                // updatez low_link:
                // - low_link[node]  = timpul de start cel mai mic pe care NODE  il
                // cunoaste
                // - low_link[vecin] = timpul de start cel mai mic pe care VECIN il
                // cunoaste
                // Tot ce acceseaza vecin (Ex. vecin - ... - x) poate accesa si node
                // (ex. node - vecin - ... - x)
                low_link[node] = std::min(low_link[node], low_link[vecin]);

                // daca nu au existat muchii de intoarcere spre node sau spre un parinte
                // al lui node
                // inseamna ca muchia (node, vecin) este muchie critica
                if (low_link[vecin] > found[node]) {
                    critical_edges.push_back(Edge(node, vecin));
                }
            } else {
                // !!!graful fiind neorientat as updata fiecare copil in functie de
                // parintele sau
                // trebuie sa am grija sa nu fac asta
                if (vecin != parent[node]) {
                    // am gasit o muchie de intoarcere
                    low_link[node] = std::min(low_link[node], found[vecin]);
                }
            }
        }
      }

    void print_output(const vector<Edge>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (int i = 0; i < int(result.size()); i++) {
            fout << result[i].x << ' ' << result[i].y << '\n';
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
