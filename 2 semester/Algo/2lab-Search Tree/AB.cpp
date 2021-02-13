/***
 * Author: Kozhukharov Nikita
 * Декартово дерево, здесь работает как АВЛ
 * Зашло сразу на задачи A, B
 ***/
#include <iostream>

using namespace std;
#define null nullptr

struct node {
    int x, y, size;
    node  * left, * right;
    explicit node(int a, int b) : x(a), y(b), left(null), right(null), size(1) {}
    void update() {
        this->size = this->left->size + this->right->size + 1;
    }
};

class Treap {
public:
    node * root;
    Treap() : root(null) {}

    /* user-friendly functions */

    node * find(int key) { return find_rec(this->root, key); }
    static pair<node *, node *> split(node * t, int k);
    static pair<node *, node *> split_i(node * t, int k); /* i - implicit, not used here */
    node * next( int key ) { return next_rec(this->root, key); }
    node * prev( int key ) { return prev_rec(this->root, key); }
    void remove(int k) { this->root = remove_rec(this->root, k); }
    node * insert(node * n) {
        node * res = find(n->x);
        if (res != null) {
            delete n;
            return res;
        }
        return this->root = insert_rec(this->root, n);
    }
    /* recursive functions */
private:
    node * next_rec( node * p, int key );
    node * prev_rec( node * p, int key );
    node * find_rec( node * p, int key );
    node * insert_rec(node * a, node * n);
    node * remove_rec(node *, int);
    static node * merge(node * t1, node * t2);
};


int main() {
    Treap t;
    string req, num;
    cout << std::boolalpha;

    while (cin >> req) {
        cin >> num;
        int n = stoi(num);
        node * p = null;
        switch (req[0]) {
            case 'i':
                t.insert(new node(n, rand() % INT_MAX - INT_MAX / 2));
                break;
            case 'e':
                p = t.find(n);
                cout << (p == null ? "false\n" : "true\n");
                break;
            case 'd':
                t.remove(n);
                break;
            case 'n': //next
                if ((p = t.next(n)) == null)
                    cout << "none\n";
                else
                    cout << p->x << "\n";
                break;
            case 'p': //prev
                if ((p = t.prev(n)) == null)
                    cout << "none\n";
                else
                    cout << p->x << "\n";
                break;
            default:
                break;
        }
    }
    
}

node * Treap::find_rec( node * p, int key ) {
    if (p != nullptr) {
        if (key < p->x)
            return find_rec(p->left, key);
        else if (key > p->x)
            return find_rec(p->right, key);
    }
    return p; /* p == null or p->x == key */
}

node * Treap::remove_rec(node * p, int k) {
    if (p != null) {
        if (p->x == k) {
            node * new_tree = merge(p->left, p->right);
            delete p;
            return new_tree;
        }
        if (p->x < k) {
            p->right = remove_rec(p->right, k);
            return p;
        }
        p->left = remove_rec(p->left, k);
    }
    return p;
}

node * Treap::insert_rec(node * a, node * n) {
    if (a == null)
        return n;
    if (n->y > a->y) { /* приоритет нового элемента больше корня, посплитим по его значению */
        pair<node *, node *> p = split(a, n->x); /* дерево и присоединим к нему */
        n->left = p.first;
        n->right = p.second;
        return n;
    } else /* корень останется такой же */
        if (n->x < a->x) /* тогда пихаем влево */
            a->left = insert_rec(a->left, n);
        else
            a->right = insert_rec(a->right, n);

    return a;
}

node * Treap::merge(node * t1, node * t2) {
    if (t2 == null)
        return t1;
    if (t1 == null)
        return t2;

    else if (t1->y > t2->y) { /// >=
        t1->right = merge(t1->right, t2);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        return t2;
    }
}

pair<node *, node *> Treap::split(node * t, int k) {
    pair<node *, node *> tmp;
    if (t == null)
        return make_pair(null, null);
    else if (k > t->x) {
        tmp = split(t->right, k);
        t->right = tmp.first;
        return make_pair(t, tmp.second);
    } else {
        tmp = split(t->left, k);
        t->left = tmp.second;
        return make_pair(tmp.first, t);
    }
}

pair<node *, node *> Treap::split_i(node *t, int k) {
    pair<node *, node *> tmp;
    if (t == null)
        return make_pair(null, null);
    int l = t->left->size;
    if (l >= k) {
        tmp = split(t->left, k);
        t->left = tmp.second;
        t->update();
        return make_pair(tmp.first, t);
    } else {
        tmp = split(t->right, k - l - 1);
        t->right = tmp.first;
        t->update();
        return make_pair(t, tmp.second);
    }
}

node * Treap::prev_rec( node * p, int key ) {
    if (p == nullptr)
        return nullptr;
    if (p->x >= key)
        return prev_rec(p->left, key);
    node *ans = prev_rec(p-> right, key);
    if (ans == null || ans->x < p->x)
        return p;
    else
        return ans;
/*    if (p == null)
        return null;
    node *pred = null;
    while (p != null) {
        if (p->x < key) {
            pred = p;
            p = p->right;
        } else
            p = p->left;
    }
    return pred;*/
}

node * Treap::next_rec( node * p, int key ) {
    if (p == nullptr)
        return nullptr;
    if (p->x <= key)
        return next_rec(p->right, key);
    node *ans = next_rec(p->left, key);
    if (ans == nullptr || ans->x > p->x)
        return p;
    else
        return ans;
 /*   if (p == null)
        return null;
    node * suc = null;
    while (p != null) {
        if (p->x > key) {
            suc = p;
            p = p->left;
        } else
            p = p->right;
    }
    return suc;*/
}