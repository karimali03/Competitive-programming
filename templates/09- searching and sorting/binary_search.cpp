// attention !! :  r is like end is Standard library
int lower_bound(vector<int>& v, int start, int end, int val) {
    int l = start, r = end;

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (v[mid] < val) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}

int upper_bound(vector<int>& v, int start, int end, int val) {
    int l = start, r = end;

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (v[mid] <= val) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

   
    return l;
}
