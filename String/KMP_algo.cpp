
class Solution {
public:
    vector<int> buildLPS(string b) {
        vector<int> lps(b.size(), 0);
        int len = 0;
        for (int i = 1; i < b.size();) {
            if (b[i] == b[len]) {
                lps[i] = ++len;
                i++;
            } else if (len > 0) {
                len = lps[len - 1];
            } else {
                i++;
            }
        }
        return lps;
    }
    bool KMP(string a, string b) {
        if (b.empty()) return true;
        vector<int> lps = buildLPS(b);
        int j = 0;
        for (int i = 0; i < a.size();) {
            if (a[i] == b[j]) {
                i++;
                j++;
                if (j == b.size()) {
                    return true;
                }
            } else if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }

        } 
        return false;
    }
    int repeatedStringMatch(string a, string b) {
        string s = "";
        int ct = 0;
        while (s.size() < b.size()) {
            s += a;
            ct += 1;
        }

        bool ans = KMP(s, b);
        if (ans) return ct;

        s += a;
        ans = KMP(s, b);
        if (ans) return ct + 1;

        s += a;
        ans = KMP(s, b);
        if (ans) return ct + 2;

        return -1;
        
    }
};


/*
`lps[len-1]` is the **next-longest border** (a prefix that is also a suffix) of the prefix you've already matched.

**Setup:** You've matched `b[0..len-1]` as a suffix ending at `i-1`. That means `b[0..len-1]` is a prefix AND a suffix of `b[0..i-1]`. Now `b[i] != b[len]`, so this border can't be extended.

**The question:** What's the next best (shorter) prefix that is also a suffix ending at `i-1`?

Any shorter candidate must:
1. be a suffix of `b[0..i-1]`, and
2. be a prefix of `b`.

Since the matched part `b[0..len-1]` itself ends at `i-1`, any suffix of `b[0..i-1]` that's shorter than `len` is also a suffix of `b[0..len-1]`. And it must also be a prefix of `b`. So the candidates are exactly the **borders of the string `b[0..len-1]`**.

And the longest border of `b[0..len-1]` is, by definition, `lps[len-1]`.

**Example:** `b = "aabaaac"`, say we're at `i=6` (`'c'`), with `len=3` (matched `"aab"`... let's use a cleaner one: matched `"aaba"`, len=4).

- Borders of `"aaba"`: `"a"` (length 1). So `lps[3] = 1`.
- We jump `len = 1`, meaning "fall back to matching just `"a"`", then retry comparing `b[i]` with `b[1]`.

**Why not `len-2` or something else?**
- `lps[len-1]` gives the longest valid fallback, so you don't skip a possible match.
- Shorter borders are reached automatically, because if `lps[len-1]` also fails, you apply `lps` again on it (chain: `len → lps[len-1] → lps[lps[len-1]-1] → ...`) until `len = 0`.

**Why index `len-1` and not `len`?**
`lps[k]` describes the prefix of length `k+1` (indices `0..k`). The matched prefix has length `len`, so its last index is `len-1`.

**Intuition:** you never restart from scratch. You reuse what you already know about `b` against itself, which is why the whole thing is O(m): `len` goes up at most once per `i`, and every fallback decreases it.
*/