void upper(string &s){
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

void lower(string &s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void uni(string &s){
	  auto it = unique(s.begin(), s.end());
      s.resize(distance(s.begin(), it));
}

ll sum_all(ll n,ll c=1){
    return ((n/c)*((n/c)+1)*c)/2;
}

// setfill('0') sets the fill character to '0'.
// setw(3) sets the width to 3 for the next output.
//  setfill('0') << setw(3) <<


// intersect two segments
bool intersect(pair<int,int> a, pair<int,int> b) {
    if (a.first > b.first) swap(a, b);
    return a.s >= b.f;
}

