/* Given a bitmask  
$m$ , you want to efficiently iterate through all of its submasks, that is, masks  
$s$  in which only bits that were included in mask  
$m$  are set.
*/
for (int s = m; s ; s = (s-1)&m ) {
    ... you can use s ...
}

// iterate over all masks and submasks in O(N^3)
for (int m = 0; m < (1<<n); ++m) {
    for (int s = m; s; s = (s-1) & m) {
        // use s and m (s ≠ 0)
    }
    // handle s = 0
    // use 0 and m
}

