#include <iostream>
#include "BinaryTree.h"
using namespace std;

int main() {
    BTree *tree = new BTree();
    /*int a[] = {20, 21, 18, 19, 16, 17, 14, 15, 12, 13, 11} ;
    for (int i = 0; i < 11 ; i ++) {
        tree->insert(a[i]);
    }
    tree->splay(12);
    tree->splay(16);
    tree->semi_splay(12);
    tree->semi_splay(12);
    tree->root->print(0);
     */
    /*for (int i = 0; i < 7 ; i ++) {
        tree->insert(a[i]);
    }
    tree->insert(5);
    tree->insert(7);
    tree->insert(6);
    tree->splay(6);
    tree->root->print(0);*/
    for(int i = 0; i < 10; i++){
        int x;
        cout << "Enter a number: ";
        cin >> x;
        cout << endl;
        tree->insert(x);
        tree->splay(x);
        tree->root->print(0);
    }
    return 0;
}
