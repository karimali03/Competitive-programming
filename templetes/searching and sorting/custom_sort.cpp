vector<pair<int,int>> v = {{3,2}, {1,5}, {3,1}, {2,4}};

// sort ascending by first, then by second
sort(v.begin(), v.end(), [](auto &a, auto &b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
});

// sort descending by first, then by second
sort(v.begin(), v.end(), [](auto &a, auto &b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second > b.second;
});


// max-heap by first, then second
struct PairPQMax {
    bool operator()(const pair<int,int> &a, const pair<int,int> &b) const {
        if (a.first != b.first) return a.first < b.first; // bigger first first
        return a.second < b.second;                      // then bigger second
    }
};

// min-heap by first, then second
struct PairPQMin {
    bool operator()(const pair<int,int> &a, const pair<int,int> &b) const {
        if (a.first != b.first) return a.first > b.first; // smaller first first
        return a.second > b.second;                      // then smaller second
    }
};

priority_queue<pair<int,int>, vector<pair<int,int>>, PairPQMax> pq_max;
priority_queue<pair<int,int>, vector<pair<int,int>>, PairPQMin> pq_min;



// ascending by first, then second
struct PairMapAsc {
    bool operator()(const pair<int,int> &a, const pair<int,int> &b) const {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    }
};

// descending by first, then second
struct PairMapDesc {
    bool operator()(const pair<int,int> &a, const pair<int,int> &b) const {
        if (a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    }
};

set<pair<int,int>, PairMapAsc> st_asc;
set<pair<int,int>, PairMapDesc> st_desc;

map<pair<int,int>, int, PairMapAsc> mp_asc;
map<pair<int,int>, int, PairMapDesc> mp_desc;


struct node {
    int x, y, d;
    node(int x=0,int y=0,int d=0):x(x),y(y),d(d){}
    bool operator<(const node &rhs) const {
        return d > rhs.d;
    }
};

