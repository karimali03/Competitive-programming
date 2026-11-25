#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Two players alternate, both play optimally.
// Normal play: the player who cannot move LOSES. Set misere = true if the player who cannot move WINS.
// A state is WINNING if SOME move goes to a LOSING state; LOSING if EVERY move goes to a winning state.
// The game must always end (no cycles between states), otherwise the recursion never stops.
bool misere = false;

// ---- mex ----
// Smallest non-negative integer NOT in v. O(k log k).
int mex(vi v) {
    sort(v.begin(), v.end());
    int m = 0;
    for (int x : v) if (x == m) m++; else if (x > m) break;
    return m;
}

// ---- any game with ONE integer state ----
// EDIT moves(): every state reachable from s in one move. Default: subtraction game, take t in S stones.
vi S = {1, 3, 4};
vector<ll> moves(ll s) {
    vector<ll> r;
    for (int t : S) if (t <= s) r.push_back(s - t);
    return r;
}
// True iff the player to move from s wins. O(#states * #moves). Clear memoWin if you change moves().
map<ll, bool> memoWin;
bool win(ll s) {
    auto it = memoWin.find(s);
    if (it != memoWin.end()) return it->second;
    vector<ll> nx = moves(s);
    bool w = nx.empty() ? misere : false;
    for (ll t : nx) if (!win(t)) w = true;
    return memoWin[s] = w;
}
// Grundy number of s (0 = losing). Normal play only. O(#states * #moves).
// Use it for a SUM of independent games: the first player wins iff XOR of the grundy values != 0.
map<ll, int> memoG;
int grundy(ll s) {
    auto it = memoG.find(s);
    if (it != memoG.end()) return it->second;
    vi g;
    for (ll t : moves(s)) g.push_back(grundy(t));
    return memoG[s] = mex(g);
}

// ---- any game with a VECTOR state (piles, positions, a board, ...) ----
// EDIT movesV(). Default: Nim, make one pile smaller. Sorting the state merges equal states (piles are unordered).
vector<vi> movesV(const vi& s) {
    vector<vi> r;
    for (int i = 0; i < (int)s.size(); i++)
        for (int x = 0; x < s[i]; x++) {
            vi t = s;
            t[i] = x;
            sort(t.begin(), t.end());
            r.push_back(t);
        }
    return r;
}
// True iff the player to move from s wins. Exponential in the state size: piles <= 6, count <= 4.
map<vi, bool> memoV;
bool winV(const vi& s) {
    auto it = memoV.find(s);
    if (it != memoV.end()) return it->second;
    vector<vi> nx = movesV(s);
    bool w = nx.empty() ? misere : false;
    for (auto& t : nx) if (!winV(t)) w = true;
    return memoV[s] = w;
}

// ---- token on a DAG ----
// Token starts at a node; a move slides it along an edge u->v; no move = lose (normal play).
// Returns w[v] = 1 if the player to move with the token at v wins. Nodes 1..n. O(n + m).
vi dagWin(int n, const vector<pii>& e) {
    vector<vi> adj(n + 1);
    for (auto [u, v] : e) adj[u].push_back(v);
    vi w(n + 1, -1);
    function<int(int)> go = [&](int v) {
        if (w[v] != -1) return w[v];
        w[v] = 0;
        for (int to : adj[v]) if (!go(to)) w[v] = 1;
        return w[v];
    };
    for (int v = 1; v <= n; v++) go(v);
    return w;
}
// Grundy number of every node. Several tokens on the same DAG: first wins iff XOR of g[token] != 0.
vi dagGrundy(int n, const vector<pii>& e) {
    vector<vi> adj(n + 1);
    for (auto [u, v] : e) adj[u].push_back(v);
    vi g(n + 1, -1);
    function<int(int)> go = [&](int v) {
        if (g[v] != -1) return g[v];
        vi nx;
        for (int to : adj[v]) nx.push_back(go(to));
        return g[v] = mex(nx);
    };
    for (int v = 1; v <= n; v++) go(v);
    return g;
}

// ---- take from either end (score game) ----
// Players alternately take a[l] or a[r]; each wants the larger total.
// Returns (first player's total) - (second player's total) for a[l..r]. Plain recursion O(2^n), n <= 20.
ll endsDiff(const vi& a, int l, int r) {
    if (l > r) return 0;
    return max(a[l] - endsDiff(a, l + 1, r), a[r] - endsDiff(a, l, r - 1));
}

// ---- known results (good first guesses; stress them against the brutes above) ----
// Nim: first wins iff XOR != 0. Misere Nim: if all piles <= 1, first wins iff the number of 1-piles is even.
bool nimFormula(const vi& p, bool mis) {
    int x = 0, mx = 0;
    for (int v : p) x ^= v, mx = max(mx, v);
    if (mis && mx <= 1) return x == 0;
    return x != 0;
}
// Take 1..k stones: first wins iff n % (k + 1) != 0.
bool takeUpToK(ll n, ll k) { return n % (k + 1) != 0; }

// ===== CLASSIC GAMES =====
// Each game: <game>Brute / Grundy = memoized recursion over the real moves (no formula),
// <game>Formula = the known rule to guess and stress against it. All normal play, small inputs only.

// ---- Wythoff ----
// Two piles; take any amount from one pile OR the same amount from both. True iff first wins. O(a*b*(a+b)), a, b <= 60.
map<pii, bool> memoW;
bool wythoffBrute(int a, int b) {
    if (a > b) swap(a, b);
    auto it = memoW.find({a, b});
    if (it != memoW.end()) return it->second;
    bool w = false;
    for (int x = 1; x <= b; x++) {
        if (x <= a && !wythoffBrute(a - x, b - x)) w = true;
        if (x <= a && !wythoffBrute(a - x, b)) w = true;
        if (!wythoffBrute(a, b - x)) w = true;
    }
    return memoW[{a, b}] = w;
}
// Losing pairs (a <= b) are (floor(k*phi), floor(k*phi^2)) = (A, A + k). Exact: A = (k + isqrt(5k^2)) / 2. O(1), b - a <= 1e9.
bool wythoffFormula(ll a, ll b) {
    if (a > b) swap(a, b);
    ll k = b - a, s = sqrtl(5.0L * k * k);
    while (s * s > 5 * k * k) s--;
    while ((s + 1) * (s + 1) <= 5 * k * k) s++;
    return a != (k + s) / 2;
}

// ---- Staircase Nim ----
// Stairs 0..n-1, s[i] coins on stair i; a move takes x >= 1 coins from stair i >= 1 down to stair i-1. True iff first wins.
// Exponential: <= 4 stairs, piles <= 4.
map<vi, bool> memoSt;
bool stairBrute(const vi& s) {
    auto it = memoSt.find(s);
    if (it != memoSt.end()) return it->second;
    bool w = false;
    for (int i = 1; i < (int)s.size(); i++)
        for (int x = 1; x <= s[i]; x++) {
            vi t = s;
            t[i] -= x, t[i - 1] += x;
            if (!stairBrute(t)) w = true;
        }
    return memoSt[s] = w;
}
// First wins iff XOR of the piles on ODD stairs != 0 (even stairs don't matter: the opponent just moves those coins down again).
bool stairFormula(const vi& s) {
    int x = 0;
    for (int i = 1; i < (int)s.size(); i += 2) x ^= s[i];
    return x != 0;
}

// ---- Moore's Nim_k ----
// Nim where a move reduces between 1 and k piles (each by any positive amount). True iff first wins.
// Exponential: <= 3 piles, piles <= 6 (k = 1 is plain Nim).
map<pair<int, vi>, bool> memoM;
bool mooreBrute(vi s, int k) {
    sort(s.begin(), s.end());
    auto it = memoM.find({k, s});
    if (it != memoM.end()) return it->second;
    bool w = false;
    vi t = s;
    function<void(int, int)> go = [&](int i, int used) { // pile i next, `used` piles reduced so far
        if (w) return;
        if (i == (int)s.size()) {
            if (used && !mooreBrute(t, k)) w = true;
            return;
        }
        go(i + 1, used);
        if (used < k) {
            for (int x = 0; x < s[i]; x++) t[i] = x, go(i + 1, used + 1);
            t[i] = s[i];
        }
    };
    go(0, 0);
    return memoM[{k, s}] = w;
}
// Write the piles in binary: first LOSES iff for every bit the number of piles having it is divisible by k + 1. O(bits * piles).
bool mooreFormula(const vi& p, int k) {
    for (int b = 0; b < 30; b++) {
        int c = 0;
        for (int v : p) c += v >> b & 1;
        if (c % (k + 1)) return true;
    }
    return false;
}

// ---- Kayles ----
// Row of n pins; knock down 1 pin or 2 adjacent pins (the row splits in two). Grundy of a row of n pins; first wins iff != 0.
// Splits are summed by XOR. O(n^2 log n), n <= 2000.
map<int, int> memoK;
int kaylesGrundy(int n) {
    if (n <= 0) return 0;
    auto it = memoK.find(n);
    if (it != memoK.end()) return it->second;
    vi g;
    for (int a = 0; a < n; a++) g.push_back(kaylesGrundy(a) ^ kaylesGrundy(n - 1 - a));
    for (int a = 0; a + 2 <= n; a++) g.push_back(kaylesGrundy(a) ^ kaylesGrundy(n - 2 - a));
    return memoK[n] = mex(g);
}
// Known: the Grundy sequence is periodic with period 12 from n = 71 on (checked numerically). O(1) for any n.
int kaylesFormula(int n) { return kaylesGrundy(n > 82 ? 71 + (n - 71) % 12 : n); }

// ---- Grundy's game ----
// Split one heap into two UNEQUAL non-empty heaps. Grundy of a heap of n; first wins iff != 0.
// No simple formula is known (the sequence has no known period): use this as the brute. O(n^2 log n), n <= 2000.
map<int, int> memoGG;
int grundysGame(int n) {
    auto it = memoGG.find(n);
    if (it != memoGG.end()) return it->second;
    vi g;
    for (int a = 1; 2 * a < n; a++) g.push_back(grundysGame(a) ^ grundysGame(n - a));
    return memoGG[n] = mex(g);
}

// ---- Euclid's game ----
// (a, b): subtract a positive multiple of the smaller from the larger, result >= 0. A state with a 0 is LOST for the mover
// (the previous player made the zero). True iff first wins. O(a * b / min), a, b <= 60.
map<pii, bool> memoE;
bool euclidBrute(int a, int b) {
    if (a > b) swap(a, b);
    if (a == 0) return false;
    auto it = memoE.find({a, b});
    if (it != memoE.end()) return it->second;
    bool w = false;
    for (int t = b - a; t >= 0; t -= a) if (!euclidBrute(a, t)) w = true;
    return memoE[{a, b}] = w;
}
// With a <= b: win if b >= 2a (one of (a, b%a) and (a, b%a + a) is losing, pick it) or a == b; else the only move is (a, b - a): negate. O(log).
bool euclidFormula(ll a, ll b) {
    if (a > b) swap(a, b);
    if (a == 0) return false;
    if (b >= 2 * a || b == a) return true;
    return !euclidFormula(a, b - a);
}

// ---- Chomp ----
// h[j] = height of column j (non-increasing), square (row 0, column 0) is poisoned; eating square (i, j) removes every square
// (i', j') with i' >= i, j' >= j. Whoever must eat the poison loses. True iff first wins. Use chompBrute(vi(c, r)) for r x c.
// Known: first wins every rectangle except 1x1 (strategy stealing, see "13 - Game Theory/Strategy-Stealing Argument.cpp"); no formula for the move.
// O(C(r+c, r) * r * c), r, c <= 7.
map<vi, bool> memoC;
bool chompBrute(const vi& h) {
    auto it = memoC.find(h);
    if (it != memoC.end()) return it->second;
    bool w = false;
    for (int j = 0; j < (int)h.size(); j++)
        for (int i = 0; i < h[j]; i++) {
            if (i == 0 && j == 0) continue;
            vi t = h;
            for (int c = j; c < (int)h.size(); c++) t[c] = min(t[c], i);
            if (!chompBrute(t)) w = true;
        }
    return memoC[h] = w;
}

// ---- Green Hackenbush on a rooted tree ----
// Nodes 0..n-1, node 0 = the ground, node v >= 1 hangs from par[v] < v by edge v. Cutting edge v removes everything no longer
// connected to the ground. Returns the Grundy number of the whole tree. State = bitmask of remaining edges. O(2^n * n^2), <= 10 edges.
int hackenbushBrute(const vi& par) {
    int n = par.size();
    map<int, int> memo;
    function<int(int)> go = [&](int m) {
        auto it = memo.find(m);
        if (it != memo.end()) return it->second;
        vi g;
        for (int v = 1; v < n; v++) if (m >> v & 1) {
            int t = 0; // edges of m minus edge v that are still connected to the ground
            for (int u = 1; u < n; u++) if ((m >> u & 1) && u != v && (par[u] == 0 || (t >> par[u] & 1))) t |= 1 << u;
            g.push_back(go(t));
        }
        return memo[m] = mex(g);
    };
    return go(((1 << n) - 1) ^ 1);
}
// Colon principle: g(v) = XOR over children c of (g(c) + 1); answer is g(0). O(n).
int hackenbushFormula(const vi& par) {
    int n = par.size();
    vi g(n, 0);
    for (int v = n - 1; v >= 1; v--) g[par[v]] ^= g[v] + 1;
    return g[0];
}

int main(int argc, char* argv[]) {
    // PATTERN FINDER: ./brute 40 prints W/L and grundy for states 0..40, using moves() above.
    if (argc > 1) {
        int N = atoi(argv[1]);
        string wl;
        vi losing;
        for (int n = 0; n <= N; n++) {
            wl += win(n) ? 'W' : 'L';
            if (!win(n)) losing.push_back(n);
        }
        cout << "W/L:    " << wl << '\n' << "losing: ";
        for (int x : losing) cout << x << ' ';
        cout << "\ngrundy: ";
        for (int n = 0; n <= N; n++) cout << grundy(n) << ' ';
        cout << '\n';
        return 0;
    }

    // STRESS MODE: reads gen.cpp's "n k" then k take amounts; prints who wins.
    ll n;
    int k;
    cin >> n >> k;
    S.assign(k, 0);
    for (int& x : S) cin >> x;
    cout << (win(n) ? "First" : "Second") << '\n';
}

/* Other ready-to-use main bodies (pair each with the matching gen main):

    // Nim piles: "k" then k piles
    int k; cin >> k;
    vi p(k);
    for (int& x : p) cin >> x;
    sort(p.begin(), p.end());
    cout << (winV(p) ? "First" : "Second") << '\n';

    // Token on a DAG: "n m start" then m edges
    int n, m, s; cin >> n >> m >> s;
    vector<pii> e(m);
    for (auto& [u, v] : e) cin >> u >> v;
    cout << (dagWin(n, e)[s] ? "First" : "Second") << '\n';

    // Take-from-ends array: "n" then n values; prints first total - second total
    int n; cin >> n;
    vi a(n);
    for (int& x : a) cin >> x;
    cout << endsDiff(a, 0, n - 1) << '\n';

    // Wythoff: "a b"
    int a, b; cin >> a >> b;
    cout << (wythoffBrute(a, b) ? "First" : "Second") << '\n';

    // Chomp: "r c"
    int r, c; cin >> r >> c;
    cout << (chompBrute(vi(c, r)) ? "First" : "Second") << '\n';

    // Hackenbush tree: "n" then the parents of nodes 1..n-1 (par[v] < v); prints the Grundy number
    int n; cin >> n;
    vi par(n, 0);
    for (int v = 1; v < n; v++) cin >> par[v];
    cout << hackenbushBrute(par) << '\n';

    // 2D PATTERN FINDER: W/L grid for two-number states (a, b), e.g. two piles. Edit movesV() first.
    int N = 15;
    for (int a = 0; a <= N; a++) {
        for (int b = 0; b <= N; b++) cout << (winV({min(a, b), max(a, b)}) ? 'W' : '.');
        cout << '\n';
    }
*/
