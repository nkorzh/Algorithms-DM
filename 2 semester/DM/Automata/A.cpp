/***
 * Это попытка написать алгоритм Томпсона, которая закончилась Runtime Error на 5 тесте.
 * В этом файле потрачено около 9 часов жизни КТшника (возможно, я тупой, но я с этим борюсь).
 ***/
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <sstream>

#define null nullptr

using namespace std;

typedef multimap<char, int> tmap;
typedef pair<tmap::iterator, tmap::iterator> tmap_range;

class automat {
    struct node {
    protected:
        tmap transition;
    public:
        int id;
        bool is_final;
        node () : id(-1), is_final(false) {}
        node ( int id ) : id(id), is_final(false) {}
        bool add_trans( int final_id, char c ) {
            return transition.emplace(c, final_id)->second;
        }
        tmap_range go( char c ) {
            return transition.equal_range(c);
        }
    };

    vector<node *> state;
    string word_to_check;
    set<char> alphabet;

    node * walk( node * cur, char c ) {
        static char last_symbol;
        if (!cur) {
//            cerr << "Empty node after '" << last_symbol << "' symbol.\n";
            return cur;
        }
//        last_symbol = c;
        tmap_range range = cur->go(c);
        return range.first == range.second ?
            null :
         state[range.first->second]; // get begin iterator from pair beg/end (range), get id of node
    }
    bool set_transit( int id, int fin_id, char symbol ) {
        if (id < 0 || id >= state.size())
            return false;
        if (!state[id]) {
            state[id] = new node(id);
        }
        return state[id]->add_trans(fin_id, symbol);
    }
    bool check_final( node * n ) {

        if (!n) {
            cerr << "Got empty node.\n";
            return false;
        }
        return n->is_final;
    }
    /***
     * Та самая попытка написать Томпсона
     * @return
     */
    bool determinize() {
        using nodes = set<node *>;

        struct new_state : public node {
            nodes nset;
            new_state(node * n, int id) { nset.emplace(n); this->id = id; }
            new_state(int id) { this->id = id; }
            void insert(node * element) { nset.insert(element); }
            // unnecessary?
            bool operator<(const new_state & s) const {
                return nset < s.nset;
            }
        };

        auto cmp = [] (const new_state * a, const new_state * b) { return a->nset < b->nset; };
        using saved_set = set<new_state *, typeof(cmp)>;
        saved_set saved_nodes(cmp);


        auto set_contains = [] ( const saved_set & s, new_state * nn ) -> bool {
            pair<saved_set::iterator , saved_set::iterator > range = s.equal_range(nn);
            return range.first != range.second;
        };
        auto get_all_by_symbol = [this]( new_state & src_node, char symbol, new_state & final_set ) {
            for (node * nnode : src_node.nset) {
                tmap_range range = nnode->go(symbol);
                for (auto it = range.first; it != range.second; it++) {
                    final_set.insert(state[it->second]);
                    final_set.is_final |= state[it->second]->is_final;
                }
            }
        };
        auto make_transition = [&saved_nodes] (new_state * pd, new_state * qd, char symbol) {
            new_state * st = *(saved_nodes.find(qd));
            pd->add_trans(st->id, symbol);
        };

        vector<new_state *> new_states;
        int next_node_id = 0;

        queue<new_state *> P;

        nodes start_node_set;
        new_states.emplace_back(new new_state(state.front(), next_node_id++));

        // init queue of node sets
        P.push(new_states.front());
        saved_nodes.emplace(new_states.front());

        while (!P.empty()) {
            // достаем множество
            new_state * pd = P.front(); P.pop();
            for (auto symbol : alphabet) {
                new_state *new_node = new new_state(next_node_id);
                // get set of all nodes, available from pd by symbol
                get_all_by_symbol(*pd, symbol, *new_node);
                // set transition to the new_node from pd
                if (new_node->nset.empty()) {
                    delete new_node;
                    continue;
                }
                // add new_node to array of states
                
                if (!set_contains(saved_nodes, new_node)) {
                    pd->add_trans(next_node_id++, symbol);   // add transition
                    saved_nodes.emplace(new_node); //pd?
                    new_states.emplace_back(new_node);
                    P.push(new_node);
                } else {
                    make_transition(pd, new_node, symbol); // add transition
                }
            }
        }

        for_each(state.begin(), state.end(), [] (auto & s) { delete s; });
        state.reserve(new_states.size());
        for (int i = 0; i < new_states.size(); ++i) {
            state[i] = new_states[i];
        }
        // convert to normal
        return true;
    }
public:
    bool dump_check() {
        unordered_set<int> cur_states;
        cur_states.emplace(0);
        
        for (auto symbol : word_to_check) { // бегу по строке
            unordered_set<int> next_states;
            for (auto j : cur_states) {             // для каждого возможного на текущий момент состояния бегу по всем переходам
                tmap_range range_of_possible_trans = state[j]->go(symbol);
                for_each (range_of_possible_trans.first, range_of_possible_trans.second, [&next_states] (pair<char, int> trans) {
                    next_states.emplace(trans.second); // пихаю в множество новых возможных состояний каждый индекс из возможных состояний
                });
            }
            cur_states = next_states;
        }
        for (auto i : cur_states) { // если хоть одно состояние по итогу допускающее - мы выиграли
            if (state[i]->is_final) // но я всё равно проиграл, потому что мой Томпсон, блин, не работает
                return true;        // если кто-то это читает, глянь код в determinize, пожалуйста
        }                           // если увидишь очевидный ляп - напиши на почту, пожалуйста
        return false;
    }

    bool check_word() {
        node * cur_node = state[0];
        for (char c : word_to_check) {
            cur_node = walk(cur_node, c);
        }
        return check_final(cur_node);
    }
    /// все состояния я нумерую с 0
    void init( istream & in ) { // can be bool to message if smth was incorrect
        for_each(state.begin(), state.end(), [] (auto & s) { s = null; });
        in >> word_to_check;
        int conditions, transitions, allowed_amount;
        in >> conditions >> transitions >> allowed_amount;

        state.resize(conditions);
        int state_num = 0;
        for_each(state.begin(), state.end(), [&state_num] (auto & s) { s = new node(state_num++); });
        vector<int> allowed_states;

        for (int i = 0; i < allowed_amount; ++i) {
            int num;
            in >> num;
            allowed_states.push_back(num - 1);
        }

        for (int allowed_state : allowed_states) {
            // can use unitialized ptr
            state[allowed_state]->is_final = true;
        }

        for (int i = 0; i < transitions; ++i) {
            int id, fin_id;
            char symbol;
            in >> id >> fin_id >> symbol;
            id--, fin_id--;
            alphabet.emplace(symbol);
            set_transit(id, fin_id, symbol);
        }

//        determinize();
    }

    ~automat() {
        // clean vector
        for_each(state.begin(), state.end(), [] (auto & s) { delete s; });
    }
};

//int main() {
//    ifstream in("problem2.in");
//    ofstream out("problem2.out");
//    automat dka;
//
//    stringstream input;
//    input << "abacaba 4 6 1 2 1 2 a 2 1 c 2 3 b 3 2 a 2 4 b 1 4 a ";
//    dka.init(in);
//
//    out << (dka.dump_check() ? "Accepts" : "Rejects") << endl;
//    return 0;
//}
