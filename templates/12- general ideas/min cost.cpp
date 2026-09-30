2) ONE-DIRECTIONAL CHANGES -> EXTREMAL FEASIBLE SOLUTION
============================================================

General principle:

    If the cost is exactly the amount you change,
    and changes are allowed in only one direction,
    find the extremal feasible solution.

------------------------------------------------------------
CASE A: You may only DECREASE values
------------------------------------------------------------

Suppose:

    cost = sum(original[i] - new[i])

and:

    new[i] <= original[i]

To MINIMIZE the cost, make every new[i] as LARGE as possible
while still satisfying all constraints.

Example constraint:

    new[i] <= new[i-1] + K

Then the optimal greedy choice is:

    new[i] = min(original[i], new[i-1] + K);

Why?

Any smaller value is also feasible, but causes extra cost.
So the largest feasible value is always optimal.


Typical code:

    long long cost = 0;

    new_a[L] = a[L];

    for (int i = L + 1; i <= R; i++) {
        new_a[i] = min(a[i], new_a[i-1] + K);
        cost += a[i] - new_a[i];
    }


------------------------------------------------------------
CASE B: You may only INCREASE values
------------------------------------------------------------

Suppose:

    cost = sum(new[i] - original[i])

and:

    new[i] >= original[i]

To MINIMIZE the cost, make every new[i] as SMALL as possible
while satisfying the constraints.

For example, if:

    new[i] >= new[i-1] + K

then:

    new[i] = max(original[i], new[i-1] + K);

