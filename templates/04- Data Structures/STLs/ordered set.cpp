#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
using ordered_multiset = tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>;


// find_by_order(k): returns an iterator to the kth element (counting from zero) in the set
// order_of_key : returns to the number of items that are strictly smaller than our item k
ordered_set o_set; 
o_set.insert(2); 
*(o_set.find_by_order(1)) 
o_set.order_of_key(5) 

if (o_set.find(2) != o_set.end()) 
	o_set.erase(o_set.find(2)); 
	
	
	
	
	
	
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> pbds;

struct ordered_multiset {
    pbds t;
    int timer = 0;

    // Insert: Adds element with a unique timestamp
    void insert(int x) {
        t.insert({x, timer++});
    }

    // Erase: Removes ONE instance of x
    // Uses lower_bound to find the first instance of x
    bool erase(int x) {
        auto it = t.lower_bound({x, -1});
        if (it != t.end() && it->first == x) {
            t.erase(it);
            return true;
        }
        return false;
    }

    // Order of Key: Count of elements STRICTLY less than x
    int order_of_key(int x) {
        return t.order_of_key({x, -1});
    }

    // Find by Order: Value at index k (0-based sorted)
    // Returns -1 (or any sentinel) if k is out of bounds
    int find_by_order(int k) {
        if (k >= (int)t.size()) return -1;
        return t.find_by_order(k)->first;
    }

    // Size
    int size() { return t.size(); }
    
    // Clear
    void clear() { t.clear(); timer = 0; }
};

