#include "RedBlackTree.h"
#include <stdexcept>

using namespace std;

// Sources: assignment_6_description.pdf (interfaces and exceptions),
// RedBlackTreeTests.cpp (tree shapes and string format).
// Implementation and explanation assistance: OpenAI Codex, 2026-11-08.

RedBlackTree::RedBlackTree() {
    // The header already initializes root to nullptr and numItems to 0.
}

RedBlackTree::RedBlackTree(int value) {
    Insert(value);
}

RedBlackTree::RedBlackTree(const RedBlackTree& other) {
    root = CopyTree(other.root, nullptr);
    numItems = other.numItems;
}

RBTNode* RedBlackTree::CopyTree(RBTNode* node, RBTNode* parent) {
    if (node == nullptr) {
        return nullptr;
    }

    // New nodes keep the two trees independent; preserve shape and colors.
    RBTNode* copy = new RBTNode;
    copy->data = node->data;
    copy->color = node->color;
    copy->parent = parent;
    copy->left = CopyTree(node->left, copy);
    copy->right = CopyTree(node->right, copy);
    return copy;
}

bool RedBlackTree::Contains(int value) const {
    RBTNode* current = root;
    while (current != nullptr) {
        if (value == current->data) {
            return true;
        }
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

int RedBlackTree::GetMin() const {
    if (root == nullptr) {
        throw invalid_argument("An empty tree has no minimum");
    }

    RBTNode* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->data;
}

int RedBlackTree::GetMax() const {
    if (root == nullptr) {
        throw invalid_argument("An empty tree has no maximum");
    }

    RBTNode* current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->data;
}

void RedBlackTree::Insert(int value) {
    RBTNode* current = root;
    RBTNode* parent = nullptr;

    // Find the BST position before allocating, so duplicates do not change the tree.
    while (current != nullptr) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            throw invalid_argument("Duplicate value");
        }
    }

    RBTNode* node = new RBTNode;
    node->data = value;
    node->parent = parent;

    if (parent == nullptr) {
        root = node;
    } else if (value < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    numItems++;
    FixInsert(node);
}

void RedBlackTree::FixInsert(RBTNode* node) {
    // A red node needs repair only when its parent is also red.
    while (node != root && node->parent->color == COLOR_RED) {
        RBTNode* parent = node->parent;
        RBTNode* grandparent = parent->parent;

        if (parent == grandparent->left) {
            RBTNode* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // Keep black heights equal; check the grandparent next.
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                // A nullptr uncle counts as black.
                if (node == parent->right) {
                    // LR: first turn the triangle into an LL line.
                    node = parent;
                    RotateLeft(node);
                }

                // LL: rotate the grandparent and recolor.
                parent = node->parent;
                grandparent = parent->parent;
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RotateRight(grandparent);
            }
        } else {
            // Same cases with left and right exchanged.
            RBTNode* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == COLOR_RED) {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    // RL: first turn the triangle into an RR line.
                    node = parent;
                    RotateRight(node);
                }

                // RR: rotate the grandparent and recolor.
                parent = node->parent;
                grandparent = parent->parent;
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RotateLeft(grandparent);
            }
        }
    }

    // Recoloring may have reached the root; the root must always be black.
    root->color = COLOR_BLACK;
}

void RedBlackTree::RotateLeft(RBTNode* node) {
    RBTNode* child = node->right;

    // The child's left subtree moves to the node's right side.
    node->right = child->left;
    if (child->left != nullptr) {
        child->left->parent = node;
    }

    // Connect the promoted child to the old parent (or make it the root).
    child->parent = node->parent;
    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    child->left = node;
    node->parent = child;
}

void RedBlackTree::RotateRight(RBTNode* node) {
    RBTNode* child = node->left;

    // Mirror of RotateLeft: the child's right subtree changes sides.
    node->left = child->right;
    if (child->right != nullptr) {
        child->right->parent = node;
    }

    child->parent = node->parent;
    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    child->right = node;
    node->parent = child;
}

string RedBlackTree::ToInfixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    string color = "B";
    if (node->color == COLOR_RED) {
        color = "R";
    }
    string item = " " + color + to_string(node->data) + " ";
    return ToInfixString(node->left) + item + ToInfixString(node->right);
}

string RedBlackTree::ToPrefixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    string color = "B";
    if (node->color == COLOR_RED) {
        color = "R";
    }
    string item = " " + color + to_string(node->data) + " ";
    return item + ToPrefixString(node->left) + ToPrefixString(node->right);
}

string RedBlackTree::ToPostfixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    string color = "B";
    if (node->color == COLOR_RED) {
        color = "R";
    }
    string item = " " + color + to_string(node->data) + " ";
    return ToPostfixString(node->left) + ToPostfixString(node->right) + item;
}
