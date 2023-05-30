#include<iostream>
using namespace std;
#define N 3
// Define a B+ tree node structure
struct BPlusNode {
    int keys[N]; // Keys array to hold the data
    BPlusNode* child[N + 1]; // Pointers to child nodes
    int numKeys; // Number of keys currently in node
    bool leaf; // Indicates whether node is a leaf node
     // Constructor to initialize the node variables
    BPlusNode() {
        numKeys = 0;
        leaf = true;
        for (int i = 0; i <= N; i++) {
            child[i] = NULL;
        }
    }
};
 // Insert a data element into the B+ tree
void insert(BPlusNode* root, int data) {
    BPlusNode* node = search(root, data);
    int i;
    for (i = 0; i < node->numKeys && node->keys[i] < data; i++);
    for (int j = node->numKeys; j > i; j--) {
        node->keys[j] = node->keys[j - 1];
    }
    node->keys[i] = data;
    node->numKeys++;
    if (node->numKeys == N) {
        split(node);
    }
}
 // Split a full node into two nodes
void split(BPlusNode* node) {
    BPlusNode* newNode = new BPlusNode;
    newNode->leaf = node->leaf;
    newNode->numKeys = N / 2;
    node->numKeys = N / 2;
    for (int i = 0; i < N / 2; i++) {
        newNode->keys[i] = node->keys[i + N / 2];
    }
    if (!node->leaf) {
        for (int i = 0; i <= N / 2; i++) {
            newNode->child[i] = node->child[i + N / 2];
        }
    }
    for (int i = node->numKeys; i < N; i++) {
        node->keys[i] = 0;
        if (!node->leaf) {
            node->child[i + 1] = NULL;
        }
    }
    insert(node->parent, newNode->keys[0]);
    node->next = newNode;
    newNode->prev = node;
    newNode->parent = node->parent;
    if (node == root) {
        root = new BPlusNode;
        root->leaf = false;
        root->numKeys = 1;
        root->keys[0] = newNode->keys[0];
        root->child[0] = node;
        root->child[1] = newNode;
        node->parent = root;
        newNode->parent = root;
    }
}
 // Search for a node where data needs to be inserted
BPlusNode* search(BPlusNode* node, int data) {
    int i;
    for (i = 0; i < node->numKeys && node->keys[i] < data; i++);
    if (node->leaf) {
        return node;
    } else {
        return search(node->child[i], data);
    }
}
 // Traverse the B+ tree
void traverse(BPlusNode* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < root->numKeys; i++) {
        cout << root->keys[i] << " ";
    }
    if (!root->leaf) {
        for (int i = 0; i <= root->numKeys; i++) {
            traverse(root->child[i]);
        }
    }
}
 int main() {
    BPlusNode* root = new BPlusNode;
    insert(root, 5);
    insert(root, 7);
    insert(root, 10);
    insert(root, 16);
    insert(root, 26);
    insert(root, 37);
    insert(root, 40);
    insert(root, 70);
    traverse(root);
    return 0;
}