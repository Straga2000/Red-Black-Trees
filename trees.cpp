#include <iostream>
#include "trees.h"
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int dim; cin>>dim;

    tree *T = new tree(dim);
    cin>>*T;
    /*T->insert_node(3);
    T->insert_node(0);
    T->insert_node(10);
    T->insert_node(12);
    T->insert_node(5);
    T->insert_node(6);
    T->insert_node(8);
    T->insert_node(-1);
    T->insert_node(2);
    T->insert_node(16);*/
    T->find_maximum();
    T->find_minimum();
    T->search_node(3);
    T->delete_node(4);
    cout<<*T;
    /*T->show_tree();*/

}
