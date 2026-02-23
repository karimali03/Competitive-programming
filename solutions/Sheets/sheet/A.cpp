#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXA = 50005;
const int MAXN = 200005;
const int MAXPF = 8; // unique prime factors per number (for <= 5e4 this is small)
const int MAXE = MAXN * MAXPF;

int spf[MAXA + 5];
int a[MAXN];
int pf[MAXN][MAXPF];
int pfCnt[MAXN];
int allPrimes[MAXE];

int headL[MAXN], toE[MAXE], nxtE[MAXE], edgeCnt;
int matchL[MAXN], matchR[MAXN], distL[MAXN], qArr[MAXN];

void buildSPF() {
    for (int i = 1; i <= MAXA; i++) spf[i] = i;
    for (int i = 2; i * i <= MAXA; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= MAXA; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

void factorUnique(int x, int idx) {
    pfCnt[idx] = 0;
    while (x > 1) {
        int p = spf[x];
        if (pfCnt[idx] == 0 || pf[idx][pfCnt[idx] - 1] != p) {
            pf[idx][pfCnt[idx]++] = p;
        }
        x /= p;
    }
}

void initGraph(int n) {
    for (int i = 1; i <= n; i++) headL[i] = -1;
    edgeCnt = 0;
}

void addEdge(int u, int v) {
    toE[edgeCnt] = v;
    nxtE[edgeCnt] = headL[u];
    headL[u] = edgeCnt++;
}

bool bfsHK(int n) {
    int qh = 0, qt = 0;
    for (int u = 1; u <= n; u++) {
        if (matchL[u] == 0) {
            distL[u] = 0;
            qArr[qt++] = u;
        } else {
            distL[u] = -1;
        }
    }

    bool found = false;
    while (qh < qt) {
        int u = qArr[qh++];
        for (int e = headL[u]; e != -1; e = nxtE[e]) {
            int v = toE[e];
            int mu = matchR[v];
            if (mu == 0) {
                found = true;
            } else if (distL[mu] == -1) {
                distL[mu] = distL[u] + 1;
                qArr[qt++] = mu;
            }
        }
    }
    return found;
}

bool dfsHK(int u) {
    for (int e = headL[u]; e != -1; e = nxtE[e]) {
        int v = toE[e];
        int mu = matchR[v];
        if (mu == 0 || (distL[mu] == distL[u] + 1 && dfsHK(mu))) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    distL[u] = -1;
    return false;
}

int hopcroftKarp(int n, int m) {
    for (int i = 1; i <= n; i++) matchL[i] = 0;
    for (int i = 1; i <= m; i++) matchR[i] = 0;

    int matching = 0;
    while (bfsHK(n)) {
        for (int u = 1; u <= n; u++) {
            if (matchL[u] == 0 && dfsHK(u)) matching++;
        }
    }
    return matching;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int totalPF = 0;
    for (int i = 1; i <= n; i++) {
        factorUnique(a[i], i);
        for (int j = 0; j < pfCnt[i]; j++) allPrimes[totalPF++] = pf[i][j];
    }

    sort(allPrimes, allPrimes + totalPF);
    int m = 0;
    for (int i = 0; i < totalPF; i++) {
        if (i == 0 || allPrimes[i] != allPrimes[i - 1]) {
            allPrimes[m++] = allPrimes[i];
        }
    }

    initGraph(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < pfCnt[i]; j++) {
            int p = pf[i][j];
            int id = (int)(lower_bound(allPrimes, allPrimes + m, p) - allPrimes) + 1;
            addEdge(i, id);
        }
    }

    int maxMatch = hopcroftKarp(n, m);
    cout << (n - maxMatch) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    buildSPF();

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
