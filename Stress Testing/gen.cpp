#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rand_range(ll l, ll r) { return l + (ull) rng() % (r - l + 1); }
void shuffle(vector<int> &v) { shuffle(v.begin(), v.end(), rng); }
char rand_char() { return 'a' + rand_range(0, 25); }

string rand_string(int len) {
    string s;
    for (int i = 0; i < len; ++i)
        s += rand_char();
    return s;
}

vector<int> rand_permutation(int n) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    shuffle(v);
    return v;
}

vector<int> rand_vector(int n, int l, int r) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        v[i] = rand_range(l, r);
    return v;
}

vector<pair<int, int>> rand_graph(int n, int m, bool directed = false) {
    set<pair<int, int>> edges;
    while ((int)edges.size() < m) {
        int u = rand_range(1, n);
        int v = rand_range(1, n);
        if (u == v) continue;
        if (!directed && u > v) swap(u, v);
        edges.emplace(u, v);
    }
    return vector<pair<int, int>>(edges.begin(), edges.end());
}

int main(int argc, char* argv[]) {
    if (argc > 1) rng.seed(atoll(argv[1])); // ./gen 5 -> same test every time; ./gen -> random
    // Pair-sum example input. Change main for a different problem.
    const int n = rand_range(1, 8);
    const auto values = rand_vector(n, -2, 2);

    cout << n << ' ' << rand_range(-4, 4) << '\n';
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << ' ';
        cout << values[i];
    }
    cout << '\n';
}
