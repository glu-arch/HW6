#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <string>

#define COLOR_RED 0
#define COLOR_BLACK 1

struct RBTNode {
    int data;
    int color = COLOR_RED;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;
    RBTNode* parent = nullptr;
};

class RedBlackTree {
public:
    RedBlackTree();
    RedBlackTree(int value);
    RedBlackTree(const RedBlackTree& other);

    void Insert(int value);
    bool Contains(int value) const;
    int GetMin() const;
    int GetMax() const;
    unsigned long long int Size() const { return numItems; }

    std::string ToInfixString() const { return ToInfixString(root); }
    std::string ToPrefixString() const { return ToPrefixString(root); }
    std::string ToPostfixString() const { return ToPostfixString(root); }

private:
    unsigned long long int numItems = 0;
    RBTNode* root = nullptr;

    void RotateLeft(RBTNode* node);
    void RotateRight(RBTNode* node);
    void FixInsert(RBTNode* node);
    RBTNode* CopyTree(RBTNode* node, RBTNode* parent);

    std::string ToInfixString(RBTNode* node) const;
    std::string ToPrefixString(RBTNode* node) const;
    std::string ToPostfixString(RBTNode* node) const;
};

#endif
