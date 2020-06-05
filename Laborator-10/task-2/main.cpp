#include <bits/stdc++.h>
using namespace std;
/*
 Aceeasi cerinta si aceleasi restrictii ca mai sus, doar ca se cere gasirea
 costului minim al unui arbore de acoperire folosind algoritmul lui Prim.
 */
const int kNmax = 2e5 + 10;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    int m;
    vector<pair<int, int> > adj[kNmax];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Calculati costul minim al unui arbore de acoperire
        folosind algoritmul lui Prim.
        */
        vector<bool> visited(n + 1);
        auto cmp = [](pair<int, int>& x, pair<int, int>& y) {
            return x.second > y.second;
        };
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        visited[1] = true;
        
        for (auto& u : adj[1]) {
            pq.push(u);
        }
        
        int cost = 0;
        while (!pq.empty()) {
            pair<int, int> u = pq.top();
            pq.pop();
            
            if (visited[u.first] != true) {
                visited[u.first] = true;
                cost += u.second;
                
                for(auto& v : adj[u.first]) {
                    if (visited[v.first] != true) {
                        pq.push(v);
                    }
                }
            }
        }
        return cost;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << "\n";
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
