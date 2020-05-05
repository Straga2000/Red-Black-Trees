#include <iostream>
#include "RBTrees.h"

int main()
{
    int dim; cin>>dim;
    RBTree *T = new RBTree(dim);
    cin>>*T;
    /*T->insert_node(6);
    T->insert_node(3);
    T->insert_node(12);
    T->insert_node(16);
    T->insert_node(20);
    T->insert_node(32);*/
    cout<<*T;
    T->find_minimum();
    T->find_maximum();
    T->search_node(15);
}
