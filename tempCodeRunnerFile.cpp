
//DEVA ANAND M
//CS23B1020
#include <iostream>
using namespace std;

struct Node 
{
    int data;
    Node* left;
    Node* right;
    int height;
};

int max(int a, int b) 
{
    return (a > b) ? a : b;
}

int getHeight(Node* node) 
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int getBalance(Node* node) 
{
    if (node == nullptr) 
    {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* newNode(int data) 
{
    Node* node = new Node();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) 
{
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) 
{
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int data) 
{
    if (node == nullptr)
    {
        return newNode(data);
    }
    if (data < node->data)
    {
        node->left = insert(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
    }
    else
    {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
    {
        return rightRotate(node);
    }
    if (balance < -1 && data > node->right->data)
    {
        return leftRotate(node);
    }
    if (balance > 1 && data > node->left->data) 
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && data < node->right->data) 
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* root) 
{
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    int values[] = {45, 67, 34, 12, 19, 69, 98, 27, 9};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
    {
        root = insert(root, values[i]);
    }
    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    return 0;
}
