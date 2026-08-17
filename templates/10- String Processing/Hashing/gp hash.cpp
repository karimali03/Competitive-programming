using namespace __gnu_pbds;
#include <ext/pb_ds/assoc_container.hpp>

// custom hash (instead of default)
struct CustomHash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        // Use high-precision clock as a random seed
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


// This is the custom hash struct for pairs
struct PairHash {
    template <class T1, class T2>
    size_t operator () (const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);

        // A good way to combine two hashes
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};


int main() {
    // How to use it:
    // gp_hash_table<Key, Value, YourHashStruct>
    
    // Map with a pair as the key
    gp_hash_table<pair<int, int>, string, PairHash> map_with_pair_key;

    // Set of pairs
    gp_hash_table<pair<int, int>, null_type, PairHash> set_of_pairs;

    map_with_pair_key[{10, 20}] = "Hello";
    set_of_pairs.insert({30, 40});

    cout << map_with_pair_key[{10, 20}] << endl;
}
