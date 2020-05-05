#ifndef TREES_H_INCLUDED
#define TREES_H_INCLUDED

#include "nodes.h"
#include "tree_template.h"
#include <iostream>
using namespace std;

///ABC (Nod *rad):Arbore
///https://www.tutorialspoint.com/cplusplus-program-to-perform-left-rotation-on-a-binary-search-tree

class tree : virtual public tree_template{

private:
    node *head;
    int counter;

    node* insert_node(int data, node *head)
    {
        if (head != NULL)
        {
            if (data <= head->get_info())
            {
                head->set_st(insert_node(data, head->get_st()));
                head = balance(head);
            }
            else
            {
                head->set_dr(insert_node(data, head->get_dr()));
                head = balance(head);
            }
        }
        else
            return new node(data);
    }

    void print_tree(node *head)
    {
        if (head != NULL)
        {
            counter ++;
            for(int i = 1; i < counter; i++)
                cout<<"\t";
            cout<<*head;

            print_tree(head->get_st());
            print_tree(head->get_dr());
            counter --;
        }
    }

    node* delete_node(int data, node *head)
    {
        if (head == NULL)
            return head;
        else if (data < head->get_info())
            head->set_st(delete_node(data, head->get_st()));
        else if (data > head->get_info())
            head->set_dr(delete_node(data, head->get_dr()));
        else
        {
            if (head->get_st() == NULL && head->get_dr() == NULL)
            {
                delete head;
                head = NULL;
            }
            else if(head->get_st() == NULL )
            {
                node *temp = head;
                head->set_dr(head);
                delete temp;
            }
            else if(head->get_dr() == NULL )
            {
                node *temp = head;
                head->set_st(head);
                delete temp;
            }
            else
            {
                node *temp = find_minimum(head->get_dr());
                head->set_info(temp->get_info());
                head->set_dr(delete_node(temp->get_info(), head->get_dr()));
            }
        }
        return head;
    }


    node *search_node(node *temp, int info)
    {
        if (temp == NULL)
            return NULL;

        if (temp->info == info)
            return temp;

        if (temp->info > info)
        {
            node *leftValue = search_node(temp->st, info);

            if (leftValue != NULL)
                return leftValue;
        }

        if (temp->info < info)
        {
            node *rightValue = search_node(temp->dr, info);

            if (rightValue != NULL)
                return rightValue;
        }

        return NULL;
    }

    node *find_minimum(node *head)
    {
        if (head->get_st() == NULL)
            return head;
        else
            return find_minimum(head->get_st());
    }

    node *find_maximum(node *head)
    {
        if (head->get_dr() == NULL)
            return head;
        else
            return find_maximum(head->get_dr());
    }

    ///o rotatie a elementelor din dreapta spre stanga
    node *rr_rotation(node *head)
    {
        node *temp = head->get_dr();
        head->set_dr(temp->get_st());
        temp->set_st(head);

        return temp;
    }

    ///o rotatie a elementelor din stanga spre dreapta
    node *ll_rotation(node *head)
    {
        node *temp = head->get_st();
        head->set_st(temp->get_dr());
        temp->set_dr(head);

        return temp;
    }

    node *lr_rotation(node *head)
    {

        node *temp = head->get_st();
        head->set_st(rr_rotation(temp));

        return ll_rotation(head);
    }

    node *rl_rotation(node *head)
    {

        node *temp = head->get_dr();
        head->set_dr(ll_rotation(temp));

        return rr_rotation(head);
    }

        int height(node *head)
    {
        if (head != NULL)
            return max(height(head->get_st()), height(head->get_dr())) + 1;

        return 0;
    }

    int diff(node *head)
    {
        return height(head->get_st()) - height(head->get_dr());
    }

    node *balance(node *head)
    {

        int bal_factor = diff(head);

        if (bal_factor > 1)

            if (diff(head->get_st()) > 0)
                head = ll_rotation(head);
            else
                head = lr_rotation(head);

        else if (bal_factor < -1)

            if (diff(head->get_dr()) > 0)
                head = rl_rotation(head);
            else
                head = rr_rotation(head);

        return head;
    }

public:

    tree(int n):tree_template(n)
    {
        head = NULL;
        counter = 0;
    }

    void show_tree()
    {
        print_tree(head);
    }

    void insert_node(int data)
    {
        head = insert_node(data, head);
    }

    void delete_node(int data)
    {
        head = delete_node(data, head);
    }

    void search_node(int data)
    {
        node *result =  search_node(head, data);

        if (result == NULL)
            cout<<"Valoarea "<<data<<" nu exista in arbore.\n";
        else
            cout<<"Valoarea "<<data<<" exista in arbore.\n";
    }

    void find_minimum()
    {
        node *result = find_minimum(head);

        if(result == NULL)
            cout<<"Nu exista noduri in arbore.\n";
        else
            cout<<"Minimul este "<<result->get_info()<<".\n";
    }

    void find_maximum()
    {
        node *result = find_maximum(head);

        if(result == NULL)
            cout<<"Nu exista noduri in arbore.\n";
        else
            cout<<"Maximul este "<<result->get_info()<<".\n";
    }

    void delete_tree(node* head)
    {
        if(head->get_st() == NULL && head->get_dr() == NULL)
            delete head;
        else
        {
            delete_tree(head->get_st());
            delete_tree(head->get_dr());
        }
    }

    friend ostream& operator << (ostream &output, tree &tree)
    {
        if(tree.head == NULL)
            output<<"The tree is empty.\n";
        else
            tree.show_tree();
        return output;
    }

    ~tree()
    {
        delete_tree(head);
    }

};

#endif // TREES_H_INCLUDED
