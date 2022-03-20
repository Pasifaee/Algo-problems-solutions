#include <iostream>
#include <string>
#include <stdlib.h>

typedef struct item * pitem;
struct item {
    int letter = -1; // A -> 0, C -> 1, G -> 2, T -> 3
    int cnt = 1; // no. of vertices in this subtree
    unsigned int max[4] = {0, 0, 0, 0};
    // info about most left and most right fragments of letters
    std::pair<int, int> left; // first = letter, second = how many
    std::pair<int, int> right;
    bool rev = false;
    pitem l = nullptr, r = nullptr;
};

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

std::pair<int, int> left(pitem it) {
    std::pair<int, int> h = std::make_pair(-1, 0);
    return it ? it->left : h;
}

std::pair<int, int> right(pitem it) {
    std::pair<int, int> h = std::make_pair(-1, 0);
    return it ? it->right : h;
}

// Updates left and right attributes of [it] based on its children
void upd_left_and_right(pitem it) {
    if (!it) return;
    std::pair<int, int> ll, lr, rl, rr;
    if (it->l) {
        ll = it->l->rev ? right(it->l) : left(it->l);
        lr = it->l->rev ? left(it->l) : right(it->l);
    }
    if (it->r) {
        rl = it->r->rev ? right(it->r) : left(it->r);
        rr = it->r->rev ? left(it->r) : right(it->r);
    }
    // update left
    if (it->l) {
        it->left = ll;
        if (ll.second == cnt(it->l)) {
            if (it->letter == (it->l)->letter) {
                it->left.second++;
                if (rl.first == it->letter) {
                    it->left.second += rl.second;
                }
            }
        }
    }
    else {
        it->left = std::make_pair(it->letter, 1);
        if (it->r && rl.first == it->letter)
            it->left.second += rl.second;
    }
    // update right (symmetrically)
    if (it->r) {
        it->right = rr;
        if (rr.second == cnt(it->r)) {
            if (it->letter == (it->r)->letter) {
                it->right.second++;
                if (lr.first == it->letter) {
                    it->right.second += lr.second;
                }
            }
        }
    }
    else {
        it->right = std::make_pair(it->letter, 1);
        if (it->l && lr.first == it->letter)
            it->right.second += lr.second;
    }
}

unsigned int* max(pitem it) {
    static unsigned int res[4] = {0};
    return it ? it->max : res;
}

void upd_max(pitem it) {
    if (it) {
        for (int i = 0; i < 4; i++)
            it->max[i] = std::max(max(it->l)[i], max(it->r)[i]);

        std::pair<int, int> lr, rl;
        if (it->l) lr = it->l->rev ? left(it->l) : right(it->l);
        else lr = std::make_pair(-1, 0);
        if (it->r) rl = it->r->rev ? right(it->r) : left(it->r);
        else rl = std::make_pair(-1, 0);
        unsigned int max_tmp = 1 + (lr.first == it->letter ? lr.second : 0)
                                + (rl.first == it->letter ? rl.second : 0);
        it->max[it->letter] = std::max(it->max[it->letter], max_tmp);
    }
}

void upd_all(pitem it) {
    upd_cnt(it);
    upd_left_and_right(it);
    upd_max(it);
}

void push(pitem it) {
    if (it && it->rev) {
        it->rev = false;
        std::swap (it->l, it->r);
        //std::swap(it->left, it->right);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

pitem init(int letter) {
    pitem t = new item();
    t->letter = letter;
    t->left = std::make_pair(letter, 1);
    t->right = t->left;
    return t;
}

pitem build (int * code, int n) {
    // Construct BST on values {code[0], code[1], ..., code[n - 1]}
    if (n == 0) return nullptr;
    int mid = n / 2;
    pitem t = init(code[mid]);//new item (code[mid], rand ());
    t->l = build (code, mid);
    t->r = build (code + mid + 1, n - mid - 1);
    upd_all(t);
    return t;
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r)
        t = l ? l : r;
    else if (cnt(l) > cnt(r))
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_all(t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = nullptr );
    push (t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_all(t);
}

void reverse (pitem & t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

/*void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (t->key <= it->key ? t->r : t->l, it);
}*/

void move(pitem & t, int l, int r, int p) {
    pitem t1, t2, t3, t4;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    if (p < l) {
        t4 = t3;
        t3 = t2;
        split(t1, t1, t2, p);
    }
    else {
        split(t3, t3, t4, p-(l-1)-1);
    }
    merge(t, t1, t3);
    merge(t, t, t2);
    merge(t, t, t4);
}

void output (pitem t) {
    if (!t)  return;
    //push (t);
    output (t->l);
    std::cout << t->letter << " : cnt = " << t->cnt << ", left = <" << t->left.first << ", " << t->left.second << ">";
    std::cout << ", right = <" << t->right.first << ", " << t->right.second << ">";
    std::cout << "        max = {" << t->max[0] << ", " << t->max[1] << ", " << t->max[2] << ", " << t->max[3] << "}";
    if (t->rev) std::cout << " REV";
    std::cout << "\n";
    output (t->r);
}

int main() {
    int n, q;
    std::cin >> n >> q;
    int code[n];
    for (int i = 0; i < n; i++) {
        char letter;
        std::cin >> letter;
        if (letter == 'A')
            code[i] = 0;
        else if (letter == 'C')
            code[i] = 1;
        else if (letter == 'G')
            code[i] = 2;
        else
            code[i] = 3;
    }

    pitem code_BST = build(code, n);
    //output(code_BST);
    for (int i = 0; i < q; i++) {
        char query;
        int l, r, p;
        std::cin >> query >> l >> r;
        if (query == 'O') {
            reverse(code_BST, l - 1, r - 1);
        }
        else if (query == 'P') {
            std::cin >> p;
            move(code_BST, l - 1, r - 1, p - 1);
        }
        else if (query == 'N') {
            pitem t1, t2, t3;
            split (code_BST, t1, t2, l - 1);
            split (t2, t2, t3, r-l+1);
            push(t2);
            unsigned int res = 0;
            for (auto max_val : t2->max) {
                res = std::max(res, max_val);
            }

            merge (code_BST, t1, t2);
            merge (code_BST, code_BST, t3);

            std::cout << res << "\n";
        }
        //output(code_BST);
    }

    return 0;
}
