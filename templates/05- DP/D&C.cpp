/*
============================================================
DIVIDE & CONQUER DP OPTIMIZATION
============================================================

DP form:

    dp[g][i] = min over x (
                    dp[g-1][x-1] + cost(x, i)
                )

Meaning:
    dp[g][i] = answer for [0..i] using (g+1) groups.
    x        = start of the last group.
    last group = [x..i].

Base:
    dp[0][i] = cost(0, i)

D&C works when optimal split is monotonic:

    opt[g][i] <= opt[g][i+1]

Then to calculate dp[g][l..r]:

    mid = (l+r)/2

    find opt[mid] in [optL .. optR]

    left  half can only use [optL .. opt[mid]]
    right half can only use [opt[mid] .. optR]

So:

    calc(g, l, mid-1, optL, opt)
    calc(g, mid+1, r, opt, optR)


Complexity:
    Normally: O(K * N^2)

    With D&C:
        O(K * N * log N) transitions approximately

    If cost(l,r) can be moved efficiently, this becomes practical.


IMPORTANT:
    add(), rm(), move() below are PROBLEM SPECIFIC.
    Replace them depending on what cost(l,r) means.
============================================================
*/

const int N = 35005;
const int K = 105;
const int INF = 1e9;

int n, k;
int v[N];

int dp[K][N];


// ============================================================
// COST(l,r) MAINTENANCE
//
// Current problem:
// For every value inside [l,r], contribute:
//
//      last_position[value] - first_position[value]
//
// res = sum of these contributions.
// ============================================================

deque<int> pos[N];

int res;
int cur_l, cur_r;


void add(int i) {
    int x = v[i];

    // remove old contribution
    if (!pos[x].empty())
        res -= pos[x].back() - pos[x].front();

    // i is added from either left or right
    if (pos[x].empty() || pos[x].back() < i)
        pos[x].push_back(i);
    else
        pos[x].push_front(i);

    // add new contribution
    res += pos[x].back() - pos[x].front();
}


void rm(int i) {
    int x = v[i];

    // remove old contribution
    if (!pos[x].empty())
        res -= pos[x].back() - pos[x].front();

    if (pos[x].front() == i)
        pos[x].pop_front();
    else
        pos[x].pop_back();

    // add new contribution
    if (!pos[x].empty())
        res += pos[x].back() - pos[x].front();
}


// Change current [cur_l, cur_r] -> [l, r]
void move(int l, int r) {

    // expand
    while (cur_l > l) add(--cur_l);
    while (cur_r < r) add(++cur_r);

    // shrink
    while (cur_l < l) rm(cur_l++);
    while (cur_r > r) rm(cur_r--);
}


// ============================================================
// D&C DP
// ============================================================

void calc(int g, int l, int r, int optL, int optR) {

    if (l > r) return;

    int mid = (l + r) / 2;

    int best = INF;
    int opt = optL;

    // x = start of last group [x..mid]
    //
    // Need at least g elements before x,
    // because dp[g-1][x-1] uses g groups.
    int L = max(g, optL);
    int R = min(mid, optR);

    for (int x = R; x >= L; x--) {

        move(x, mid);

        int cur =
            dp[g-1][x-1]
            + res;              // cost(x,mid)

        if (cur < best) {
            best = cur;
            opt = x;
        }
    }

    dp[g][mid] = best;

    // opt is monotonic
    calc(g, l, mid-1, optL, opt);
    calc(g, mid+1, r, opt, optR);
}


void solve() {

    cin >> n >> k;

    for (int i = 0; i < n; i++)
        cin >> v[i];


    // --------------------------------------------------------
    // Base:
    //
    // dp[0][i] = cost(0,i)
    // one group containing [0..i]
    // --------------------------------------------------------

    res = 0;

    for (int i = 0; i <= n; i++)
        pos[i].clear();

    for (int i = 0; i < n; i++) {
        add(i);
        dp[0][i] = res;
    }


    // --------------------------------------------------------
    // Build layers 1..k-1
    // --------------------------------------------------------

    for (int g = 1; g < k; g++) {

        // reset movable interval
        cur_l = 0;
        cur_r = -1;
        res = 0;

        for (int i = 0; i <= n; i++)
            pos[i].clear();

        calc( g,
            g,  // need at least g+1 elements
            n-1,
            g,
            n-1
        );
    }

    cout << dp[k-1][n-1] << '\n';
}