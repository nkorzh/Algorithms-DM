/***
 * Author: Kozhukharov Nikita
 * Обычное декартово дерево.
 * В изначально пустое множество можно пихать числа и запрашивать сумму на участвке.
 * Вытаскиваю дерево ({x | l <= x <= r}) двумя сплитами, за счет обновлений суммы в операциях
 * мерж и сплит в корне полученного дерева оказыватеся результат (сумма на участке).
 ***/
#include <iostream>
#include <climits>
// определяет константы с ограничениями целочисленного типа данных для конкретной системы и компилятора
#include <vector>

using namespace std;

#define null nullptr
#define bigNum 1000000000

struct node {
    long long prior;
    long long data;
    long long sum;

    node *left, *right;

    node( long long data = 0 ) : data(data), sum(data)
    {
        prior = rand() * rand();
        left = right = null;
    }
};

struct Treap {
    node * root;

    Treap( long long k = -1 ) : root(null) { if (k != -1) buildEmptyTree(k); }

    node * find( long long value ) {
        node * cur = root;
        while (cur != null) {
            if (cur->data < value)
                cur = cur->right;
            else if (cur->data > value)
                cur = cur->left;
            else
                break;
        }
        return cur;
    }

    long long getSum( node * p ) {
        if (p == null)
            return 0;
        return p->sum;
    }

    node * update( node * p ) {
        if (p == null)
            return null;
        p->sum = getSum(p->left) + getSum(p->right) + p->data;
        return p;
    }

    node * merge( node * l, node * r ) {
        if (l == null) return update(r);
        if (r == null) return update(l);

        if (l->prior > r->prior) {
            l->right = merge(l->right, r);
            return update(l);
        } else {
            r->left = merge(l, r->left);
            return update(r);
        }
    }

    void split(node * t, long long value, node * &l, node * &r) {
        if (t == null) {
            l = r = null;
            return;
        }
        if (t->data < value) {
            split(t->right, value, t->right, r);
            l = t;
        } else {
            split(t->left, value, l, t->left);
            r = t;
        }
        update(t);
    }

    long long getData( node * t ) {
        if (t == null) return 0;
        return t->data;
    }

    void toArray( node * node, vector<long long> & a ) {
        if (node != null) {
            toArray(node->left, a);
            a.push_back(getData(node));
            toArray(node->right, a);
        }
    }

    void buildEmptyTree( long long n ) {
        for (long long i = 0; i < n; ++i)
            root = merge(new node, root);
    }

    node * remove( node * r, long long key ) {
        node* t1, * t2, * t3;
        split(r, key, t1, t2);
        split(t2, 1, t2, t3);
        r = merge(t1, t3);
        delete t2;
        return r;
    }

    void insert( node * new_node ) {
        node * l, * r;

        if (find(new_node->data) != null) {
            delete new_node;
            return;
        }
        split(root, new_node->data, l, r);

        root = merge(merge(l, new_node), r);
    }

    long long sum( long long i, long long j ) {
        node *t1, *t2, *t3;

        split(root, i, t1, t2);
        split(t2, j + 1, t2, t3);

        long long res = getSum(t2);

        root = merge(merge(t1, t2), t3);
        return res;
    }
};

int main() {
    long long r, m;
    cin >> m;
    char request;
    long long lastRes = -1, n;

    Treap tree;

    for (long long i = 0; i < m; ++i) {
        cin >> request;
        cin >> n;
        switch (request) {
            case '+':
                if (lastRes != -1)
                    n = (n + lastRes) % bigNum;
                tree.insert(new node(n));
                lastRes = -1;
                break;
            case '?':
                cin >> r;
                cout << (lastRes = tree.sum(n, r)) << "\n";
                break;
            default:
                cerr << "Unknown request\n";
        }
    }
    return 0;
}