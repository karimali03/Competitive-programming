/*
============================================================
Hidden Probability — Beta/Bayesian CP Cheat Sheet
============================================================

1) p is known:
    P(success) = p

2) New random p every trial:
    p ~ Uniform(0,1)
    P(success) = E[p] = 1/2

3) ONE hidden p chosen once and reused:
    observations matter
    -> Beta-Bernoulli
*/


/*
Beta-Bernoulli

Prior:
    p ~ Beta(A, B)

After:
    s successes
    f failures

Posterior:
    p ~ Beta(A+s, B+f)

Next success probability:

             A + s
    P = -----------------
        A + B + s + f
*/

struct Beta {
    double A, B;

    Beta(double A = 1, double B = 1) : A(A), B(B) {}

    void success() { A++; }
    void failure() { B++; }

    double next_prob() {
        return A / (A + B);
    }
};


/*
Uniform(0,1) = Beta(1,1)

After s successes, f failures:

             s + 1
    P = ---------------
          s + f + 2
*/

double next_prob(int success, int failure) {
    return double(success + 1) /
           (success + failure + 2);
}


/*
If:
    day = total observations
    s   = successes

then:
    failures = day - s

             s + 1
    P = -------------
          day + 2
*/

double next_prob_day(int day, int success) {
    return double(success + 1) / (day + 2);
}


/*
General Beta(A,B):

             A + s
    P = -----------------
        A + B + s + f
*/

double next_prob(
    double A, double B,
    int s, int f
) {
    return (A + s) / (A + B + s + f);
}


/*
============================================================
DP Pattern
============================================================

Hidden p chosen ONCE and reused:

    dp[day][state]               // may be WRONG

Use:

    dp[day][state][success]

because different success counts => different next probability.

Uniform prior:

    p = (success + 1.0) / (day + 2)
*/


/*
Transition:

    p = P(success next)

success:
    prob *= p
    success++

failure:
    prob *= 1-p
    success unchanged

day always increases.
*/

void generic_dp(int N) {
    vector<double> dp(N + 1), ndp(N + 1);

    dp[0] = 1;

    for (int day = 0; day < N; day++) {
        fill(ndp.begin(), ndp.end(), 0);

        for (int s = 0; s <= day; s++) {
            double p = double(s + 1) / (day + 2);

            ndp[s + 1] += dp[s] * p;
            ndp[s]     += dp[s] * (1 - p);
        }

        dp.swap(ndp);
    }
}


/*
============================================================
Indirect Observation
============================================================

If:

    event happens -> you die

and DP state means you are alive,

then reaching the state implies:

    event did NOT happen

So it counts as a failure observation.
*/


/*
============================================================
Door / Ferret Example
============================================================

day = previous hours
g   = giant appearances

Uniform hidden probability:

               g + 1
    P(giant) = -------
               day+2
*/

double giant_prob(int day, int g) {
    return double(g + 1) / (day + 2);
}


/*
HIDE:

giant:
    prob *= pg
    g++

no giant:
    prob *= 1-pg
*/


/*
SEARCH:

giant -> die

Only no-giant survives:

    prob *= 1-pg
    g unchanged
    day++

This records one failure observation.
*/
