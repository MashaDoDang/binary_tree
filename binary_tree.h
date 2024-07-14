#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <QString>

class BinaryTree
{
public:
    int data;
    BinaryTree* left, * right;

    BinaryTree();

    BinaryTree(int new_data);
    void insert(BinaryTree*& root, int data);
    BinaryTree* find(BinaryTree* root, int data);

    int get_height(BinaryTree* root);
    int get_size(BinaryTree* root);
    BinaryTree* erase(BinaryTree* root, int data);

    void preOrder_print(BinaryTree* root, QString* text_file);
    void inOrder_print(BinaryTree* root, QString* text_file);
    void postOrder_print(BinaryTree* root, QString* text_file);
    void print2D(BinaryTree* root, int spaces, QString* text_file);
    BinaryTree* arrToTree(QStringList words);

    int treeToVine(BinaryTree* grand);
    void compress(BinaryTree* grand, int m);
    BinaryTree* balanceTree(BinaryTree* root);

    bool isComplete_w(BinaryTree* root, int index, int size);
    bool isComplete(BinaryTree* root);

    void delete_tree(BinaryTree* root);
};

#endif // BINARYTREE_H
