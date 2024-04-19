#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define _CRT_SECURE_NO_WARGNINGS

typedef struct Node {
    int key;
    int priority;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct Treap {
    Node* tree;
} Treap;

Node* createNode(int key, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->key = key;
        newNode->priority = priority;
        newNode->left = newNode->right = newNode->parent = NULL;
    }
    return newNode;
}

void insertNode(Treap* treap, Node* newNode) {
    if (!treap->tree) {
        treap->tree = newNode;
        return;
    }

    Node* parent = NULL;
    Node* current = treap->tree;

    while (current) {
        parent = current;
        if (newNode->key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;
    if (newNode->key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
}

void transplant(Treap* treap, Node* u, Node* v) {
    if (!u->parent)
        treap->tree = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;
}

Node* minimum(Node* node) {
    while (node->left)
        node = node->left;
    return node;
}

void deleteNode(Treap* treap, Node* target) {
    if (!target)
        return;

    Node* parent = target->parent;

    if (!target->left)
        transplant(treap, target, target->right);
    else if (!target->right)
        transplant(treap, target, target->left);
    else {
        Node* successor = minimum(target->right);
        if (successor->parent != target) {
            transplant(treap, successor, successor->right);
            successor->right = target->right;
            successor->right->parent = successor;
        }
        transplant(treap, target, successor);
        successor->left = target->left;
        successor->left->parent = successor;
    }
    free(target);
}

void insert(Treap* treap, int key, int priority) {
    Node* newNode = createNode(key, priority);
    insertNode(treap, newNode);
}

void removeNode(Treap* treap, int key) {
    Node* current = treap->tree;
    while (current) {
        if (current->key == key) {
            deleteNode(treap, current);
            return;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
}

void PrintTree(struct Node* t, char* result)
{
    if (t != NULL) {
        char c[100];
        sprintf(c, "(%d,%d)", t->key, t->priority);
        strcat(result, c);

        PrintTree(t->left, result);
        PrintTree(t->right, result);
    }
}

//int main() {
//    Treap treap = { NULL };
//
//    insert(&treap, 10, 5);
//    insert(&treap, 5, 3);
//    insert(&treap, 15, 8);
//    insert(&treap, 3, 12);
//    insert(&treap, 7, 1);
//
//    removeNode(&treap, 10);
//    removeNode(&treap, 3);
//    removeNode(&treap, 15);
//
//    return 0;
//}
