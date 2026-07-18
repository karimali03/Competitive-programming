int SQ,sum;
int frq[1'000'001]{};
struct Query
{
    int l, r, idx;
    bool operator < (const Query &other) const
    {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;
        return (l/SQ) & 1 ? r > other.r : r < other.r;
    }
};
 
void add(int val) {
    sum -= val * (frq[val]*frq[val]);
    frq[val]++;
    sum += val * (frq[val]*frq[val]);
}

void del(int val) {
    sum -= val * (frq[val]*frq[val]);
    frq[val]--;   
    sum += val * (frq[val]*frq[val]);
}

vector<int> MO(vector<Query> &q, vector<int> &v){
    int n = v.size();
    SQ = sqrt(n) + 1;
    sum = 0;
    vector<int> res(q.size());
    sort(q.begin(), q.end());
    int l = 0 ,r = -1;
    for(auto [lq,rq,idx] : q){
        while(lq < l) add(v[--l]);
        while(rq > r) add(v[++r]);
        while(lq > l) del(v[l++]);
        while(rq < r) del(v[r--]);
        res[idx] = sum;
    }
    return res;
}


/*
Use Case:
Efficiently answers multiple range queries of the form [L, R], where:
The queries are offline (non-persistent)

Core Idea:
Process queries in a specific order to minimize the movement of the two pointers (left and right).
Maintain a data structure that can update the answer incrementally when:
L is incremented or decremented
R is incremented or decremented

Optimization Strategy:

Sort the queries by block number of L (L / block_size), and then by R within each block.

Block size is usually √n.

Time Complexity:

O((n + q) * √n) — where n is the size of the array and q is the number of queries.

Important Note:
This works only when the modification cost is small and incremental.
*/
