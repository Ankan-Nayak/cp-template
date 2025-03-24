string Decimal_To_Base(int n, int base){
    string s;
    while(n != 0){
        s.push_back((n % base) +'0');
        n /= base;
    }
    reverse(s.begin(), s.end());
    return s;
}