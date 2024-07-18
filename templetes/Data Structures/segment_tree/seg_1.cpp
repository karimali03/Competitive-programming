#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define int long long

 



struct item {
    vector<int> v;
    vector<int> pre;
 
    item(vector<int> &v,vector<int> &pre): v(v), pre(pre) {
    }
};
 
struct segment_tree {
private:
    int size;
 
    vector<item> seg;
    vector<int> neu = {INT_MAX};
    item neutral = {neu, neu};
 
    item merge(item &x, item &y) {
        int i = 0, j = 0, k = 0;
        int sz1 = (int) x.v.size();
        int sz2 = (int) y.v.size();
        vector<int> ret = vector<int>(sz1 + sz2);
        while (i < sz1 && j < sz2) {
            if (x.v[i] < y.v[j]) {
                ret[k++] = x.v[i++];
            } else {
                ret[k++] = y.v[j++];
            }
        }
        while (i < sz1) {
            ret[k++] = x.v[i++];
        }
        while (j < sz2) {
            ret[k++] = y.v[j++];
        }
        vector<int> pre = vector<int>(sz1 + sz2);
        for (int i = 0; i < sz1 + sz2; i++) {
            if (i == 0) {
                pre[i] = ret[i];
            } else {
                pre[i] = pre[i - 1] + ret[i];
            }
        }
        return item{ret, pre};
    }
 
    item single(int v) {
        vector<int> arr = {v};
        return item{arr, arr};
    }
 
    int calc(item &a, int k) {
        return upper_bound(a.v.begin(),a.v.end(), k) - a.v.begin();
    }
 
 
    void _build(vector<int> &v,int idx, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int) v.size()) {
                seg[idx] = single(v[lx]);
            }
            return;
        }
        int m = (lx + rx) / 2;
        _build(v, idx * 2 + 1, lx, m);
        _build(v, idx * 2 + 2, m, rx);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
 
    void _set(int i,int v,int idx,int lx,int rx) {
        if (rx - lx == 1) {
            seg[idx] = single(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) _set(i, v, idx * 2 + 1, lx, m);
        else _set(i, v, idx * 2 + 2, m, rx);
 
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
 
 
    int _query(int l, int r, int k, int idx, int lx, int rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) {
            int x = calc(seg[idx], k);
            if (x == 0) return 0;
            return seg[idx].pre[x - 1];
        }
        int m = (lx + rx) / 2;
        int s1 = _query(l, r, k, idx * 2 + 1, lx, m);
        int s2 = _query(l, r, k, idx * 2 + 2, m, rx);
        return (s1 + s2);
    }
 
public:
    segment_tree(int n) {
        size = 1;
        while (size < n) {
            size <<= 1;
        }
        seg = vector<item>(size << 1, neutral);
    }
 
    void build(vector<int> &v) {
        _build(v, 0, 0, size);
    }
 
    void set(int i, int v) {
        assert(i >=0 && i < size);
        _set(i, v, 0, 0, size);
    }
 
    int query(int l, int r, int k) {
        return _query(l, r, k, 0, 0, size);
    }
};
 
 

signed main() {
   
    return 0;
}
