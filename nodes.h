#ifndef NODES_H_INCLUDED
#define NODES_H_INCLUDED
using namespace std;

///Nod (int info, nod *st, nod *dr)
class node{
protected:
    int info;
    node *st, *dr;
public:

    node(int info)
    {
        this->info = info;
        this->st = NULL;
        this->dr = NULL;
    }

    void set_info(int info)
    {
        this->info = info;
    }

    void set_st(node *st)
    {
        this->st = st;
    }


    void set_dr(node *dr)
    {
        this->dr = dr;
    }

    int get_info()
    {
        return info;
    }

    node *get_st()
    {
        return st;
    }


    node *get_dr()
    {
        return dr;
    }

    friend ostream& operator <<(ostream& output, node &n)
    {
        output<<"Information: "<<n.info<<"\n";
        return output;
    }

    friend istream& operator >>(istream& input, node &n)
    {
        input>>n.info;
        return input;

    }

    friend class tree;
};

class RBNode{
protected:
    int info;
    bool color;
    RBNode *st, *dr, *p;
public:
    RBNode(int info)
    {
        this->color = true; ///initialized cu red
        this->info  = info;
        this->st = NULL;
        this->dr = NULL;
        this->p = NULL;
    }

    void set_info(int info)
    {
        this->info = info;
    }

    void set_color(bool color)
    {
        this->color = color;
    }

    void set_st(RBNode *st)
    {
        this->st = st;
    }

    void set_dr(RBNode *dr)
    {
        this->dr = dr;
    }

    void set_p(RBNode *p)
    {
        this->p = p;
    }

    int get_info()
    {
        return info;
    }

    bool get_color()
    {
        return color;
    }

    RBNode *get_st()
    {
        return st;
    }

    RBNode *get_dr()
    {
        return dr;
    }

    RBNode *get_p()
    {
        return p;
    }

    RBNode *getSibling()
    {
        if (p == NULL)
            return NULL;
        else
            if(p->st == this)
                return p->dr;
            else
                return p->st;
    }


    friend ostream& operator <<(ostream& output, RBNode &n)
    {
        if(n.color == 0)
            output<<"Color: black, data: "<<n.info<<"\n";
        else
            output<<"Color: red, data: "<<n.info<<"\n";

        return output;
    }

    friend istream& operator >>(istream& input, RBNode &n)
    {
        input>>n.info;
        return input;
    }

    friend class RBTree;
};

#endif // NODES_H_INCLUDED
