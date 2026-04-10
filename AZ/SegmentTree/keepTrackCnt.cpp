#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector<pair<ll, ll>> tree;
vector<ll> arr;

void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx].first = arr[l];
        tree[idx].second = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(idx * 2 + 1, l, mid);
    build(idx * 2 + 2, mid + 1, r);
    tree[idx].first = min(tree[idx * 2 + 1].first, tree[idx * 2 + 2].first);
    tree[idx].second = 0;
    if (tree[idx * 2 + 1].first == tree[idx].first) tree[idx].second += tree[idx * 2 + 1].second;
    if (tree[idx * 2 + 2].first == tree[idx].first) tree[idx].second += tree[idx * 2 + 2].second;
}

pair<ll, ll> query(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return {LLONG_MAX, 0};
    if (l >= ql && r <= qr) return tree[idx];
    int mid = (l + r) / 2;
    auto leftRes = query(idx * 2 + 1, l, mid, ql, qr);
    auto rightRes = query(idx * 2 + 2, mid + 1, r, ql, qr);

    pair<ll, ll> ans;
    ans.first = min(leftRes.first, rightRes.first);
    ans.second = 0;
    if (leftRes.first == ans.first) ans.second += leftRes.second;
    if (rightRes.first == ans.first) ans.second += rightRes.second;

    return ans;
}

void update(int idx, int l, int r, int pos, int val) {
    if (l == r) {
        arr[l] = val;
        tree[idx] = {val, 1};
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(idx * 2 + 1, l, mid, pos, val);
    } else {
        update(idx * 2 + 2, mid + 1, r, pos, val);
    }
    tree[idx].first = min(tree[idx * 2 + 1].first, tree[idx * 2 + 2].first);
    tree[idx].second = 0;
    if (tree[idx * 2 + 1].first == tree[idx].first) tree[idx].second += tree[idx * 2 + 1].second;
    if (tree[idx * 2 + 2].first == tree[idx].first) tree[idx].second += tree[idx * 2 + 2].second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n, q;
    cin >> n >> q;
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    tree.resize(4 * n, {0, 0});
    build(0, 0, n-1);

    while (q--) {
        int op;
        cin >> op;

        if (op == 2) {
            int l, r;
            cin >> l >> r;
            auto p = query(0, 0, n-1, l, r-1);
            cout << p.first << ' ' << p.second  << '\n';
        } 

        if (op == 1) {
            int pos, val;
            cin >> pos >> val;
            update(0, 0, n-1, pos, val);
        }
    }
    
    return 0;
}



/*___________________________________________________________________________________________________________________________________*/
#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector<pair<ll,ll>> tree;
vector<ll> arr;

// 🔥 Merge function (core idea)
pair<ll,ll> merge(pair<ll,ll> a, pair<ll,ll> b) {
    if (a.first < b.first) return a;
    if (b.first < a.first) return b;
    return {a.first, a.second + b.second};
}

// Build
void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = {arr[l], 1};
        return;
    }
    int mid = (l + r) / 2;
    build(2*idx+1, l, mid);
    build(2*idx+2, mid+1, r);
    tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);
}

// Query
pair<ll,ll> query(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return {LLONG_MAX, 0};
    if (l >= ql && r <= qr) return tree[idx];

    int mid = (l + r) / 2;
    auto left = query(2*idx+1, l, mid, ql, qr);
    auto right = query(2*idx+2, mid+1, r, ql, qr);

    return merge(left, right);
}

// Update
void update(int idx, int l, int r, int pos, ll val) {
    if (l == r) {
        arr[l] = val;
        tree[idx] = {val, 1};
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2*idx+1, l, mid, pos, val);
    else update(2*idx+2, mid+1, r, pos, val);

    tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    tree.resize(4*n);
    build(0, 0, n-1);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int pos; ll val;
            cin >> pos >> val;
            update(0, 0, n-1, pos, val);
        } 
        else {
            int l, r;
            cin >> l >> r;
            auto ans = query(0, 0, n-1, l, r-1);
            cout << ans.first << " " << ans.second << "\n";
        }
    }

    return 0;
}


/************************************************************************************************* */


#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct Node {
    ll mn;
    ll cnt;
};

vector<Node> tree;
vector<ll> arr;

// 🔥 Merge function
Node merge(Node a, Node b) {
    if (a.mn < b.mn) return a;
    if (b.mn < a.mn) return b;
    return {a.mn, a.cnt + b.cnt};
}

// Build
void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = {arr[l], 1};
        return;
    }
    int mid = (l + r) / 2;
    build(2*idx+1, l, mid);
    build(2*idx+2, mid+1, r);
    tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);
}

// Query
Node query(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return {LLONG_MAX, 0};
    if (l >= ql && r <= qr) return tree[idx];

    int mid = (l + r) / 2;
    Node left = query(2*idx+1, l, mid, ql, qr);
    Node right = query(2*idx+2, mid+1, r, ql, qr);

    return merge(left, right);
}

// Update
void update(int idx, int l, int r, int pos, ll val) {
    if (l == r) {
        arr[l] = val;
        tree[idx] = {val, 1};
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2*idx+1, l, mid, pos, val);
    else update(2*idx+2, mid+1, r, pos, val);

    tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    tree.resize(4*n);
    build(0, 0, n-1);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int pos; ll val;
            cin >> pos >> val;
            update(0, 0, n-1, pos, val);
        } 
        else {
            int l, r;
            cin >> l >> r;
            Node ans = query(0, 0, n-1, l, r-1);
            cout << ans.mn << " " << ans.cnt << "\n";
        }
    }

    return 0;
}



/*___________________________________________________________________________________________________________________________*/


/*When DO we use new Node(...)?
You use new when working with pointers / dynamic memory, like:
✅ Case 1: Pointer-based segment tree

Node* left;
👉 left is a pointer (address)
👉 It stores location of a Node, not the node itself
🔥 Two different things
Expression	Meaning
left	pointer (address)
*left	actual object (Node)


✅ Using object (. operator)
x.mn
👉 Use . when you have actual object
✅ Using pointer (-> operator)
ptr->mn
👉 Use -> when you have pointer
✅ Equivalent form
(*ptr).mn
👉 This is SAME as:
ptr->mn
🔥 Key Rule
ptr->member  ==  (*ptr).member
⚠️ Why parentheses needed?
*ptr.mn   ❌ WRONG
Because:
. has higher priority than *
So correct is:
(*ptr).mn  ✅



Node* left = build(l, mid);
✅ What is left?
👉 left is a pointer (Node*)
Type = Node*
It stores address of a Node*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct Node {
    ll mn, cnt;
    Node *left, *right;

    Node(ll v = LLONG_MAX, ll c = 0) {
        mn = v;
        cnt = c;
        left = right = NULL;
    }
};

vector<ll> arr;

// 🔥 Merge function
Node merge(Node a, Node b) {
    if (a.mn < b.mn) return a;
    if (b.mn < a.mn) return b;
    return Node(a.mn, a.cnt + b.cnt);
}

// Build
Node* build(int l, int r) {
    if (l == r) {
        return new Node(arr[l], 1);
    }
    int mid = (l + r) / 2;
    Node* left = build(l, mid);
    Node* right = build(mid+1, r);

    Node* cur = new Node();
    Node res = merge(*left, *right);
    cur->mn = res.mn;
    cur->cnt = res.cnt;
    cur->left = left;
    cur->right = right;

    return cur;
}

// Query
Node query(Node* node, int l, int r, int ql, int qr) {
    if (!node || ql > r || qr < l) return Node(LLONG_MAX, 0);

    if (l >= ql && r <= qr) return *node;

    int mid = (l + r) / 2;
    Node left = query(node->left, l, mid, ql, qr);
    Node right = query(node->right, mid+1, r, ql, qr);

    return merge(left, right);
}

// Update
Node* update(Node* node, int l, int r, int pos, ll val) {
    if (l == r) {
        return new Node(val, 1);
    }

    int mid = (l + r) / 2;

    Node* newNode = new Node();
    
    if (pos <= mid) {
        newNode->left = update(node->left, l, mid, pos, val);
        newNode->right = node->right;
    } else {
        newNode->left = node->left;
        newNode->right = update(node->right, mid+1, r, pos, val);
    }

    Node res = merge(*newNode->left, *newNode->right);
    newNode->mn = res.mn;
    newNode->cnt = res.cnt;

    return newNode;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    Node* root = build(0, n-1);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int pos; ll val;
            cin >> pos >> val;
            root = update(root, 0, n-1, pos, val);
        } 
        else {
            int l, r;
            cin >> l >> r;
            Node ans = query(root, 0, n-1, l, r-1);
            cout << ans.mn << " " << ans.cnt << "\n";
        }
    }

    return 0;
}