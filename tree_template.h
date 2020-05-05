#ifndef TREE_TEMPLATE_H_INCLUDED
#define TREE_TEMPLATE_H_INCLUDED

using namespace std;

///Arbore(int nr_noduri) – clasa abstracta
class tree_template{

protected:
    int numberOfNodes;

public:

    tree_template(int nodeNumber)
    {
        numberOfNodes = nodeNumber;
    }

    void set_node_number(int nodeNumber)
    {
        numberOfNodes = nodeNumber;
    }

    int get_node_number()
    {
        return numberOfNodes;
    }

    friend istream& operator >> (istream &, tree_template&);
    friend ostream& operator << (ostream &, tree_template&);

    virtual void show_tree() = 0;

    virtual void insert_node(int) = 0;
    virtual void delete_node(int) = 0;
    virtual void search_node(int) = 0;

    virtual void find_minimum() = 0;
    virtual void find_maximum() = 0;
};


istream& operator >> (istream &input, tree_template &tree) {

    for(int i = 0; i < tree.numberOfNodes; i++)
    {
        int a; input>>a;
        tree.insert_node(a);
    }
	return input;
}

ostream& operator << (ostream &output, tree_template &tree)
{
    tree.show_tree();
    return output;
}


#endif // TREE_TEMPLATE_H_INCLUDED
