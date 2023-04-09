//
// Created by alexs on 2023-03-06.
//

#ifndef DSA_BST_HPP
#define DSA_BST_HPP

#include <vector>
#include <stack>
#include <stdexcept>

template<class T>
struct Node {
    T value;
    Node *left;
    Node *right;
    Node *parent;
    int height;

    Node(T value, Node *parent);

    [[nodiscard]] bool isLeaf() const;

    [[nodiscard]] int getBalanceFactor() const;
};

template<class T>
Node<T>::Node(T value, Node<T> *parent): value(value), left(nullptr), right(nullptr), parent(parent),
                                         height(1) {}

template<class T>
bool Node<T>::isLeaf() const {
    return !left && !right;
}

template<class T>
int Node<T>::getBalanceFactor() const {
    int leftHeight = left ? left->height : 0;
    int rightHeight = right ? right->height : 0;
    return rightHeight - leftHeight;
}

enum TraverseOrder {
    INORDER,
    PREORDER,
    POSTORDER
};

template<class T>
class BstIterator {
private:
    std::stack<Node<T> *> values;
public:
    BstIterator(Node<T> *root, TraverseOrder order);

    BstIterator &operator++();

    Node<T> *getNode() const;

    T getValue() const;

    [[nodiscard]] bool hasNext() const;
};

template<class T>
BstIterator<T>::BstIterator(Node<T> *root, TraverseOrder order) {
    switch (order) {
        // LVD (left, vertex, right)
        case INORDER: {
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<T> *node = t.second;

                if (node->isLeaf()) {
                    values.push(node);
                    tempStack.pop();
                }

                if (count == 2) {
                    tempStack.pop();
                }

                if (count == 0 && node->right) {
                    tempStack.push({0, node->right});
                }

                if (count == 1 && node->left) {
                    values.push(node);
                    tempStack.push({0, node->left});
                }

                ++count;
            }

            break;
        }

            // VLR (vertex, left, right)
        case PREORDER: {
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<T> *node = t.second;

                if (node->isLeaf() || count == 2) {
                    values.push(node);
                    tempStack.pop();
                }

                if (count == 0 && node->right) {
                    tempStack.push({0, node->right});
                }

                if (count == 1 && node->left) {
                    tempStack.push({0, node->left});
                }

                ++count;
            }

            break;
        }

            // LRV (left, right, vertex)
        case POSTORDER: {
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<T> *node = t.second;

                if (node->isLeaf()) {
                    values.push(node);
                    tempStack.pop();
                }

                if (count == 2) {
                    tempStack.pop();
                }

                if (count == 0 && node->right) {
                    values.push(node);
                    tempStack.push({0, node->right});
                }

                if (count == 1 && node->left) {
                    tempStack.push({0, node->left});
                }

                ++count;
            }

            break;
        }

        default: {
            throw std::invalid_argument("Invalid traverse order.");
        }
    }
}

template<class T>
BstIterator<T> &BstIterator<T>::operator++() {
    values.pop();
    return *this;
}

template<class T>
Node<T> *BstIterator<T>::getNode() const {
    return values.top();
}

template<class T>
T BstIterator<T>::getValue() const {
    return values.top()->value;
}

template<class T>
bool BstIterator<T>::hasNext() const {
    return !values.empty();
}

template<class T>
class Bst {
protected:
    Node<T> *root;
    size_t height;
    size_t _size;

    Node<T> *findNode(int value) const;

    Node<T> *findInorderSuccessor(Node<T> *node) const;

    Node<T> *removeImplementation(Node<T> *node);

public:
    explicit Bst();

    ~Bst();

    void insertFromVector(const std::vector<T> &values);

    virtual Node<T> *insert(T value);

    virtual void remove(T value);

    bool has(T value);

    BstIterator<T> getIterator(TraverseOrder order) const;

    size_t getHeight() const;

    size_t size() const;
};

template<class T>
Bst<T>::Bst(): root(nullptr), height(0), _size(0) {}

template<class T>
Bst<T>::~Bst() {
    if (root) {
        BstIterator<T> it(root, PREORDER);

        while (it.hasNext()) {
            delete it.getNode();
            ++it;
        }
    }
}

// Methods

template<class T>
void Bst<T>::insertFromVector(const std::vector<T> &values) {
    for (auto x: values) {
        insert(x);
    }
}

template<class T>
Node<T> *Bst<T>::insert(T value) {
    if (!root) {
        root = new Node<T>(value, (Node<T> *) nullptr);
        height = 1;
        ++_size;
        return root;
    }

    Node<T> *parent = root;
    Node<T> *node = root;

    while (node) {
        if (node->value == value) {
            return node;
        }

        parent = node;

        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    ++_size;
    if (parent->isLeaf()) {
        ++height;
    }

    if (value < parent->value) {
        parent->left = new Node<T>(value, parent);
        return parent->left;
    } else {
        parent->right = new Node<T>(value, parent);
        return parent->right;
    }
}

template<class T>
void Bst<T>::remove(T value) {
    Node<T> *node = findNode(value);

    if (!node) {
        return;
    }

    removeImplementation(node);
}

template<class T>
BstIterator<T> Bst<T>::getIterator(TraverseOrder order) const {
    return BstIterator<T>(root, order);
}

template<class T>
Node<T> *Bst<T>::findNode(int value) const {
    Node<T> *node = root;

    while (node) {
        if (node->value == value) {
            break;
        }

        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node;
}

template<class T>
Node<T> *Bst<T>::findInorderSuccessor(Node<T> *node) const {
    while (node && node->left) {
        node = node->left;
    }

    return node;
}

template<class T>
Node<T> *Bst<T>::removeImplementation(Node<T> *node) {
    T value = node->value;

    Node<T> *parent = node->parent;

    // Node is leaf
    if (node->isLeaf()) {
        if (parent) {
            if (value < parent->value) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }

        delete node;
        return parent;
    }

    // Has one left child
    if (!node->right) {
        if (parent) {
            if (value < parent->value) {
                parent->left = node->left;
            } else {
                parent->right = node->left;
            }
        } else {
            root = node->left;
        }

        delete node;
        return parent;
    }

    // Has one right child
    if (!node->left) {
        if (parent) {
            if (value < parent->value) {
                parent->left = node->right;
            } else {
                parent->right = node->right;
            }
        } else {
            root = node->right;
        }

        delete node;
        return parent;
    }

    Node<T> *temp = findInorderSuccessor(node->right);
    node->value = temp->value;
    return removeImplementation(temp);
}

template<class T>
bool Bst<T>::has(T value) {
    return static_cast<bool>(findNode(value));
}

template<class T>
size_t Bst<T>::size() const {
    return _size;
}

template<class T>
size_t Bst<T>::getHeight() const {
    return height;
}

#endif //DSA_BST_HPP
