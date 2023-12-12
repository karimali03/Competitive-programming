#include<iostream>
#include<cstring>	// memset
#include<map>
#include<vector>
using namespace std;

class  trie
{
private:
    map<char,trie*>child;
    bool isLeaf {};
public:
     trie(){};

    void insert(string str , int i = 0) {
          trie* ptr=this;
          int n=str.size();
        for(;i<n;i++){
            if(!ptr->child.count(str[i])) ptr->child[str[i]]=new trie();  
             ptr=ptr->child[str[i]];
             if(i==n-1) ptr->isLeaf=true;
        }

	}

	bool word_exist(string str) {
        int n=str.size();
        auto ptr=this; // pointer to current class
		for(int i=0;i<n;i++){
            if(!ptr->child.count(str[i])) return false;
            ptr=ptr->child[str[i]];
        }
        return ptr->isLeaf;
	}

	bool prefix_exist(string str) {
		int n=str.size();
        auto ptr=this;
		for(int i=0;i<n;i++){
            if(!ptr->child.count(str[i])) return false;
            ptr=ptr->child[str[i]];
        }
        return true;
	}

    void auto_complete(string s,vector<string> & res){
        trie* ptr=this;
        for(int i=0;i<s.size();i++){
            ptr = ptr->child[s[i]];
        }
        ptr->get_all_strings(res,s);
    }
    
    void get_all_strings(vector<string> & res ,string s=""){
        if(isLeaf) res.push_back(s);
        for(auto & x : child){
            x.second->get_all_strings(res,s+x.first);
        }
    }
};

int main() {
	trie tree;

    tree.insert("abcd");
	tree.insert("abxyz");
	tree.insert("a");
	tree.insert("ab");
	tree.insert("abxyzw");
	tree.insert("bcd");

	vector<string> res;
	tree.auto_complete("ab",res);
	for (int i = 0; i < (int) res.size(); ++i)
		cout << res[i] << "\n";
	return 0;
}