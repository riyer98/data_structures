#include<vector>
#include<iostream>

struct treenode{
int key;
int height;
treenode *parent, *left, *right;

treenode():
height(1),parent(nullptr), left(nullptr), right(nullptr){}

treenode(int keyval): 
key(keyval),height(1),parent(nullptr), left(nullptr), right(nullptr){}

};


class BST{
    void updateheight(treenode * &N);
    void rebalance(treenode * &N);
    int nodeheight(treenode* &N);
    void rotateleft(treenode* &N);
    void rotateright(treenode* &N);

    public:
    treenode * root;
    BST(): root(nullptr){}
    BST(std::vector<int>);

    bool find(int key, treenode* &R);
    treenode* next(treenode* &N);
    treenode* leftdes(treenode* &N);
    treenode* rightanc(treenode* &N);
    std::vector<treenode* > rangesearch(int min,int max);
    void insert(int key);
    void remove(int key);
    int height(int key);

};