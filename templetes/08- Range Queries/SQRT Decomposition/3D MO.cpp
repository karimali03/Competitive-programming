// ================= CONSTANTS =================
const int MAXN = 100005;  // Max Array Size
const int BLK = 2154;     // Block size. Optimal is pow(N, 2.0/3.0). 
                          // For N=100k -> ~2154. For N=200k -> ~3420.

// ================= DATA STRUCTURES =================
struct Query {
    int l, r, t, id;

    // Standard 3D Mo's Comparator
    bool operator<(const Query& other) const {
        int l_blk = l / BLK;
        int other_l_blk = other.l / BLK;
        if (l_blk != other_l_blk) return l_blk < other_l_blk;

        int r_blk = r / BLK;
        int other_r_blk = other.r / BLK;
        if (r_blk != other_r_blk) return r_blk < other_r_blk;

        return t < other.t;
    }
};

struct Update {
    int p;        // Index to update
    int old_val;  // Value before update
    int new_val;  // Value after update
};

// ================= GLOBAL STATE =================
int n, q;
int a[MAXN];        // The array (keeps track of current state)
int answers[MAXN];  // Stores answers for queries

vector<Query> queries;
vector<Update> updates;

// TODO: Add your problem-specific data structures here
// e.g., int freq[MAXN], current_answer = 0;


// ================= PROBLEM SPECIFIC FUNCTIONS =================

// Called when index 'idx' enters the range [L, R]
inline void add(int idx) {
    int val = a[idx];
    // TODO: Update your data structure (e.g., freq[val]++)
}

// Called when index 'idx' leaves the range [L, R]
inline void remove(int idx) {
    int val = a[idx];
    // TODO: Update your data structure (e.g., freq[val]--)
}

// Called to calculate/store the answer for the current range [L, R]
inline int get_answer() {
    // TODO: Return the answer based on current state
    return 0; 
}

// ================= MO'S CORE LOGIC =================

// Applies the update at 'u_idx'. 
// If the updated position is inside [currL, currR], we must reflect it in stats.
void apply_update(int u_idx, int currL, int currR) {
    int p = updates[u_idx].p;
    int new_v = updates[u_idx].new_val;
    int old_v = updates[u_idx].old_val;

    if (p >= currL && p <= currR) {
        // Technically: remove old value, add new value
        // But since 'add/remove' use a[idx], we must be careful with order
        // 1. Remove index p (which has old_val)
        remove(p);
        // 2. Change actual array
        a[p] = new_v;
        // 3. Add index p (which now has new_val)
        add(p);
    } else {
        a[p] = new_v;
    }
}

// Reverses the update at 'u_idx'.
void undo_update(int u_idx, int currL, int currR) {
    int p = updates[u_idx].p;
    int new_v = updates[u_idx].new_val;
    int old_v = updates[u_idx].old_val;

    if (p >= currL && p <= currR) {
        remove(p);     // Remove current (new) val
        a[p] = old_v;  // Revert array
        add(p);        // Add back old val
    } else {
        a[p] = old_v;
    }
}

void run_mos() {
    sort(queries.begin(), queries.end());

    int currL = 1;
    int currR = 0;
    int currT = 0; // Tracks how many updates have been applied

    for (const auto& q : queries) {
        // 1. Adjust Time
        while (currT < q.t) {
            apply_update(currT, currL, currR);
            currT++;
        }
        while (currT > q.t) {
            currT--;
            undo_update(currT, currL, currR);
        }

        // 2. Adjust Range
        while (currL > q.l) add(--currL);
        while (currR < q.r) add(++currR);
        while (currL < q.l) remove(currL++);
        while (currR > q.r) remove(currR--);

        // 3. Store Answer
        answers[q.id] = get_answer();
    }
}

// ================= MAIN =================
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> q;

    // Reading Input
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Reading Queries
    int t_counter = 0; // Number of updates so far
    int q_counter = 0; // Index of actual queries

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            queries.push_back({l, r, t_counter, q_counter++});
        } else {
            int p, x;
            cin >> p >> x;
            updates.push_back({p, a[p], x});
            a[p] = x; // Update state temporarily to track history
            t_counter++;
        }
    }

    // Reset array to initial state before running Mo's
    // (Because we modified it while reading updates to get old_val/new_val pairs)
    for (int i = t_counter - 1; i >= 0; i--) {
        a[updates[i].p] = updates[i].old_val;
    }

    run_mos();

    for (int i = 0; i < q_counter; i++) {
        cout << answers[i] << "\n";
    }

    return 0;
}
