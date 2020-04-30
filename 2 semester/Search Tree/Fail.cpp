/***
 * Хреновые попытки написать АВЛ за час, забил и сделал Treap.
 * Разберусь с этим позже, когда буду решать задачи с e-olymp для кайфа.
 ***/
 #include <iostream>
//#include <string>
#include <cstring>
#include <ostream>

using namespace std;
//namespace {


    int compare(long a, long b) {
        return (a < b ? -1 : (a > b ? 1 : 0));
    }

    struct node
    {
        long key;
        int height;
        node *left;
        node *right;

        explicit node(long k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };


node * rotateright( node * p );
node * rotateleft( node * q );
node * find( node * p, long key );
node * balance( node * p );
node * insert( node * p, long k );
node * findmin( node * p );
node * findmax( node * p );
node * removemin( node * p );
node * remove( node * p, long k );
node * prev( node * p, long key );
node * next( node * p, long key );

int height( node * p ) {
        return p ? p->height : 0;
    }

    int bfactor( node * p ) {
        int r = height(p->right), l = height(p->left);
        return r - l;
    }

    void fixheight( node * p ) {
        int hl = height(p->left);
        int hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    node * rotateright( node * y ) {
        node * x = y->left;
        y->left = x->right;
        x->right = y;
/*
 *      taken from rotateleft
        if (y->left != T.nil) // T.nil - root parent
            y->left.p = x;
        y.p = x.p;
        if (x.p == T.nil)
            T.root = y;
        else if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
*/
//        x->p = y;
        fixheight(y);
        fixheight(x);
        return x;
    }

    node * rotateleft( node * x ) {
        node *y = x->right;
        x->right = y->left;
/*
        if (y->left != T.nil) // T.nil - root parent
            y->left.p = x;
        y.p = x.p;
        if (x.p == T.nil)
            T.root = y;
        else if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
*/
        y->left = x;

//        x->p = y;
        fixheight(x);
        fixheight(y);
        return y;
    }

    node * find( node * p, long key ) {
        if (p != nullptr) {
            if (compare(key, p->key) == -1)
                return find(p->left, key);
            else if (compare(key, p->key) == 1)
                return find(p->right, key);
        }
        return p;
    }

    node * balance( node * p ) {
        fixheight(p);
        if (bfactor(p) == 2) {
            if (bfactor(p->right) < 0)
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if (bfactor(p) == -2) {
            if (bfactor(p->left) > 0)
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p; // балансировка не нужна
    }

    node * insert( node * p, long k ) {
        if (!p) return p = new node(k);
        if (compare(k, p->key) == -1)
            p->left = insert(p->left, k);
        else if (compare(k, p->key) == 1)
            p->right = insert(p->right, k);
        return balance(p);
    }

    node * findmin( node * p ) {
        if (p == nullptr)
            return p;
        return p->left == nullptr ? p : findmin(p->left);
    }

    node * findmax( node * p ) {
        if (p == nullptr)
            return p;
        return p->right == nullptr ? p : findmax(p->right);
    }

    node * removemin( node * p ) {
        if (p->left == nullptr)
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }

    node * remove( node * p, long k ) {
        if (!p) return nullptr;
        if (k < p->key)
            p->left = remove(p->left, k);
        else if (k > p->key)
            p->right = remove(p->right, k);
        else //  k == p->key
        {
            node *q = p->left;
            node *r = p->right;
            delete p;
            if (!r) return q;
            node *min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }

        return balance(p);
    }

    node * prev( node * p, long key ) {
        if (p == nullptr)
            return nullptr;
        node *pred = nullptr;
        while (p != nullptr) {
            if (compare(p->key, key) == -1) {
                pred = p;
                p = p->right;
            } else
                p = p->left;
        }

        return pred;
    }
        

    node * next( node * p, long key ) {
        if (p == nullptr)
            return nullptr;
        node * suc = nullptr;
        while (p != nullptr) {
            if (compare(p->key, key) == 1) {
                suc = p;
                p = p->left;
            } else
                p = p->right;
        }
        return suc;
    }
//} // anonymous namespace //TODO: make a class later

int main() {
    ios_base::sync_with_stdio(false);

    node * root = nullptr;
    string request;

    while (cin >> request) {
        string keys;
        int key;
        cin >> keys;
        key = stoi(keys);
        node * t = nullptr;
        switch (request[0]) {
            case 'i': //insert
                root = insert(root, key);
                break;
            case 'e': //exists
            {
                t = find(root, key);
                cout << ((t != nullptr) ? "true" : "false") << "\n";
            }
                break;
            case 'n': //next
            {
                t = next(root, key);
                if (t == nullptr)
                    cout << "none";
                else
                    cout << (t->key);
                cout << "\n";
            }
                break;
            case 'p': //prev
            {
                t = prev(root, key);
                if (t == nullptr)
                    cout << "none";
                else
                    cout << (t->key);
                cout << "\n";
            }
                break;
            case 'd': //delete
                remove(root, key);
                break;
//            default:
//                break;
        }
        request.empty();
    }

    return 0;
}
