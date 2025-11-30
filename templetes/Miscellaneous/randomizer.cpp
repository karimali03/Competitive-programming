std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
ll rand_range(ll l, ll r) { return l + (ull) rng() % (r - l + 1); }
void shuffle(vector<int> &v) { shuffle(v.begin(), v.end(), rng); }
char rand_char() { return 'a' + rand_range(0, 25); }

// find min element occure more than k times
int mn = 1e9;
for(int i = 0 ; i < 100 ; i++){
    int rnd = v[l + rng()%(r-l+1)];
    if(frq[rnd] > val && rnd < mn) mn = rnd;
}


