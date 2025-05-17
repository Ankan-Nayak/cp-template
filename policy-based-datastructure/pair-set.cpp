
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
using namespace std;
using namespace __gnu_pbds;
template <class T> using Ordered_set = tree<T, null_type, 
less<T>, rb_tree_tag,tree_order_statistics_node_update>;
int main() {
    Ordered_set <pair<int,int> > a;
    a.insert({1,0});
    a.insert({12,0});
    a.insert({17,78});
    a.insert({17,40});
    a.insert({112,22});
    a.insert({7,12});
    a.insert({9,112});
    cout << (a.find_by_order(2))->first<<" "<<(a.find_by_order(2))->second << endl; //output is 9 112
    cout << (a.find_by_order(5))->first<<" "<<(a.find_by_order(5))->second << endl; //output is 17 78
    cout << (a.order_of_key({10,12})) << endl; //output is 3
    cout << (a.order_of_key({12,0})) << endl; //output is 3
    cout << (a.order_of_key({12,1})) << endl; //output is 4
}