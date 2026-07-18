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

struct TestCase {
    vector<int> a;
};

TestCase generate_input() {
    TestCase tc;
    int n = rand_range(1, 100);
    for (int i = 0; i < n; ++i)
        tc.a.push_back(rand_range(1, 1000));
    shuffle(tc.a);
    return tc;
}

int my_solution(const TestCase& tc) {
    // Your optimized solution here
    return 0;
}

int correct_solution(const TestCase& tc) {
    // Brute-force reference solution
    return 0;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    const int T = 1000;
    for (int t = 1; t <= T; ++t) {
        TestCase tc = generate_input();
        int res1 = my_solution(tc);
        int res2 = correct_solution(tc);
        if (res1 != res2) {
            cout << "Test " << t << " failed.\n";
            cout << "Input:\n";
            for (int x : tc.a) cout << x << " ";
            cout << "\nMy output: " << res1 << "\nExpected: " << res2 << "\n";
            return 0;
        }
    }
    cout << "All tests passed.\n";
    return 0;
}