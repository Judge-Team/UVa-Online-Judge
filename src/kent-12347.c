#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int preOrderTree[10000];

typedef struct _node {
    int data;
    struct _node *left;
    struct _node *right;
} NODE, *PNODE;

PNODE allocNode(int data)
{
    PNODE new = (PNODE)malloc(sizeof(NODE));
    if (new) {
        new->data = data;
        new->left = NULL;
        new->right = NULL;
    }
    return new;
}

void insertNode(PNODE parent, PNODE node)
{
    if (!parent) {
        return;
    }

    if (parent->data > node->data) {
        if (parent->left == NULL) {
            parent->left = node;
        } 
        else {
            insertNode(parent->left, node);
        }
    }
    else {
        if (parent->right == NULL) {
            parent->right = node;
        }
        else {
            insertNode(parent->right,node);
        }
    }
}

void ShoePostOrder(PNODE node)
{
    if (node == NULL) {
        return;
    }

    ShoePostOrder(node->left);
    ShoePostOrder(node->right);
    printf("%d\n",node->data);
}

int main()
{
    int data;
    int count = 0;
    PNODE root = NULL;
    PNODE node = NULL;

    while (scanf("%d",&data) != EOF) {
        node = allocNode(data);
        if (count == 0) {
            root = node;
        }
        else {
            insertNode(root,node);
        }

        count++;
    }

    ShoePostOrder(root);
    
    return 0;
}
