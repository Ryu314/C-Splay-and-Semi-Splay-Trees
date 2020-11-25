//
// Created by R Yu on 11/4/2020.
//

#ifndef HOMEWORK_9_BINARYTREE_H
#define HOMEWORK_9_BINARYTREE_H
#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node *parent;
    Node(int x) {
        data = x;
        left = right = parent = NULL;
    }
    Node(int x, Node *p) {
        data = x;    parent = p;    left = right = NULL;
    }
    void print(int indent) {
        cout << data << endl;
        indent ++;
        if (right != NULL) {
            for (int i = 0; i < indent ; i++ )
                cout << "\t";
            right->print(indent);
        }
        if (left != NULL) {
            for (int i = 0; i < indent ; i++ )
                cout << "\t";
            left->print(indent);
        }
    }
};
class BTree {
public:
    Node *root;
    BTree(){
        root = NULL;
    };
    BTree(Node *r){
        root = r;
    }
    void insert(int x) {
        Node *prev = NULL;
        Node *curr = root;
        //traverse down the tree to find the correct position
        while (curr != NULL) {
            prev = curr;
            if (x <= curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        //insert the Node
        // case 1: the tree is empty, this is the first Node
        if (root == NULL) {
            root = new Node (x);
        }
        // case 2: tree is not empty
        else if (x <= prev->data)
            prev->left = new Node(x, prev) ;
        else //x > prev->data
            prev->right = new Node(x, prev);
    }
    void rotateRight(Node *Gr, Node *Par, Node *Ch) {
        if (Par != root ) {
            //Gr becomes Ch's parent
            if(Gr->right == Par) {
                Gr->right = Ch;
                Ch->parent = Gr;
            }
            else if(Gr->left == Par){
                Gr->left = Ch;
                Ch->parent = Gr;
            }
            if (Ch->right != NULL) {
                // right child of Ch (Q) becomes left child of Par
                Par->left = Ch->right;
                Ch->right->parent = Par;
                //only works when Q is not null
            }
            else {
                Par->left = NULL;
            }
            //Ch acquires Par as its right child
            Ch->right = Par;
            Par->parent = Ch;
        }
        else {
            if (Ch->right != NULL) { // right child of Ch (Q) becomes left child of Pa
                Par->left = Ch->right;
                Ch->right->parent = Par; //only works when Q is not null
            }
            else {
                Par->left = NULL;
            }
            //Ch acquires Par as its right child
            Ch->right = Par;
            Par->parent = Ch;
            root = Ch;
            Ch->parent = NULL;
        }
    }
    void rotateLeft(Node *Gr, Node *Par, Node *Ch) {
        if (Par != root ) {
            //Gr becomes Ch's parent
            if(Gr->left == Par) {
                Gr->left = Ch;
                Ch->parent = Gr;
            }
            else if(Gr->right == Par){
                Gr->right = Ch;
                Ch->parent = Gr;
            }
            if (Ch->left != NULL) {
                // right child of Ch (Q) becomes left child of Par
                Par->right = Ch->left;
                Ch->left->parent = Par;
                //only works when Q is not null
            }
            else {
                Par->right = NULL;
            }
            //Ch acquires Par as its right child
            Ch->left = Par;
            Par->parent = Ch;
        }
        else {
            if (Ch->left != NULL) { // right child of Ch (Q) becomes left child of Pa
                Par->right = Ch->left;
                Ch->left->parent = Par; //only works when Q is not null
            }
            else {
                Par->right = NULL;
            }
            //Ch acquires Par as its right child
            Ch->left = Par;
            Par->parent = Ch;
            root = Ch;
            Ch->parent = NULL;

        }
    }
    void splay(int x){
        Node *curr = root;
        //traverse down the tree to find the correct position

        while (curr != NULL){
            if (x < curr->data) {
                curr = curr->left;
            }
            else if (x == curr->data) {
                break;
            }
            else {
                curr = curr->right;
            }
        }
        while(curr != root){
            if(curr->parent->parent == NULL){
                if(curr->parent->left == curr){
                    rotateRight(curr->parent->parent, curr->parent, curr);
                    //cout <<"Right Rotation complete" << endl;
                }
                else if(curr->parent->right == curr){
                    rotateLeft(curr->parent->parent, curr->parent, curr);
                    //cout <<"Left Rotation complete" << endl;
                    //root->print(0);
                    //cout << root->data << endl;
                }
            }
            else {
                if(curr->parent->left == curr and curr->parent->parent->left == curr->parent){
                    //cout <<"ZigZigLeft" << endl;
                    rotateRight(curr->parent->parent->parent, curr->parent->parent, curr->parent);
                    //root->print(0);

                    rotateRight(curr->parent->parent, curr->parent, curr);
                    //root->print(0);

                }
                else if(curr->parent->right == curr and curr->parent->parent->right == curr->parent){
                    //cout << "ZigZigRight" << endl;
                    rotateLeft(curr->parent->parent->parent, curr->parent->parent, curr->parent);
                    rotateLeft(curr->parent->parent, curr->parent, curr);
                }
                else if(curr->parent->right == curr and curr->parent->parent->left == curr->parent) {
                    //cout << "ZigZag" << endl;
                    rotateLeft(curr->parent->parent, curr->parent, curr);
                    //root->print(0);
                    rotateRight(curr->parent->parent, curr->parent, curr);
                    //root->print(0);
                }
                else{
                    //cout << "ZagZig" << endl;
                    rotateRight(curr->parent->parent, curr->parent, curr);
                    //root->print(0);
                    rotateLeft(curr->parent->parent, curr->parent, curr);
                    //root->print(0);
                }
            }
            //root->print(0);
        }

    }
    void semi_splay(int x) {
        Node *curr = root;
        //traverse down the tree to find the correct position
        while (curr != NULL) {
            if (x < curr->data)
                curr = curr->left;
            else if (x == curr->data)
                break;
            else
                curr = curr->right;
        }
        while (curr->parent != NULL) {
            if (curr->parent->parent == NULL) {
                if (curr->parent->left == curr) {
                    rotateRight(curr->parent->parent, curr->parent, curr);
                } else if (curr->parent->right == curr) {
                    rotateLeft(curr->parent->parent, curr->parent, curr);
                }
            } else {
                if (curr->parent->left == curr and curr->parent->parent->left == curr->parent) {
                    rotateRight(curr->parent->parent->parent, curr->parent->parent, curr->parent);
                    //root->print(0);
                    curr = curr->parent;
                } else if (curr->parent->right == curr and curr->parent->parent->right == curr->parent) {
                    rotateLeft(curr->parent->parent->parent, curr->parent->parent, curr->parent);
                    curr = curr->parent;
                } else if (curr->parent->right == curr and curr->parent->parent->left == curr->parent) {
                    rotateLeft(curr->parent->parent, curr->parent, curr);
                    rotateRight(curr->parent->parent, curr->parent, curr);
                } else {
                    rotateRight(curr->parent->parent, curr->parent, curr);
                    rotateLeft(curr->parent->parent, curr->parent, curr);
                }
            }
        }
    }

};
#endif //HOMEWORK_9_BINARYTREE_H
