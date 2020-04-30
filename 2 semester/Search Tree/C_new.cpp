/***
 * Author: Kozhukharov Nikita
 * Декартово дерево по неявному ключу.
 * Удобнее использовать функции сплит и мерж,
 * если передавать им указатели на результат
 * (чтобы не писать название pair<node *, node *> и не
 * выносить его в качестве typedef).
 */
#include <iostream>
#include <climits>
// определяет константы с ограничениями целочисленного типа данных для конкретной системы и компилятора
#include <vector>

using namespace std;

#define null nullptr

struct node {
    int size;
    int prior;
    int data;
    bool isFree;

    node* left, * right;

    node( int data = 0, bool isZero = true ) : data(data), isFree(isZero), size(1) {
        prior = rand() * rand();
        left = right = nullptr;
    }
};

struct Treap {
    node * root;
    int num = 0;

    Treap( int k = -1 ) : root(null) { if (k != -1) build(k); }

    node * merge( node * l, node * r ) {
        if (l == null) return r;
        if (r == null) return l;

        if (l->prior > r->prior) {
            l->right = merge(l->right, r);
            updateSize(l);
            updateZero(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            updateSize(r);
            updateZero(r);
            return r;
        }
    }

    void split(node * t, int key, node * &l, node * &r) {
        if (t == null) {
            l = r = null;
            return;
        }
        if (getSize(t->left) < key) {
            split(t->right, key - getSize(t->left) - 1, t->right, r);
            l = t;
        } else {
            split(t->left, key, l, t->left);
            r = t;
        }
        updateSize(t);
        updateZero(t);
    }

    int getSize( node * t ) {
        if (t == null) return 0;
        return t->size;
    }

    node * updateSize( node * t ) {
        if (t != null)
            t->size = getSize(t->left) + getSize(t->right) + 1;
        return t;
    }

    node * updateZero( node * t ) {
        if (t != null)
            t->isFree = getZero(t->left) || getZero(t->right) || (t->data == 0);
        return t;
    }

    bool getZero( node * t ) {
        if (t == null) return false;
        return t->isFree;
    }

    int getData( node * t ) {
        if (t == null) return -1;
        return t->data;
    }

    void toArray( node * node, vector<int> & a ) {
        if (node != null) {
            toArray(node->left, a);
            a.push_back(getData(node));
            toArray(node->right, a);
        }
    }

    void build( int n ) {
        for (int i = 0; i < n; ++i)
            root = merge(new node, root);
    }

    node * remove( node * r, int key ) {
        node* t1, * t2, * t3;
        split(r, key, t1, t2);
        split(t2, 1, t2, t3);
        r = merge(t1, t3);
        delete (t2);
        return r;
    }

    void insert( int ind ) {
        node * l, * r, * z;
        int i;

        split(root, ind, l, r);
        z = searchNull(r, i);
        if (z != null && z->data == 0)
            r = remove(r, i);

        root = merge(merge(l, new node(++num, false)), r);
    }


    node * searchNull( node * cur, int & ind ) {
//        node * cur = t;
        ind = getSize(cur->left);

        while (getZero(cur)) {
            if (getZero(cur->left)) {
                cur = cur->left;
                ind = ind - getSize(cur->right) - 1;
            } else if (getData(cur) == 0) {
                break;
            } else {
                cur = cur->right;
                ind += getSize(cur->left) + 1;
            }
        }
        return cur;
    }

};

int main() {
    int n, j, m;
    cin >> n >> m;

    Treap tree(m);

    for (int i = 0; i < n; ++i) {
        cin >> j;
        tree.insert(j - 1);
    }

    vector<int> ans;
    tree.toArray(tree.root, ans);
    while (!ans.empty() && ans.back() == 0)
        ans.pop_back();

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";

    return 0;
}