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
/*
        Divisbility Rules :

        Number is divisible by 2 if last digit equal 0,2,4,6,8

        Number is divisible by 3 if sum of digits divisible by 3

        Number is divisible by 4 if the last two digits divisible by 4  
        ex: 1936  36%4==0

        Number is divisible by 5 if last digit is 0 or 5

        Number is divisible by 6 if it is divisible by 2 & 3

        Number is divisible by 8 if the last 3 digits is divisible by 8

        Number is divisible by 9 if sum of digits if divisible by 9

        Number is divisible by 10 is the last digit is 0

        Number is divisible by 11 is the difference between
        Odd indexes and even indexes is divisible by 11

        Number is divisible by 12 if it is divisible by 3 and 4

*/
