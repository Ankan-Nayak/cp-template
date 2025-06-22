long long mod_add(long long a, long long b, long long m) {
    return ((a % m + m) % m + (b % m + m) % m) % m;
}

long long mod_minus(long long a, long long b, long long m) {
    return ((a % m + m) % m - (b % m + m) % m + m) % m;
}

long long mod_mul(long long a, long long b, long long m) {
    return ((a % m + m) % m * (b % m + m) % m) % m;
}

int nCr_mod2(int n, int r) {
    return ((n & r) == r) ? 1 : 0;
}

long long binpow(long long a, long long b, long long m) {
    a = (a % m + m) % m; // ensure positive
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// Modular division: a / b mod m
// Assumes m is prime
long long modulo_div(long long a, long long b, long long m) {
    return mod_mul(a, binpow(b, m - 2, m), m);
}

long long mod_inv(long long b, long long m) {
    return binpow(b, m - 2, m);
}


// Super_Pow: a^(b^c) mod MOD
// even for (a^b)^c = a^(b*c) = binpow(a, mod_mul(b, c, MOD - 1), MOD)
long long Super_Pow(long long a, long long b, long long c, long long m) {
    long long exponent = binpow(b, c, m - 1); // Use Euler or Fermat for prime MOD
    return binpow(a, exponent, m);
}
