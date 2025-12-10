#include <bitset>
#include <iostream>
using namespace std;

int main()
{
    // declaring an uninitialized bitset object
    bitset<8> uninitializedBitset; // Uninitialized bitset: 00000000

    // initialization with decimal number
    bitset<8> decimalBitset(15); // Initialized with decimal: 00001111

    // initialization with binary string
    bitset<8> stringBitset(string("1111")); // Initialized with string: 00001111

    /*
        set()        Set the bit value at the given index to 1.
        reset()      Set the bit value at a given index to 0.
        flip()       Flip the bit value at the given index.
        count()      Count the number of set bits.
        test()       Returns the boolean value at the given index.
        any()        Checks if any bit is set.
        none()       Checks if none bit is set.
        all()        Check if all bit is set.
        size()       Returns the size of the bitset.
        to_string()  Converts bitset to std::string.
        to_ulong()   Converts bitset to unsigned long.
        to_ullong()  Converts bitset to unsigned long long.
             
    */

    return 0;
}
