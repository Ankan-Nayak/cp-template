class Solution {
public:
    int reverse(int x) {
        int org = x;
        string s = to_string(org);
        std::reverse(s.begin(), s.end());
        long long newValue = stoll(s);
        if (org < 0) newValue *= -1;
        if (newValue < -(1LL << 31) || newValue > (1LL << 31)) return 0;
        return newValue;
    }
};