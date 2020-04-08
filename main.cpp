#include<iostream>
using namespace std;

///Nod (int info, nod*st, nod *dr)
///Nod_rosu_negru:Nod {char culoare[]};
///Arbore(int nr_noduri) – clasa abstracta
///ABC (Nod *rad):Arbore
///Arbore_bicolor (Nod_rosu_negru *rad) : Arbore


class node{
protected:
    int info;
    node *st, *dr;
public:
    node(int info, node *st = NULL, node *dr = NULL)
    {
        this->st = st;
        this->dr = dr;
        this->info = info;
    }

    void set_info(int info)
    {
        this->info = info;
    }

    int get_info()
    {
        return info;
    }

    void print()
    {
        cout<<info<<" "<<&st<<" "<<&dr<<"\n";
    }

    friend ostream& operator <<(ostream& output, node &n)
    {
        output<<"Information: "<<n.info;
        output<<"\n";
        return output;
    }

    friend istream& operator >>(istream& input, node &n)
    {
        input>>n.info;
        return input;

    }
};


class RBNode:public node{
private:
    bool color;
public:
    RBNode(bool color, int info, node *st, node *dr):node(info, st, dr)
    {
        this->color = color;
    }

    friend ostream& operator <<(ostream& output, RBNode &n)
    {
        if(n.color == 0)
            output<<"Color: black, data: "<<n.info;
        else
            output<<"Color: red, data: "<<n.info;

        output<<"\n";
        return output;
    }

};
int main()
{
    //node nod(13, NULL, NULL);
    //cout<<nod;

    ///nod.print();
    //node *nod = new node(0, NULL, NULL);
    //nod->print();
    RBNode n(0, 14, NULL, NULL);
    cout<<n;
    cin>>n;
    cout<<n;
}
