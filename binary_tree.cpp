#include "binarytree.h"
#include "newwindow.h"
#include <cstdlib>
#include <cmath>
#include <QString>

BinaryTree::BinaryTree() {
    left = nullptr;
    right = nullptr;
}

BinaryTree::BinaryTree(int new_data) {
    data = new_data;
    left = nullptr;
    right = nullptr;
}

void BinaryTree::insert(BinaryTree*& root, int data) {
    BinaryTree* newNode = new BinaryTree(data);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    BinaryTree* prev = nullptr, * cur = root;
    while (cur) {
        if (data < cur->data) {
            prev = cur;
            cur = cur->left;
        }
        else if (data > cur->data) {
            prev = cur;
            cur = cur->right;
        }
    }
    if (data < prev->data) prev->left = newNode;
    else prev->right = newNode;
}

BinaryTree* BinaryTree::find(BinaryTree* root, int data) {
    while (root != nullptr) {
        if (data < root->data) root = root->left;
        else if (data > root->data) root = root->right;
        else return root;
    }
    return nullptr;
}

int BinaryTree::get_size(BinaryTree* root) {
    if (root == nullptr) return 0;
    else return get_size(root->right) + get_size(root->left) + 1;
}

int BinaryTree::get_height(BinaryTree* root) {
    if (root == nullptr) return -1;
    return std::max(get_height(root->left), get_height(root->right)) + 1;
}

BinaryTree* BinaryTree::erase(BinaryTree* root, int data) {
    BinaryTree* cur = root, * prev = nullptr;
    while (cur != nullptr && cur->data != data) {
        prev = cur;
        if (data < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    if (cur == nullptr) return root;
    if (cur->left == nullptr || cur->right == nullptr) {
        BinaryTree* newCur;
        if (cur->left == nullptr) newCur = cur->right;
        else newCur = cur->left;
        if (prev == nullptr) return newCur;
        if (cur == prev->left) prev->left = newCur;
        else prev->right = newCur;
        free(cur);
    }
    else {
        BinaryTree* temp, * par = nullptr;
        temp = cur->right;
        while (temp->left != nullptr) {
            par = temp;
            temp = temp->left;
        }
        if (par != nullptr) par->left = temp->right;
        else cur->right = temp->right;
        cur->data = temp->data;
        free(temp);
    }
    return root;
}

void BinaryTree::preOrder_print(BinaryTree* root, QString* text_file) {
    if (root == nullptr) return;
    text_file->append(QString::number(root->data) + " ");
    preOrder_print(root->left, text_file);
    preOrder_print(root->right, text_file);
}

void BinaryTree::inOrder_print(BinaryTree* root, QString* text_file) {
    if (root == nullptr) return;
    inOrder_print(root->left, text_file);
    text_file->append(QString::number(root->data) + " ");
    inOrder_print(root->right, text_file);
}

void BinaryTree::postOrder_print(BinaryTree* root, QString* text_file) {
    if (root == nullptr) return;
    inOrder_print(root->left, text_file);
    inOrder_print(root->right, text_file);
    text_file->append(QString::number(root->data) + " ");
}

void BinaryTree::print2D(BinaryTree* root, int spaces, QString* text_tree) {
    if (root == NULL) return;
    spaces += 10;
    print2D(root->right, spaces, text_tree);
    text_tree->append("\n");
    for (int i = 10; i < spaces; i++) text_tree->append(" ");
    text_tree->append(QString::number(root->data) + "\n");
    print2D(root->left, spaces, text_tree);
}

BinaryTree* BinaryTree::arrToTree(QStringList words) {
    BinaryTree* root = nullptr;
    for (int i = 0; i < words.size() - 1; i++) {
        root->insert(root, words[i].toInt());
    }
    return root;
}

int BinaryTree::treeToVine(BinaryTree* grand) {
    int count = 0;
    BinaryTree* temp = grand->right;

    while (temp) {
        if (temp->left) {
            BinaryTree* oldTemp = temp;
            temp = temp->left;
            oldTemp->left = temp->right;
            temp->right = oldTemp;
            grand->right = temp;
        }
        else {
            count++;
            grand = temp;
            temp = temp->right;
        }
    }
    return count;
}

void BinaryTree::compress(BinaryTree* grand, int m) {
    BinaryTree* temp = grand->right;
    for (int i = 0; i < m; i++) {
        BinaryTree* oldTemp = temp;
        temp = temp->right;
        grand->right = temp;
        oldTemp->right = temp->left;
        temp->left = oldTemp;
        grand = temp;
        temp = temp->right;
    }
}

BinaryTree* BinaryTree::balanceTree(BinaryTree* root) {
    BinaryTree* grand = new BinaryTree(0);
    grand->right = root;
    int count = treeToVine(grand);
    int h = log2(count + 1);
    int m = pow(2, h) - 1;
    compress(grand, count - m);
    for (m = m / 2; m > 0; m /= 2) {
        compress(grand, m);
    }
    return grand->right;
}

bool BinaryTree::isComplete_w(BinaryTree* root, int index, int size) {
    if (root == nullptr) return true;
    if (index >= size) return false;
    return (isComplete_w(root->left, 2 * index + 1, size) && isComplete_w(root->right, 2 * index + 2, size));
}

bool BinaryTree::isComplete(BinaryTree* root) {
    int size = get_size(root);
    int index = 0;
    return isComplete_w(root, index, size);
}

void BinaryTree::delete_tree(BinaryTree* root) {
    if (root == nullptr) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}
