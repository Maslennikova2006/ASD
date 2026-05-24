// Copyright 2026 Mary Maslennikova

#ifndef LIB_RBTREE_RBTREE_H_
#define LIB_RBTREE_RBTREE_H_

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"
#include "../lib_bstree/bstree.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>

enum Color {red, black, blackBlack};

template <class TKey, class TValue>
struct RBNode {
    Pair<TKey, TValue> data;
    RBNode<TKey, TValue>* left;
    RBNode<TKey, TValue>* right;
    RBNode<TKey, TValue>* parent;
    Color color;

    RBNode();
    RBNode(const TKey& key, const TValue& val, RBNode<TKey, TValue>* l = nullptr, RBNode<TKey, TValue>* r = nullptr,
        RBNode<TKey, TValue>* p = nullptr, Color c = red);
};

template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode() : data(), left(nullptr), right(nullptr), parent(nullptr), color(red) {}
template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode(const TKey& key, const TValue& val, RBNode<TKey, TValue>* l, RBNode<TKey, TValue>* r,
    RBNode<TKey, TValue>* p, Color c) :
    data(key, val), left(l), right(r), parent(p), color(c) {}

template <class TKey, class TValue>
class RBTree : public BSTree<TKey, TValue, RBNode<TKey, TValue>> {

public:
    RBTree();

    void insert(const TKey& key, const TValue& val);  // +
    void erase(const TKey& key);

private:
    void recolor(RBNode<TKey, TValue>* node);
    void swap_colors(RBNode<TKey, TValue>* first, RBNode<TKey, TValue>* second);

    void left_rotate(RBNode<TKey, TValue>* node);
    void right_rotate(RBNode<TKey, TValue>* node);

    void RR(RBNode<TKey, TValue>* node);
    void LL(RBNode<TKey, TValue>* node);
    void RL(RBNode<TKey, TValue>* node);
    void LR(RBNode<TKey, TValue>* node);

    void recover_balance(RBNode<TKey, TValue>* node);
    void erase_blackBlack() noexcept;
};

template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree() : BSTree<TKey, TValue, RBNode<TKey, TValue>>() {}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    RBNode<TKey, TValue>* parent = BSTree::insert(key, val);
    if (!parent) {
        recolor(_root);
        return;
    }
    RBNode<TKey, TValue>* node = nullptr;
    if (parent->right && parent->right->data.first == key)
        node = parent->right;
    else if (parent->left && parent->left->data.first == key)
        node = parent->left;
    if (!node) return;
    node->parent = parent;

    if (parent->color == red)
        recover_balance(node);
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::erase(const TKey& key) {
    RBNode<TKey, TValue>* parent_d = BSTree::find_parent(key);
    if (!parent_d) return;

    RBNode<TKey, TValue>* d = nullptr;
    if (parent_d == _root && _root->data.first == key)
        d = _root;
    else if (parent_d->right && parent_d->right->data.first == key)
        d = parent_d->right;
    else if (parent_d->left && parent_d->left->data.first == key)
        d = parent_d->left;
    if (!d) return;

    Color deleted_color = d->color;
    bool dHasTwoChildren = (d->left && d->right);
    bool dIsLeftChildren = (parent_d->left == d);

    RBNode<TKey, TValue>* r = nullptr;
    if (!d->left && !d->right)
        r = nullptr;
    else if (!d->left)
        r = d->right;
    else if (!d->right)
        r = d->left;
    else {
        r = BSTree::find_max_left(d);
        deleted_color = r->color;
    }

    RBNode<TKey, TValue>* parent_r = BSTree::erase(key);
    if (!parent_r && !_root) return;
    if (!parent_r && _root) {
        _root->color = black;
        return;
    }

    RBNode<TKey, TValue>* p = nullptr;
    bool isVirtual = false;

    if (dHasTwoChildren) {
        if (deleted_color == black) {
            p = new RBNode<TKey, TValue>();
            p->color = blackBlack;
            p->parent = parent_r;
            isVirtual = true;

            if (parent_r->left == nullptr)
                parent_r->left = p;
            else
                parent_r->right = p;
        }
        else {
            if (_root) _root->color = black;
            return;
        }
    }
    else if (r) {
        p = r;
    }
    else {
        p = new RBNode<TKey, TValue>();
        p->color = blackBlack;
        p->parent = parent_r;
        isVirtual = true;

        if (dIsLeftChildren)
            parent_r->left = p;
        else
            parent_r->right = p;
    }
    if (!p) return;

    if (deleted_color == black && p->color == red) {
        if (isVirtual) {
            RBNode<TKey, TValue>* parent = p->parent;
            if (parent) {
                if (parent->left == p) parent->left = nullptr;
                else parent->right = nullptr;
            }
            delete p;
        }
        else {
            recolor(p);
        }
        if (_root) _root->color = black;
        return;
    }

    if (deleted_color == red) {
        if (isVirtual) {
            RBNode<TKey, TValue>* parent = p->parent;
            if (parent) {
                if (parent->left == p) parent->left = nullptr;
                else parent->right = nullptr;
            }
            delete p;
        }
        if (_root) _root->color = black;
        return;
    }

    p->color = blackBlack;

    while (p->color == blackBlack) {
        auto P = p->parent;
        if (!P) {
            p->color = black;
            break;
        }

        bool pIsLeftChildren = (P->left == p);
        RBNode<TKey, TValue>* S = pIsLeftChildren ? P->right : P->left;
        RBNode<TKey, TValue>* CS = nullptr;

        if (S && S->color == red) {
            recolor(P);
            recolor(S);
            if (pIsLeftChildren)
                RR(P);
            else
                LL(P);
            continue;
        }

        if (!S || S->color == black) {
            CS = (S && pIsLeftChildren) ? S->right : (S ? S->left : nullptr);
            if (CS && CS->color == red) {
                if (pIsLeftChildren)
                    RR(P);
                else
                    LL(P);
                swap_colors(P, S);
                recolor(CS);
                p->color = black;
                break;
            }

            CS = (S && pIsLeftChildren) ? S->left : (S ? S->right : nullptr);
            if (CS && CS->color == red) {
                if (pIsLeftChildren)
                    LL(S);
                else
                    RR(S);
                swap_colors(S, CS);
                continue;
            }

            if (S)
                recolor(S);
            if (P->color == red) {
                recolor(P);
                p->color = black;
                p = _root;
            }
            else {
                if (S)
                    P->color = blackBlack;
                p = P;
            }
            continue;
        }
    }

    if (isVirtual && p) {
        RBNode<TKey, TValue>* parent = p->parent;
        if (parent) {
            if (parent->left == p)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        }
        delete p;
    }

    if (_root)
        _root->color = black;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::recolor(RBNode<TKey, TValue>* node) {
    node->color = (node->color == red) ? black : red;
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::swap_colors(RBNode<TKey, TValue>* first, RBNode<TKey, TValue>* second) {
    Color first_color = first->color;
    first->color = second->color;
    second->color = first_color;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::left_rotate(RBNode<TKey, TValue>* node) {
    /*   G                               P
    *     \                             / \
    *      P     left_rotate(G) ->     G   C
    *     / \                           \
    *    T   C                           T
    */

    auto G = node;
    auto P = G->right;
    auto T = P->left;

    if (G->parent) {
        if (G == G->parent->left)
            G->parent->left = P;
        else
            G->parent->right = P;
    }

    G->right = T;
    if (T)
        T->parent = G;
    P->parent = G->parent;
    P->left = G;
    G->parent = P;

    if (!P->parent)
        _root = P;
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::right_rotate(RBNode<TKey, TValue>* node) {
    /*       G                             P
    *       /                             / \
    *      P     right_rotate(G) ->      C   G
    *     / \                               /
    *    C   T                             T
    */
    auto G = node;
    auto P = G->left;
    auto T = P->right;

    if (G->parent) {
        if (G == G->parent->left)
            G->parent->left = P;
        else
            G->parent->right = P;
    }

    G->left = T;
    if (T)
        T->parent = G;
    P->parent = G->parent;
    P->right = G;
    G->parent = P;

    if (!P->parent)
        _root = P;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::RR(RBNode<TKey, TValue>* node) {
    /*   G
    *     \
    *      P     left_rotate(G) ->       P
    *       \                           / \
    *        C                         G   C
    */
    auto G = node;
    left_rotate(G);
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::LL(RBNode<TKey, TValue>* node) {
    /*       G
    *       /
    *      P     right_rotate(G) ->       P
    *     /                              / \
    *    C                              C   G
    */
    auto G = node;
    right_rotate(G);
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::RL(RBNode<TKey, TValue>* node) {
    /*   G                         G
    *     \                         \
    *      P   right_rotate(P) ->    C   left_rotate(G)      C
    *     /                           \                     / \
    *    C                             P                   G   P
    */
    auto G = node;
    auto P = G->right;
    right_rotate(P);
    left_rotate(G);
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::LR(RBNode<TKey, TValue>* node) {
    /*       G                           G
    *       /                           /
    *      P     left_rotate(P) ->     C   right_rotate(G)   C
    *       \                         /                     / \
    *        C                       P                     P   G
    */
    auto G = node;
    auto P = G->left;
    left_rotate(P);
    right_rotate(G);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::recover_balance(RBNode<TKey, TValue>* node) {
    if (!node) return;
    auto C = node;
    auto P = C->parent;
    if (!P) return;
    auto G = P->parent;
    if (!G) return;
    auto U = (G->right == P) ? G->left : G->right;

    while (P->color == red && U && U->color == red) {
        recolor(U);
        recolor(P);
        if (_root == G)
            break;
        recolor(G);
        C = G;
        P = C->parent;
        if (!P) break;
        G = P->parent;
        if (!G) break;
        U = (G->right == P) ? G->left : G->right;
    }
    if (!P || P->color == black) return;

    if (G->right == P && P->right == C) {
        RR(G);
        swap_colors(G, P);
    }
    else if (G->right == P && P->left == C) {
        RL(G);
        swap_colors(G, C);
    }
    else if (G->left == P && P->left == C) {
        LL(G);
        swap_colors(G, P);
    }
    else if (G->left == P && P->right == C) {
        LR(G);
        swap_colors(G, C);
    }
}
#endif  // LIB_RBTREE_RBTREE_H_