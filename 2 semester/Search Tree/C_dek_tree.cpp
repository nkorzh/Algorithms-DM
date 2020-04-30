/***
 * Author: Kozhukharov Nikita
 * Декартово дерево по неявному ключу, здесь реализован массив с операцией insert(i, x)
 * Если i занято, то делается insert(i + 1, a[i]), затем a[i] = x
 * Все элементы массива > 0 (по условию; используется в конструкторе node)
 ***/
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
#define null nullptr

struct node {
    int x, y, size;
    node  * left, * right;
    bool used;
    explicit node(int value = 0) : x(value), y(rand() % INT_MAX), left(null), right(null), size(1), used(value != 0) {}
};

class Treap {
public:
    node * root;
    int size;
    explicit Treap( int size = 0 ) : root(null) { if (size) initArray(size); }

    /* user-friendly functions */

    node * find(int key) { return find_rec(this->root, key); }
    pair<node *, node *> split( node * t, int k );
    pair<node *, node *> split_i( node * t, int k ); /* i - implicit, not used here */
    node * next( int key ) { return next_rec(this->root, key); }
    node * prev( int key ) { return prev_rec(this->root, key); }
    void remove( int k ) { this->root = remove_rec(this->root, k); }
    node * insert( node * n, int ind );
    node * At(int k) {
        if (this->root == null) return null;
        return getKmax_rec(this->root, k);
    }
    node * findmin(node * p);
    vector<int> toArray();

    /* recursive functions */
private:
    int getSize(node * p) {
        return p == null ? 0 : p->size;
    }
    node * getKmax_rec( node *, int );
    node * next_rec( node * p, int key );
    node * prev_rec( node * p, int key );
    node * find_rec( node * p, int key );
    node * insert_rec(node *, node *);
    node * remove_rec(node *, int);
    node * merge(node * t1, node * t2);
    node * updateSize(node *);
    node * updateUsing(node *);
    void initArray(int arraySize);
    node * next_ind(node * );
    void walk( node *cur, vector<int> &list, int &i );

    node *findFree( node *freePlace, int &i, int ind );
};


int main() {
    long seed = std::chrono::steady_clock::now().time_since_epoch().count();
//    cout << seed << endl;
    srand(seed);
//    srand(-1712227168);
//correct: 1175214092
//incorrect: -1712227168
/*
5 4
3 3 4 1 3
*/
    ios_base::sync_with_stdio(false);
    cout << std::boolalpha;

    string req, num;
    cin >> num >> req;
    int size = stoi(req), amount = stoi(num);
    Treap array(size);

    for (int i = 1; i <= amount; i++) {
        cin >> num;
        array.insert(new node(i), stoi(num) - 1);
    }
    vector<int> res = array.toArray();
    while (!res.empty() && res.back() == 0)
        res.pop_back();
    cout << res.size() << "\n";
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }
    return 0;
}

node *Treap::insert( node *n, int ind )  {
    node *l, *r, *freePlace;
    pair<node *, node *> tmp = split_i(root, ind);
    l = tmp.first;
    r = tmp.second;

    int i = getSize(r == null ? r : r->left);
    freePlace = findFree(r, i, ind/* - getSize(l)*/);

    if (freePlace != nullptr && freePlace->x == 0)
        r = remove_rec(r, i);

    return root = merge(merge(l , n), r);

/*  // old v
    if (res != null) {
        delete n;
        return res;
    }
    return this->root = insert_rec(this->root, n);
*/
}

node * Treap::findFree( node * freePlace, int &i, int ind ) {
    while (freePlace != null && !freePlace->used/* || i != ind*/) {
        if (freePlace->left != nullptr && /*i > ind*/ !freePlace->left->used) {
            freePlace = freePlace->left;
            i += -getSize(freePlace->right) - 1;
        } else if (freePlace->x == 0 /*&& i == ind*/) {
            break;
        } else {
//            if ((freePlace = freePlace->right) == null) {
//                i++;
//                return null;
//            }
            freePlace = freePlace->right;
            i += getSize(freePlace == null ? null : freePlace->left) + 1;
        }
    }
    return freePlace;
}

vector<int> Treap::toArray() {
    vector<int> res;
    node * cur = root;
    int i = 0;
    walk(root, res, i);

    return res;
}

void Treap::walk( node * cur, vector<int> & list, int & i ) {
//    if (i >= size)
//        return;
    if (cur != null) {
        if (cur->left != null)
            walk(cur->left, list, i);
        list.push_back(cur->x);
        i++;
        if (cur->used)
            size = i;
        walk(cur->right, list, i);
    }
}

node * Treap::getKmax_rec(node * cur, int k ) {
    if (cur == null) return null;
    int leftsize = getSize(cur->left);
    if (leftsize == k)
        return cur;
    else if (leftsize > k)
        return getKmax_rec(cur->left, k);
    else
        return getKmax_rec(cur->right, k - leftsize - 1);
}

/*node * Treap::find_rec( node * p, int key ) {
    if (p != nullptr) {
        if (key < p->x)
            return find_rec(p->left, key);
        else if (key > p->x)
            return find_rec(p->right, key);
    }
    return p; // p == null or p->x == key
}*/

node * Treap::remove_rec(node * p, int index) {
    /*if (p != null) {
        if (getSize(p->left) == index) {
            node * new_tree = merge(p->left, p->right);
            delete p;
            return updateUsing(updateSize(new_tree));
        }
        if (getSize(p->left) < index) {
            p->right = remove_rec(p->right, index - getSize(p->left) - 1);
            return updateUsing(updateSize(p));
        } else {
            p->left = remove_rec(p->left, index);
            return updateUsing(updateSize(p));
        }
    }
    return null;*/

    pair<node *, node *> left = split_i(p, index);
    pair<node *, node *> right = split_i(left.second, 1);
    return merge(left.first, right.second);
}

node * Treap::insert_rec(node * placeToIns, node * new_node) {
    if (placeToIns == null)
        return updateSize(new_node); /* update is unnecessary here */
    if (new_node->y > placeToIns->y) { /* значение нового элемента больше корня, посплитим по размеру */
        pair<node *, node *> p = split(placeToIns, new_node->x); /* дерево и присоединим к нему */
        new_node->left = p.first;
        new_node->right = p.second;
        return updateSize(new_node);
    } else /* приоритет корня выше, ищем место по значению */
        if (new_node->x < placeToIns->x) /* тогда пихаем влево */
            placeToIns->left = insert_rec(placeToIns->left, new_node);
        else
            placeToIns->right = insert_rec(placeToIns->right, new_node);
    return updateSize(placeToIns);
}

node * Treap::merge(node * t1, node * t2) {
    node * res;
    if (t2 == null) res = t1;
    else if (t1 == null) res = t2;
    else if (t1->y > t2->y) { /// >=
        t1->right = merge(t1->right, t2);
        res = t1;
    } else {
        t2->left = merge(t1, t2->left);
        res = t2;
    }
    return updateUsing(updateSize(res));
}


pair<node *, node *> Treap::split_i( node *t, int k ) {
    pair<node *, node *> tmp;
    if (t == null)
        return make_pair(null, null);
    int curIndex = getSize(t->left);
    if (curIndex >= k) {
        tmp = split_i(t->left, k);
        t->left = tmp.second;
        return make_pair(updateUsing(updateSize(tmp.first)), updateUsing(updateSize(t)));
    } else {
        tmp = split_i(t->right, k - curIndex - 1);
        t->right = tmp.first;
        return make_pair(updateUsing(updateSize(t)), updateUsing(updateSize(tmp.second)));
    }
}

/* рекурсивная версия немного быстрее цикла */
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

/* рекурсивная версия немного быстрее цикла */
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

node * Treap::updateSize( node * p ) {
    if (p == null)
        return null;
    p->size = (p->left == null ? 0 : p->left->size) +
           (p->right == null ? 0 : p->right->size) + 1;
    return p;
}

void Treap::initArray( int arraySize ) {
    size = arraySize;
    for (int i = 0; i < arraySize; ++i)
        root = merge(root, new node);
    size = 0;
}

node *Treap::updateUsing( node * p ) {
    if (p == null)
        return null;
    p->used = (p->left == null ? false : p->left->used) &&
            (p->right == null ? false : p->right->used) && (p->x != 0);
    return p;
}

/* делим дерево на два по ключу */
pair<node *, node *> Treap::split(node * t, int k) {
    pair<node *, node *> tmp;
    if (t == null)
        return make_pair(null, null);
    else if (k > t->x) {
        tmp = split(t->right, k);
        t->right = tmp.first;
        updateUsing(updateSize(t));
        return make_pair(t, tmp.second);
    } else {
        tmp = split(t->left, k);
        t->left = tmp.second;
        updateUsing(updateSize(t));
        return make_pair(tmp.first, t);
    }
}

node * Treap::findmin(node * p) {
    if (p == null)
        return null;
    while (p->left != null)
        p = p->left;
    return p;
}
