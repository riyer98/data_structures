#include "bst.h"

using std::vector;
using std::cerr;
using std::cout;


BST::BST(std::vector<int> values){
    for (int n: values) insert(n);
}

int BST::height(int key){ 
    treenode* N = root;
    if(find(key,N)) return N->height; 
    else return 0;
}


bool BST::find(int key, treenode * &R){
    if(root == nullptr) {
        return false;
    }
    if (R==nullptr) R = root;

    while(true){
        if (R->key==key) {
            //cout<<R->key<<"\n";
            return true;
        }
        else if(R->key>key){
            if (R->left == nullptr) {
                //cout<<R->key<<"\n";
                return false;
            }
            else R = R->left;
        }
        else{
            if(R->right == nullptr) {
                //cout<<R->key<<"\n";
                return false;
            }
            else R=R->right;
        }   
    }
}


treenode* BST::leftdes(treenode* &N){
    if (N==nullptr){
        cerr<<"Error:Null pointer passed to BST::leftdes\n";
        exit(EXIT_FAILURE);
    } 
    if (N->left==nullptr) return N;
    else return leftdes(N->left);
}


treenode* BST::rightanc(treenode* &N){
    if (N==nullptr){
        cerr<<"Error:Null pointer passed to BST::rightanc\n";
        exit(EXIT_FAILURE);
    } 
    if(N->parent ==nullptr) return nullptr;
    else if (N->key < N->parent->key) return N->parent;
    else return rightanc(N->parent);
}


treenode* BST::next(treenode* &N){
    if (N==nullptr){
        cerr<<"Error:Null pointer passed to BST::next\n";
        exit(EXIT_FAILURE);
    } 
    if (N->right!=nullptr){
        return leftdes(N->right);
    }
    else{
        return rightanc(N);
    }
}


vector<treenode*> BST::rangesearch(int min,int max){
    if(root == nullptr) {
        cerr<<"Tree is empty.\n";
        exit(EXIT_FAILURE);
    }
    vector<treenode *> nodes{};
    treenode * N = root;
    find(min,N);
    while (N->key<=max){
        if (N->key>= min) nodes.push_back(N);
        N = next(N);
        if(N==nullptr) break;
    } 
    return nodes;
}


void BST::insert(int key){
    treenode* N = nullptr;
    if(find(key,N)){
        if (N->key==key) {
            cerr<<"Key already present.\n";
            return;
        }
    }
    treenode *newnode = new treenode(key);
    if (N==nullptr) root = newnode;
    else{  
        newnode->parent = N;
        if(N->key> key) N->left = newnode;
        else N->right = newnode;
        rebalance(N);
    }
}


void BST::remove(int key){
    treenode *P,*X, *N = root;
    
    if (!find(key,N)) return;

    if(N->right == nullptr) {
        X = N->left;
        P = N;
    }
    else {
        X = next(N);
        P = X->parent;
        if (P != N) {
            P->left = X->right;
            if (X->right!=nullptr) X->right->parent = P;
            X->right = N->right;
            N->right->parent = X;
        }
        X->left = N->left;
        if(N->left!=nullptr) N->left->parent = X;
    }
    if (X !=nullptr)  X->parent = N->parent;
    if(N==root) root = X;
    else{
        if (key < N->parent->key) N->parent->left = X;
        else N->parent->right = X;  
    }
    if(P==N) rebalance(X);
    else rebalance(P);
    free(N);
}


int BST::nodeheight(treenode* &N){
    if (N==nullptr) return 0;
    else return N->height;
}


void BST::updateheight(treenode* &N){
    if (N==nullptr) return;
    N->height = 1+std::max(nodeheight(N->left),nodeheight(N->right));
}


void BST::rebalance(treenode* &N){
    while(N!=nullptr){
        treenode *M;
        if(nodeheight(N->left)>nodeheight(N->right)+1){
            M = N->left;
            if (nodeheight(M->right)>nodeheight(M->left)) {
                rotateleft(M);
                updateheight(M);
                updateheight(M->parent);
            }
            rotateright(N);
        }
        else if(nodeheight(N->right)>nodeheight(N->left)+1){
            M=N->right;
            if (nodeheight(M->left)>nodeheight(M->right)){
                rotateright(M);
                updateheight(M);
                updateheight(M->parent);  
            } 
            rotateleft(N);
        }
        updateheight(N);
        N = N->parent;
    }
}


void BST::rotateleft(treenode* &N){
    if(N==nullptr){
        cerr<<"Error: Node is nullptr\n";
        exit(EXIT_FAILURE);
    }
    treenode * R = N->right;
    if (R == nullptr){
        cerr<<"Error: Node right is nullptr\n";
        return;
    }
    R->parent = N->parent;
    if(N==root) root = R;
    else{
        if(N->key < N->parent->key) N->parent->left = R;
        else N->parent->right = R;
    }
    N->right = R->left;
    if(R->left!=nullptr) R->left->parent = N;
    R->left = N;
    N->parent = R;
}


void BST::rotateright(treenode* &N){
    if(N==nullptr){
        cerr<<"Error: Node is nullptr\n";
        exit(EXIT_FAILURE);
    }
    treenode * L = N->left;
    if (L == nullptr){
        cerr<<"Error: Node right is nullptr\n";
        return;
    }
    L->parent = N->parent;
    if(N==root) root = L;
    else{
        if(N->key < N-> parent->key) N->parent->left = L;
        else N->parent->right =L;
    }
    N->left = L->right;
    if(L->right!=nullptr) L->right->parent = N;
    L->right = N;
    N->parent = L;
}