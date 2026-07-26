/*
 * =========================================================================================
 * TEMPLATE: Secondary Offline Mo's Algorithm (Mo's with Sweep Line)
 * =========================================================================================
 * 
 * [WHEN TO USE]
 * - You have offline range queries [L, R] asking to count pairs (i, j) satisfying a condition.
 * - Standard Mo's gives TLE because the pointer movement cost O(F) is too slow 
 *   (e.g., looping over 2000 palindromes, or updating a Fenwick tree on every pointer step).
 * - You need to reduce the O(N * sqrt(Q) * F) pointer cost to O(1).
 * - The pair counting logic can be algebraically split: 
 *   Pairs(new_element, window) = Pairs(new_element, right_prefix) - Pairs(new_element, left_prefix).
 *
 * [HOW TO USE]
 * You NEVER touch the Engine section. You only edit the "PROBLEM-SPECIFIC LOGIC" block:
 * 
 * 1. build_prefixes()
 *    - Iterate i from 1 to N.
 *    - Calculate `base_pairs`: How many valid pairs A[i] forms with the prefix 1...(i-1).
 *    - Calculate `self_pairs`: Does A[i] form a valid pair with itself? (1 or 0).
 *    - Set: pref_base[i] = pref_base[i - 1] + base_pairs
 *    - Set: pref_self[i] = pref_self[i - 1] + base_pairs + self_pairs
 *    - Update your active state (e.g., frequency array) with A[i] for the next iteration.
 *
 * 2. clear_sweep_state()
 *    - Reset your global data structures (arrays, Fenwick trees) to 0.
 *
 * 3. sweep_add(idx)
 *    - Add A[idx] to your active state. 
 *    - THIS CAN BE SLOW (O(F)). It only runs exactly N times. Put your heavy loops here.
 *
 * 4. sweep_query(idx)
 *    - Query A[idx] against the active state. 
 *    - THIS MUST BE FAST (O(1)). It runs O(N * sqrt(Q)) times. Do not put heavy loops here.
 *
 * [NOTE ON SELF-PAIRS (i = j)] 
 * - The engine STRICTLY calculates pairs where L <= i < j <= R. (Perfect cancellation).
 * - If the problem asks for `i <= j`, build a separate standard prefix sum array of 
 *   elements that pair with themselves, and add (pref_self_valid[R] - pref_self_valid[L-1])
 *   to final_ans[q_id] during the output phase.
 * =========================================================================================
 */

const int MAXN = 100005;
const int MAXQ = 100005;
const int MAX_EVENTS = MAXQ * 4;

struct Query {
    int l, r, id;
};

struct Event {
    int l, r, sign, id;
};

// --- Globals ---
int N, Q;
int A[MAXN];
Query queries[MAXQ];

// Flattened Event List
Event ev[MAX_EVENTS];
int head[MAXN];
int nxt[MAX_EVENTS];
int event_cnt = 0;

inline void add_event(int p, int l, int r, int sign, int id) {
    if (l > r) return;
    ev[++event_cnt] = {l, r, sign, id};
    nxt[event_cnt] = head[p];
    head[p] = event_cnt;
}

// Mo's Arrays
long long pref_base[MAXN];
long long pref_self[MAXN];
long long transition_delta[MAXQ];
int ev_start[MAXQ];
int ev_end[MAXQ];
long long event_res[MAX_EVENTS];
long long final_ans[MAXQ];

// =====================================================================
// PROBLEM-SPECIFIC LOGIC (Edit this section for each problem)
// =====================================================================

// Define your data structures (e.g., frequency arrays, Fenwick trees)
int freq[1000005]; 

// 1. Precompute how each element interacts with the prefix 1..i-1
inline void build_prefixes() {
    // Reset global state if handling multiple test cases
    // fill(freq, freq + 1000005, 0); 
    
    for (int i = 1; i <= N; ++i) {
        // Example: Equal Pairs
        // long long pairs = freq[A[i]];
        // pref_base[i] = pref_base[i - 1] + pairs;
        // pref_self[i] = pref_self[i - 1] + pairs + 1;
        // freq[A[i]]++;
    }
}

// 2. Clear state before the sweep line execution
inline void clear_sweep_state() {
    // Example: fill(freq, freq + 1000005, 0);
}

// 3. Add an element to the active sweep line state
inline void sweep_add(int idx) {
    // Example: freq[A[idx]]++;
}

// 4. Query an element against the active sweep line state
inline long long sweep_query(int idx) {
    // Example: return freq[A[idx]];
    return 0;
}

// =====================================================================
// ENGINE (Do not touch)
// =====================================================================

void solve() {
    cin>>N>>Q;

    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= Q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    // 1. Build Prefixes via function
    build_prefixes();

    // 2. Parity Sort
    int B = max(1, (int)(N / sqrt(Q)));
    sort(queries + 1, queries + Q + 1, [&](const Query& x, const Query& y) {
        int bx = x.l / B;
        int by = y.l / B;
        if (bx != by) return bx < by;
        return (bx & 1) ? x.r < y.r : x.r > y.r;
    });

    // 3. Generate Events
    fill(head, head + N + 1, 0);
    event_cnt = 0;
    
    int L = 1, R = 0;
    int current_event_id = 0;
    
    for (int i = 1; i <= Q; ++i) {
        int QL = queries[i].l, QR = queries[i].r;
        long long cur_delta = 0;
        ev_start[i] = current_event_id + 1;

        if (L > QL) {
            cur_delta -= (pref_self[L - 1] - pref_self[QL - 1]);
            add_event(R, QL, L - 1, 1, ++current_event_id);
            L = QL;
        }
        if (R < QR) {
            cur_delta += (pref_base[QR] - pref_base[R]);
            add_event(L - 1, R + 1, QR, -1, ++current_event_id);
            R = QR;
        }
        if (L < QL) {
            cur_delta += (pref_self[QL - 1] - pref_self[L - 1]);
            add_event(R, L, QL - 1, -1, ++current_event_id);
            L = QL;
        }
        if (R > QR) {
            cur_delta -= (pref_base[R] - pref_base[QR]);
            add_event(L - 1, QR + 1, R, 1, ++current_event_id);
            R = QR;
        }

        transition_delta[i] = cur_delta;
        ev_end[i] = current_event_id;
    }

    // 4. Execute Sweep Line
    clear_sweep_state();

    for (int P = 0; P <= N; ++P) {
        if (P > 0) sweep_add(P);
        
        for (int i = head[P]; i > 0; i = nxt[i]) {
            long long sum = 0;
            for (int k = ev[i].l; k <= ev[i].r; ++k) {
                sum += sweep_query(k);
            }
            event_res[ev[i].id] = sum * ev[i].sign;
        }
    }

    // 5. Accumulate & Print
    long long cur_ans = 0;
    for (int i = 1; i <= Q; ++i) {
        cur_ans += transition_delta[i];
        for (int e = ev_start[i]; e <= ev_end[i]; ++e) {
            cur_ans += event_res[e];
        }
        final_ans[queries[i].id] = cur_ans;
    }

    for (int i = 1; i <= Q; ++i) {
        cout << final_ans[i] << "\n";
    }
}

