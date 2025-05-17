#include <bits/stdc++.h>
using namespace std;

// Header files, namespaces,
// macros as defined above
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
// #define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

// #define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update> 
// #define ordered_multiset tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>  /*ordered_multiset o_set*/

// typedef tree<string, null_type, less<string>, rb_tree_tag, tree_order_statistics_node_update> ordered_set_string;
// for inserting string rather than int

// #define ll long long
// for ordered multiset , notice less_equal



// Find won't work in less_equal, so use find_by_order(order_of_key(a[i]))
// multiset, pair set possible -> returns pos & index in set

signed main()
{
    ordered_set o_set;

    o_set.insert(5);
    o_set.insert(1);
    o_set.insert(2);

    // Finding the second smallest element
    // in the set using * because
    //  find_by_order returns an iterator
    cout << *(o_set.find_by_order(1)) << endl;

    // Finding the number of elements strictly less than k=4
    cout << o_set.order_of_key(4) << endl;

    // Finding the count of elements less 
    // than or equal to 4 i.e. strictly less
    // than 5 if integers are present
    cout << o_set.order_of_key(5) 
         << endl;

    // Deleting 2 from the set if it exists
    if (o_set.find(2) != o_set.end())
        o_set.erase(o_set.find(2));

    // Now after deleting 2 from the set
    // Finding the second smallest element in the set
    cout << *(o_set.find_by_order(1)) 
         << endl;

    // Finding the number of
    // elements strictly less than k=4
    cout << o_set.order_of_key(4) 
         << endl;



    // Note:Upper Bound would work as lower bound and vice versa
    // To check existence use lower_bound
    auto lb = o_set.lower_bound(2);
    if (lb != o_set.end()) cout << "Lower bound of 2: " << *lb << endl;

    auto ub = o_set.upper_bound(2);
    if (ub != o_set.end()) cout << "Upper bound of 2: " << *ub << endl;

    return 0;
}