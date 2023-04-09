//
// Created by alexs on 2023-03-11.
//

#ifndef DSA_AVL_HPP
#define DSA_AVL_HPP

#include "./Bst.hpp"

template<class T>
struct NodeOverflow {
    Node<T> *X;
    Node<T> *Z;

    NodeOverflow(Node<T> *X, Node<T> *Z);
};

template<class T>
NodeOverflow<T>::NodeOverflow(Node<T> *X, Node<T> *Z): X(X), Z(Z) {}

template<class T>
class Avl : public Bst<T> {
private:
    // See https://en.wikipedia.org/wiki/AVL_tree#Rebalancing
    Node<T> *rotateLeft(Node<T> *X, Node<T> *Z);

    Node<T> *rotateRight(Node<T> *X, Node<T> *Z);

    Node<T> *rotateRightLeft(Node<T> *X, Node<T> *Z);

    Node<T> *rotateLeftRight(Node<T> *X, Node<T> *Z);

    NodeOverflow<T> findOverflowedNode(Node<T> *from);

    void updateBalanceFactors(Node<T> *from, bool hasRemoved);

    Node<T> *insertNode(T value);

    void applyRotations(Node<T> *X, Node<T> *Z);

public:
    explicit Avl() = default;

    explicit Avl(const std::vector<T> &values);

    Node<T> *insert(T value);

    void remove(T value);
};

template<class T>
Avl<T>::Avl(const std::vector<T> &values) {
    for (auto x: values) {
        insert(x);
    }
}

template<class T>
Node<T> *Avl<T>::insertNode(T value) {
    return Bst<T>::insert(value);
}

template<class T>
Node<T> *Avl<T>::insert(T value) {
    Node<T> *from = insertNode(value);

    updateBalanceFactors(from, false);
    NodeOverflow<T> nodeOverflow = findOverflowedNode(from);

    if (!nodeOverflow.X) {
        return from;
    }

    applyRotations(nodeOverflow.X, nodeOverflow.Z);

    return from;
}

template<class T>
void Avl<T>::remove(T value) {
    Node<T> *node = this->findNode(value);

    if (!node) {
        return;
    }

    Node<T> *from = this->removeImplementation(node);

    if (!from) {
        return;
    }

    updateBalanceFactors(from, true);
    NodeOverflow<T> nodeOverflow = findOverflowedNode(from);

    if (!nodeOverflow.X) {
        return;
    }

    if (nodeOverflow.X == nodeOverflow.Z) {
        if (nodeOverflow.X->left) {
            nodeOverflow.Z = nodeOverflow.X->left;
        } else if (nodeOverflow.X->right) {
            nodeOverflow.Z = nodeOverflow.X->right;
        }
    }

    applyRotations(nodeOverflow.X, nodeOverflow.Z);
}

template<class T>
void Avl<T>::updateBalanceFactors(Node<T> *from, bool hasRemoved) {
    if (from->parent) {
        if (from->parent->left == from && from->parent->right) {
            return;
        }

        if (from->parent->right == from && from->parent->left) {
            return;
        }
    }

    Node<T> *current = from;

    while (current) {
        if (current->parent) {
            if (hasRemoved) {
                --current->parent->height;
            } else {
                ++current->parent->height;
            }
        }

        current = current->parent;
    }
}

template<class T>
NodeOverflow<T> Avl<T>::findOverflowedNode(Node<T> *from) {
    auto prev = from;
    while (from && abs(from->getBalanceFactor()) < 2) {
        prev = from;
        from = from->parent;
    }

    return NodeOverflow<T>(from, prev);
}

template<class T>
void Avl<T>::applyRotations(Node<T> *X, Node<T> *Z) {
    Node<T> *newRoot = nullptr;
    Node<T> *prevParent = X->parent;
    bool isLeft;
    if (X->parent) {
        isLeft = X->parent->left == X;
    }

    if (X->right == Z) {
        if (Z->getBalanceFactor() >= 0) {
            newRoot = rotateLeft(X, Z);
        } else {
            newRoot = rotateRightLeft(X, Z);
        }
    }

    if (X->left == Z) {
        if (Z->getBalanceFactor() <= 0) {
            newRoot = rotateRight(X, Z);
        } else {
            newRoot = rotateLeftRight(X, Z);
        }
    }

    if (prevParent) {
        if (isLeft) {
            prevParent->left = newRoot;
        } else {
            prevParent->right = newRoot;
        }
    } else {
        this->root = newRoot;
    }
}

template<class T>
Node<T> *Avl<T>::rotateLeft(Node<T> *X, Node<T> *Z) {
    Node<T> *t23 = Z->left;
    X->right = t23;
    if (t23) {
        t23->parent = X;
    }

    Z->left = X;
    Z->parent = X->parent;
    X->parent = Z;

    X->height -= 2;
    Z->height = std::max(Z->left->height + 1, Z->right->height + 1);

    return Z;
}

template<class T>
Node<T> *Avl<T>::rotateRight(Node<T> *X, Node<T> *Z) {
    Node<T> *t23 = Z->right;
    X->left = t23;
    if (t23) {
        t23->parent = X;
    }

    Z->right = X;
    Z->parent = X->parent;
    X->parent = Z;

    X->height -= 2;
    Z->height = std::max(Z->left->height + 1, Z->right->height + 1);

    return Z;
}

template<class T>
Node<T> *Avl<T>::rotateRightLeft(Node<T> *X, Node<T> *Z) {
    Node<T> *prevParent = X->parent;

    Node<T> *Y = Z->left;

    Node<T> *t3 = Y->right;
    Z->left = t3;
    if (t3) {
        t3->parent = Z;
    }

    Node<T> *t2 = Y->left;
    X->right = t2;

    if (t2) {
        t2->parent = X;
    }

    Y->right = Z;
    Z->parent = Y;

    Y->left = X;
    X->parent = Y;
    Y->parent = prevParent;

    ++Y->height;
    X->height = std::max(t2 ? t2->height : 0, X->left ? X->left->height : 0) + 1;
    Z->height = std::max(t3 ? t3->height : 0, Z->right ? Z->right->height : 0) + 1;

    return Y;
}

template<class T>
Node<T> *Avl<T>::rotateLeftRight(Node<T> *X, Node<T> *Z) {
    Node<T> *prevParent = X->parent;

    Node<T> *Y = Z->right;

    Node<T> *t2 = Y->right;
    X->left = t2;
    if (t2) {
        t2->parent = X;
    }

    Node<T> *t3 = Y->left;
    Z->right = t3;
    if (t3) {
        t3->parent = Z;
    }

    Y->right = X;
    X->parent = Y;

    Y->left = Z;
    Z->parent = Y;
    Y->parent = prevParent;

    ++Y->height;
    X->height = std::max(t2 ? t2->height : 0, X->right ? X->right->height : 0) + 1;
    Z->height = std::max(t3 ? t3->height : 0, Z->left ? Z->left->height : 0) + 1;

    return Y;
}

#endif //DSA_AVL_HPP
