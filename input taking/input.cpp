#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);


    long double a = 22;
    long double b = 7;
    cout << fixed << setprecision(7) << a / b;

    string s;
    while (cin >> s) {
        if (s == "stop") break;
        cout << s << endl;
    }

    string s;
    while (true) {
        cin >> s;
        if (s == "stop") break;
        cout << s << endl;
    }

    a % b = a - (a / b) * b

    10 / 3 = 3.333...
    C++ → 3
    Truncated toward zero

    -10 - (-10 / 3) * 3 = -1
    -10 - (-10 / -3) * -3 = -1
    10 - (10 / -3) * -3 = 1
    cout << -10 % 3 << ' ' << -10 % -3 << ' ' << 10 % (-3) << endl;

    cout << round(12.555) << endl;
    cout << cbrt(8) << endl;


    string s = "c++ is not that bad"; // >> string reads a token (word) separated by whitespace.
    string s = "1309 56"; 
    stringstream ss(s);

    string word;
    int num;
    while (ss >> word) {
        cout << word << endl;
        num = stoi(word); // string to int -> "12" -> 12 all
        cout << num << endl;
    }


    string s;
    getline(cin, s);
    stringstream ss(s);
    char ch; // ss >> ch reads one non-whitespace character at a time. Think take string -> iterate char of strings for (char ch : s)
    while (ss >> ch) {
        if (isdigit(ch)) { // takes char
            cout << ch << endl;
        }
    }


    string s;
    getline(cin, s);
    stringstream ss(s);
    int num;
    while (ss >> num) { // If character is NOT valid for an integer → FAILS immediately, [ fails stops
        cout << num << endl;
    }


    string s;
    getline(cin, s);

    // Convert seperators -> spaces 
    for (char &ch : s) { // & is imp for changing, ref
        if (!isdigit(ch)) ch = ' '; // use when 1, 2, 11, 12, 30 -> 1 2 11 12 30
    }

    stringstream ss(s);
    int num;
    while (ss >> num) {
        cout << num << endl;
    }

    (!isdigit(c) && c != '-')

    string s;
    getline(cin, s);
    stringstream ss(s);

    char ch;
    int num;

    while (ss >> ch) {
        if (isdigit(ch)) {
            ss.putback(ch);   // return digit
            ss >> num;        // read full integer
            cout << num << endl;
        }
    }

    for inputs like this Case1 : [1, 2, 3, 4] -> 1 1 2 3 4 -> remove the first 1

    if (isalpha(ch)) {
    std::cout << ch << " is an alphabet." << std::endl;
    }

    A is an alphabet.
    1 is not an alphabet.
    + is not an alphabet.

    to_string, islower



    if (s.find(x) == string::npos) // if not found



    string s;
    getline(cin, s);

    // Preserve float-compatible characters
    for (char &c : s) {
        if (!isdigit(c) && c != '.' && c != '-' && c != '+')
            c = ' ';
    }

    stringstream ss(s);

    double x;
    while (ss >> x) {
        cout << x << endl;
    }
    +1, 6, -1.5 -> 1 6 -1.5 -> not +1, as taking input as int double/ numeric 1

    return 0;
}
