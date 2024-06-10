#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right), height(1) {}
};

class AVLTree {
private:
    TreeNode* root;

    int height(TreeNode* node) {
        return node ? max(height(node->left), height(node->right)) + 1 : 0;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        return y;
    }

    int getBalance(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    TreeNode* newNode(int key) {
        return new TreeNode(key);
    }

    TreeNode* insertRecursive(TreeNode* node, int key) {
        if (node == nullptr)
            return newNode(key);

        if (key < node->val)
            node->left = insertRecursive(node->left, key);
        else if (key > node->val)
            node->right = insertRecursive(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->val)
            return rightRotate(node);

        if (balance < -1 && key > node->right->val)
            return leftRotate(node);

        if (balance > 1 && key > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    TreeNode* deleteNodeRecursive(TreeNode* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->val)
            root->left = deleteNodeRecursive(root->left, key);
        else if (key > root->val)
            root->right = deleteNodeRecursive(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                TreeNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;

                delete temp;
            } else {
                TreeNode* temp = minValueNode(root->right);
                root->val = temp->val;
                root->right = deleteNodeRecursive(root->right, temp->val);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    void inorderRecursive(TreeNode* root) {
        // Realiza un recorrido inorden del arbol con root en "root"
        // Cambiar el orden de 'cout' para pre  y post
        if (root != nullptr) {
            inorderRecursive(root->left);
            cout << root->val << " ";
            inorderRecursive(root->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insertRecursive(root, key);
    }

    void deleteNode(int key) {
        root = deleteNodeRecursive(root, key);
    }

    void inorderTraversal() {
        inorderRecursive(root);
        cout << endl;
    }
};

int main() {
    AVLTree avl;

    avl.insert(35); avl.insert(30); avl.insert(27);
    avl.insert(11); avl.insert(16); avl.insert(100);
    avl.insert(50); avl.insert(91); avl.insert(73);
    avl.insert(5);

    cout << "AVL construido: " << endl; avl.inorderTraversal();

    avl.deleteNode(30); avl.deleteNode(35);
    avl.deleteNode(100);

    cout << "AVL borrado y ordenado: " << endl; avl.inorderTraversal();

    return 0;
}
