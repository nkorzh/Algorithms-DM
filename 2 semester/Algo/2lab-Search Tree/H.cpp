/***
 * Author: Kozhukharov Nikita
 * Декартово дерево по неявному ключу.
 * Инверсия участка массива от l до r включительно
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
    bool reversed;

    node *left, *right;

    node( int data = -1, bool isZero = true ) : data(data), isFree(data == -1 ? true : false),
        size(1), reversed(false)
    {
        prior = rand() * rand();
        left = right = null;
    }
};

struct Treap {
    node * root;
    int num = 0;

    Treap( int k = -1 ) : root(null) { if (k != -1) buildEmptyTree(k); }

    node * update( node * p ) {
        if (p == null)
            return null;
        return updateSize(updateZero(p));
    }

    node * pushOperation( node * p ) {
        if (p == null)
            return null;
        if (p->reversed) {
            swap(p->left, p->right);
            if (p->left != null) p->left->reversed ^= true;
            if (p->right != null) p->right->reversed ^= true;
            p->reversed = false;
        }
        return p;
    }

    node * merge( node * l, node * r ) {
        if (l == null) return r;
        if (r == null) return l;

        pushOperation(l);
        pushOperation(r);

        if (l->prior > r->prior) {
            l->right = merge(l->right, r);
            return update(l);
        } else {
            r->left = merge(l, r->left);
            return update(r);
        }
    }

    void split(node * t, int key, node * &l, node * &r) {
        if (t == null) {
            l = r = null;
            return;
        }
        pushOperation(t);
        if (getSize(t->left) < key) {
            split(t->right, key - getSize(t->left) - 1, t->right, r);
            l = t;
        } else {
            split(t->left, key, l, t->left);
            r = t;
        }
        update(t);
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
            t->isFree = getZero(t->left) || getZero(t->right) || (t->data == -1);
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
            pushOperation(node);
            toArray(node->left, a);
            a.push_back(getData(node));
            toArray(node->right, a);
        }
    }

    void buildEmptyTree( int n ) {
        for (int i = 0; i < n; ++i)
            root = merge(new node, root);
    }

    node * remove( node * r, int key ) {
        node* t1, * t2, * t3;
        split(r, key, t1, t2);
        split(t2, 1, t2, t3);
        r = merge(t1, t3);
        delete t2;
        return r;
    }

    void insert( node * new_node, int ind ) {
        node * l, * r, * z;
        int i;

        split(root, ind, l, r);
        z = searchNull(r, i);
        if (z != null && z->data == -1)
            r = remove(r, i);

        root = merge(merge(l, new_node), r);
    }


    node * searchNull( node * cur, int & ind ) {
        ind = getSize(cur == null ? null : cur->left);

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

    void moveToBeg( int i, int j ) {
        node *l, *part, *r;

        split(root, i, l, part);
        split(part, j - i, part, r);

        root = merge(merge(part, l), r);
    }

    void reverse( int i, int j ) {
        node *l, *part, *r;

        split(root, i, l, part);
        split(part, j - i, part, r);

        part->reversed ^= true; /* inversion */

        root = merge(merge(l, part), r);
    }

};

int main() {
    int n, l, r, m;
    cin >> n >> m;

    Treap tree;

    for (int i = 0; i < n; ++i)
        tree.insert(new node(i + 1), i);

    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        tree.reverse(l - 1, r);
    }

    vector<int> ans;
    tree.toArray(tree.root, ans);
//    while (!ans.empty() && ans.back() == 0)
//        ans.pop_back();

    for (int an : ans)
        cout << an << " ";

    return 0;
}