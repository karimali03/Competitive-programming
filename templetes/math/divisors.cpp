// get divisors of n
vector<int> divisiors(int n){ // O( sqrt(n) )
    vector<int>res;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            res.push_back(i);
            if(i!=n/i) res.push_back(n/i);
        }
    }
    return res;
}


// get divisors form factorization

vector<pair<int,int>>v;  // {prime,count}
vector<int>divisors;
void get_divisors(int idx ,int val=1){  // O ( n^(1/3) )

    if(idx == v.size()) {
        divisors.push_back(val);
        return;
    }

    for(int i=0;i<=v[idx].second ;i++){
        get_divisors(idx+1,val);
        val*=v[idx].first;
    }
    
}



//  get divisors from 1 to N (Nlog(N))
const int N = 1'000'005;
vi divisors[N];
for(int i = 1 ; i < N ; i++ ){
        for(int j = i; j < N ; j+=i){
            divisors[j].push_back(i);
        }
}

/*

number with max number of divisors is called HCN
| Max $n$  | Max # of Divisors | Number with Max Divisors |
| -------- | --   | ------------------------ |
| >= 10^2$ | 12   | 60                       |
| >= 10^3$ | 32   | 840                      |
| >= 10^4$ | 64   | 7560                     |
| >= 10^5$ | 128  | 83160                    |
| >= 10^6$ | 240  | 720720                   |
| >= 10^7$ | 448  | 73513440                 |
| >= 10^8$ | 768  | 735134400                |
| >= 10^9$ | 1344 | 735134400                |
if you're dividing something (e.g., grid, people, blocks), HCNs make ideal candidates since they divide easily due to many factors.
*/

