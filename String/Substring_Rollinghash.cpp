/*
    ROLLING HASH LOGIC
    ------------------
2 hash to avoid collision


    Suppose:
        nums = [a, b, c, d]

    Polynomial hash:

        H = a * p^0 + b * p^1 + c * p^2 + d * p^3

    Prefix hash:

        pref[i] = nums[0] * p^0
                + nums[1] * p^1
                + ...
                + nums[i] * p^i

    Hash of subarray [l, r]:

        hash(l, r) = pref[r] - pref[l - 1]

        = nums[l] * p^l
        + nums[l+1] * p^(l+1)
        + ...
        + nums[r] * p^r

    But we want the hash to start from power 0:

        normalized_hash(l, r) = hash(l, r) / p^l

        = nums[l] * p^0
        + nums[l+1] * p^1
        + ...
        + nums[r] * p^(r-l)

    Since modular division is not directly possible:

        a / b (mod M) = a * inverse(b) (mod M)

        Therefore:

        normalized_hash = hash(l, r) * inverse(p^l) % M

    Modular inverse using Fermat's Little Theorem:

        inverse(a) = a^(M-2) % M

    This works when M is prime and a is not divisible by M.

    We use two hashes to reduce collision probability.
*/

class Solution {
public:
    const int mod1 = 1e9 + 7;
    const int mod2 = 998244353;

    // Binary Exponentiation: a^b % mod
    long long pw(long long a, long long b, long long mod) {
        long long res = 1;

        while (b) {
            if (b % 2 == 1) {
                res = (res * a) % mod;
            }

            a = (a * a) % mod;
            b /= 2;
        }

        return res;
    }

    // Modular Inverse using Fermat's Little Theorem
    // a^(-1) = a^(mod-2) % mod
    long long inv(long long a, long long mod) {
        return pw(a, mod - 2, mod);
    }

    int smallestUniqueSubarray(vector<int>& nums) {
        long long primePW1 = 31;
        long long primePW2 = 100003;

        int n = nums.size();

        vector<long long> rollH1(n + 1, 0);
        vector<long long> pww1(n + 1, 0);
        vector<long long> invpww1(n + 1, 0);

        vector<long long> rollH2(n + 1, 0);
        vector<long long> pww2(n + 1, 0);
        vector<long long> invpww2(n + 1, 0);

        // Precompute powers of p
        // pww[i] = p^i % mod

        pww1[0] = 1;
        pww2[0] = 1;

        for (int i = 1; i <= n; ++i) {
            pww1[i] = (pww1[i - 1] * primePW1) % mod1;
            pww2[i] = (pww2[i - 1] * primePW2) % mod2;
        }

        // Precompute inverse powers of p
        // invpww[i] = inverse(p^i) % mod
        //
        // inverse(p^i) = inverse(p)^i

        invpww1[0] = 1;
        invpww2[0] = 1;

        long long i1 = inv(primePW1, mod1);
        long long i2 = inv(primePW2, mod2);

        for (int i = 1; i <= n; ++i) {
            invpww1[i] = (invpww1[i - 1] * i1) % mod1;
            invpww2[i] = (invpww2[i - 1] * i2) % mod2;
        }

        // Build prefix rolling hashes
        //
        // rollH[i] = nums[0]*p^0 + nums[1]*p^1
        //          + ... + nums[i]*p^i

        for (int i = 0; i < n; ++i) {
            long long value = (nums[i] * pww1[i]) % mod1;

            rollH1[i] = value;

            if (i > 0) {
                rollH1[i] = (rollH1[i] + rollH1[i - 1]) % mod1;
            }
        }

        for (int i = 0; i < n; ++i) {
            long long value = (nums[i] * pww2[i]) % mod2;

            rollH2[i] = value;

            if (i > 0) {
                rollH2[i] = (rollH2[i] + rollH2[i - 1]) % mod2;
            }
        }

        auto check = [&](int mid) -> bool {

            // Hash -> frequency
            map<long long, int> mp;

            for (int r = mid - 1; r < n; ++r) {

                int l = r - mid + 1;

                // ---------------------------------
                // HASH 1
                // ---------------------------------

                long long res1 = rollH1[r];

                // Subtract prefix hash before l
                if (l > 0) {
                    res1 = (res1 - rollH1[l - 1] + mod1) % mod1;
                }

                // Normalize: divide by p^l
                // Division = multiplication by modular inverse
                res1 = (res1 * invpww1[l]) % mod1;


                // ---------------------------------
                // HASH 2
                // ---------------------------------

                long long res2 = rollH2[r];

                if (l > 0) {
                    res2 = (res2 - rollH2[l - 1] + mod2) % mod2;
                }

                res2 = (res2 * invpww2[l]) % mod2;


                // Combine both hashes
                mp[res1 * mod1 + res2]++;
            }

            // Check if any subarray hash occurs exactly once
            for (auto it : mp) {
                if (it.second == 1) {
                    return true;
                }
            }

            return false;
        };

        // Binary Search on answer

        int lo = 1, h = n, ans = 1;

        while (lo <= h) {
            int mid = lo + (h - lo) / 2;

            if (check(mid)) {
                ans = mid;
                h = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        return ans;
    }
};