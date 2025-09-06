#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_multiset typedef tree<int , null_type ,  less_equal<int> , rb_tree_tag , tree_order_statistics_node_update>

// find_by_order(k): returns an iterator to the kth element (counting from zero) in the set
// order_of_key : returns to the number of items that are strictly smaller than our item k
ordered_set o_set; 
o_set.insert(2); 
*(o_set.find_by_order(1)) 
o_set.order_of_key(5) 

if (o_set.find(2) != o_set.end()) 
	o_set.erase(o_set.find(2)); 

