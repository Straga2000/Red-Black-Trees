#ifndef RBTREES_H_INCLUDED
#define RBTREES_H_INCLUDED

#include "tree_template.h"
#include "nodes.h"
using namespace std;

///Arbore_bicolor (Nod_rosu_negru *rad) : Arbore
class RBTree : virtual public tree_template
{
    private:
        RBNode *head;
        int counter;

        void rotate_left(RBNode *&, RBNode *&);
        void rotate_right(RBNode *&, RBNode *&);

        bool get_color(RBNode *);
        void set_color(RBNode *, bool);

        void print_tree(RBNode *);

        RBNode* insert_node(RBNode*, RBNode *);
        RBNode *search_node(RBNode *, int);

        void fix_violation(RBNode *&, RBNode *&);

    public:

        RBTree(int n) : tree_template(n)
        {
            head = NULL;
            counter = 0;
        }

        RBNode* get_head();

        void delete_node (int) {};
        void insert_node(int);
        void search_node(int);


        void show_tree();

        void find_minimum();
        void find_maximum();


        friend ostream& operator << (ostream &, RBTree &);
};

RBNode* RBTree::get_head()
{
    return head;
}

ostream& operator << (ostream &output, RBTree &tree)
{
    if(tree.head == NULL)
        output<<"The tree is empty.\n";
    else
        tree.show_tree();
    return output;
}

void RBTree::find_maximum()
{
    RBNode *temp = head;

    if (temp == NULL)
        cout<<"Nu exista noduri in arbore.\n";
    else
    {
        while (temp->dr != NULL)
        temp = temp->dr;
        cout<<"Valoarea maxima este "<<temp->info<<".\n";
    }
}

void RBTree::find_minimum()
{
    RBNode *temp = head;

    if (temp == NULL)
        cout<<"Nu exista noduri in arbore.\n";
    else
    {
        while (temp->st != NULL)
            temp = temp->st;
        cout<<"Valoarea minima este "<<temp->info<<".\n";
    }
}

void RBTree::show_tree()
{
    print_tree(head);
}

void RBTree::search_node(int a)
{
    RBNode *searchValue = search_node(head, a);

    if (searchValue == NULL)
        cout<<"Valoarea "<<a<<" nu exista in arbore.\n";
    else
        cout<<"Valoarea "<<a<<" exista in arbore.\n";

}

void RBTree::insert_node(int info)
{
    RBNode *pt = new RBNode(info);

    head = insert_node(head, pt);

    fix_violation(head, pt);
}

RBNode* RBTree::insert_node(RBNode* head, RBNode *pt)
{
    /* If the tree is empty, return a new RBNode */
    if (head == NULL)
        return pt;

    /* Otherwise, recur down the tree */
    if (pt->info < head->info)
    {
        head->st  = insert_node(head->st, pt);
        head->st->p = head;
    }
    else if (pt->info > head->info)
    {
        head->dr = insert_node(head->dr, pt);
        head->dr->p = head;
    }

    /* return the (unchanged) RBNode pointer */
    return head;
}

void RBTree::rotate_left(RBNode *&head, RBNode *&pt)
{
    RBNode *pt_dr = pt->dr;

    pt->dr = pt_dr->st;

    if (pt->dr != NULL)
        pt->dr->p = pt;

    pt_dr->p = pt->p;

    if (pt->p == NULL)
        head = pt_dr;

    else if (pt == pt->p->st)
        pt->p->st = pt_dr;

    else
        pt->p->dr = pt_dr;

    pt_dr->st = pt;
    pt->p = pt_dr;
}

void RBTree::rotate_right(RBNode *&head, RBNode *&pt)
{
    RBNode *pt_st = pt->st;

    pt->st = pt_st->dr;

    if (pt->st != NULL)
        pt->st->p = pt;

    pt_st->p = pt->p;

    if (pt->p == NULL)
        head = pt_st;

    else if (pt == pt->p->st)
        pt->p->st = pt_st;

    else
        pt->p->dr = pt_st;

    pt_st->dr = pt;
    pt->p = pt_st;
}

bool RBTree::get_color(RBNode *temp)
{
        if (temp == NULL)
            return false;
        else
            return temp->get_color();
}

void RBTree::set_color(RBNode *temp, bool color)
{
    if (temp == NULL)
        return;
    else
        temp->set_color(color);
}

void RBTree::print_tree(RBNode *head)
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


void RBTree::fix_violation(RBNode *&head, RBNode *&pt)
{
    RBNode *p_pt = NULL;
    RBNode *grand_p_pt = NULL;

    while ((pt != head) && (pt->color != false) && (pt->p->color == true))
    {

        p_pt = pt->p;
        grand_p_pt = pt->p->p;

        /*  Case : A
        p of pt is st child of Grand-p of pt */
        if (p_pt == grand_p_pt->st)
        {

            RBNode *uncle_pt = grand_p_pt->dr;

            /* Case : 1
            The uncle of pt is also true
            Only Recoloring requitrue */
            if (uncle_pt != NULL && uncle_pt->color == true)
            {
                grand_p_pt->color = true;
                p_pt->color = false;
                uncle_pt->color = false;
                pt = grand_p_pt;
            }
            else
            {
                /* Case : 2
                pt is dr child of its p
                st-rotation requitrue */
                if (pt == p_pt->dr)
                {
                    rotate_left(head, p_pt);
                    pt = p_pt;
                    p_pt = pt->p;
                }

                /* Case : 3
                pt is st child of its p
                dr-rotation requitrue */
                rotate_right(head, grand_p_pt);
                swap(p_pt->color, grand_p_pt->color);
                pt = p_pt;
            }
        }

        /* Case : B
        p of pt is dr child of Grand-p of pt */
        else
        {
            RBNode *uncle_pt = grand_p_pt->st;

            /*  Case : 1
            The uncle of pt is also true
            Only Recoloring requitrue */
            if ((uncle_pt != NULL) && (uncle_pt->color == true))
            {
                grand_p_pt->color = true;
                p_pt->color = false;
                uncle_pt->color = false;
                pt = grand_p_pt;
            }
            else
            {
                /* Case : 2
                pt is st child of its p
                dr-rotation requitrue */
                if (pt == p_pt->st)
                {
                    rotate_right(head, p_pt);
                    pt = p_pt;
                    p_pt = pt->p;
                }

                /* Case : 3
                pt is dr child of its p
                st-rotation requitrue */
                rotate_left(head, grand_p_pt);
                swap(p_pt->color, grand_p_pt->color);
                pt = p_pt;
            }
        }
    }

    head->color = false;
}

RBNode* RBTree::search_node(RBNode *temp, int info)
{
    if (temp == NULL)
        return NULL;

    if (temp->info == info)
        return temp;

    if (temp->info > info)
    {
        RBNode *leftValue = search_node(temp->st, info);

        if (leftValue != NULL)
            return leftValue;
    }

    if (temp->info < info)
    {
        RBNode *rightValue = search_node(temp->dr, info);

        if (rightValue != NULL)
            return rightValue;
    }

    return NULL;
}
#endif // RBTREES_H_INCLUDED
