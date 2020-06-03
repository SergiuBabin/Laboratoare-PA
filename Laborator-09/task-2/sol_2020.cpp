#include <bits/stdc++.h>
using namespace std;
/*
 Se da un graf orientat conex cu n noduri si m arce. Graful are pe arce costuri
 pozitive sau negative.

 Folositi Bellman-Ford pentru a gasi costul minim (lungimea minima) a unui drum
 de la o sursa data (source) la toate celelalte n - 1 noduri din graf. In caz ca
 se va detecta un ciclu de cost negativ, se va semnala acest lucru.

 Costul / lungimea unui drum este suma costurilor/lungimilor arcelor care compun
 drumul.
 */
const int kNmax = 50005;
const int kInf = 0x3f3f3f3f;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    int m;
    int source;
    vector<pair<int, int> > adj[kNmax];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m >> source;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back(make_pair(y, w));
        }
        fin.close();
    }

    vector<int> get_result() {
        /*
        TODO: Gasiti distantele minime de la nodul source la celelalte noduri
        folosind BellmanFord pe graful orientat cu n noduri, m arce stocat in adj.
            d[node] = costul minim / lungimea minima a unui drum de la source la nodul
        node;
            d[source] = 0;
            d[node] = -1, daca nu se poate ajunge de la source la node.

        Atentie:
        O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
            adj[x][i].first = nodul adiacent lui x,
            adj[x][i].second = costul.

        In cazul in care exista ciclu de cost negativ, returnati un vector gol:
            return vector<int>();
        */
        vector<int> d(n + 1, 0);

        if (!bellman(source, d))
            // cicu
            return {}; 

        return d;
    }

    bool bellman(int souce, std::vector<int>& d) {
        // Initializam vectorul de distante cu distante infinite.
        std::fill(d.begin(), d.end(), kInf);

        // Setez sursa la distanta 0.
		d[source] = 0;

		// Construiesc un vector de muchii.
		std::vector<std::tuple<int, int, int>> edges;

		for (int x = 1; x <= n; ++x) {
			for (const auto& yc : adj[x]) {
				int y = yc.first;
				int c = yc.second;
				edges.push_back({ x, y, c });
			}
		}

		// Fac N - 1 relaxari.
		for (int i = 1; i <= n - 1; i++) {
			// Parcurg toate muchiile:
			for (const auto& edge : edges) {
				int x = std::get<0>(edge);
				int y = std::get<1>(edge);
				int c = std::get<2>(edge);

				// Incerc sa updatez distanta.
				if (d[y] > d[x] + c) {
					d[y] = d[x] + c;
                }
			}
		}

		// Verific daca mai poate fi updatata distanta
        for (const auto& edge : edges) {
            int x = std::get<0>(edge);
            int y = std::get<1>(edge);
            int c = std::get<2>(edge);

            // Incerc sa updatez distanta.
            if (d[y] > d[x] + c) {
                // Am gasit ciclu.
                return false;
            }
        }

		// Toate nodurile catre care distanta este inca kInf nu pot fi atinse din
		// nodul source, deci le setam pe -1.
		for (int i = 1; i <= n; i++) {
			if (d[i] == kInf) {
                d[i] = -1;
            }
        }

		return true;
    }

    void print_output(vector<int> result) {
        ofstream fout("out");
        if (result.size() == 0) {
            fout << "Ciclu negativ!\n";
        } else {
            for (int i = 1; i <= n; i++) {
                fout << result[i] << ' ';
            }
            fout << '\n';
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
