#include <ext/rope>
using namespace __gnu_cxx;

/*
==================== ROPE ====================

Use when you need many edits in the middle of a sequence/string.

Main operations:
    insert(pos, value)       ~ O(log n)
    erase(pos, len)          ~ O(log n)
    substr(pos, len)         ~ O(log n + len)
    s[i]                     ~ O(log n)

GNU extension, not standard STL.
*/

void rope_template() {
    rope<char> s("abcdef");

    // insert
    s.insert(3, "XYZ");              // abcXYZdef
    s.insert(0, "START");            // STARTabcXYZdef

    // erase [pos, pos + len)
    s.erase(2, 3);

    // access
    char c = s[4];

    // size
    int n = s.size();

    // substring
    rope<char> part = s.substr(2, 5);

    // replace = erase + insert
    int pos = 2, len = 3;
    s.erase(pos, len);
    s.insert(pos, "HELLO");

    // convert rope -> string
    string str;
    str.resize(s.size());
    s.copy(0, s.size(), str.data());

    cout << str << '\n';
}
