#include<iostream>
#include<cstring>	// memset
#include<map>
#include<vector>
using namespace std;

class BinaryTrie {
    private:

    static const int MAX_BITS = 31;
    int cnt;

    public:
    BinaryTrie* child[2];
    BinaryTrie(){
        memset(child,0,sizeof(child));
        cnt = 0;
    }

    void insert(int num){
        BinaryTrie* cur = this;
        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(!cur->child[bit]) cur->child[bit] = new BinaryTrie();
            cur = cur->child[bit];
            cur->cnt++;
        }
    }

    bool search(int num){
        BinaryTrie* cur = this;
        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(!cur->child[bit]) return false;
            cur = cur->child[bit];
        }
        return true;
    }

    int findMaxXOR(int num){
        int ret = 0;
        BinaryTrie* cur = this;
        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(cur->child[1 - bit]){
                ret |= (1<<shift);
                cur = cur->child[1-bit];
            }
            else{
                cur = cur->child[bit];
            }
        }
        return ret;
    }

    int countValid(int num , int mx){
        BinaryTrie* cur = this;
        int res = 0;
        bool same = true;
        for(int shift = MAX_BITS ; shift >= 0 && cur ; shift--){
            int bit = (num>>shift)&1;
            int mxbit = (mx>>shift)&1;
            if(mxbit && cur->child[bit]) res+=cur->child[bit]->cnt  + (same ? -1 : 0);
            if(mxbit) cur = cur->child[1-bit],same=false;
            else cur = cur->child[bit];
        }
        return res;
    }
    

};


class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        BinaryTrie trie;
        for(auto num : nums) trie.insert(num);
        int cnt = 0;
        for(auto num : nums){
            int l = trie.countValid(num,low);
            int r = trie.countValid(num,high+1);
            cnt+=(r-l);
        }
        return cnt/2;
    }
};