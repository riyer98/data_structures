#include "bst.h"
#include<string>

using std::cout;
using std::cin;
using std::string;
using std::vector;

int main(){
    
    int i,n_ops, key, max;
    string instr;
    treenode *null = nullptr;
    BST tree;
    
    cout<<"Enter number of Ops: ";
    cin>>n_ops;

    for(i=0; i<n_ops; i++){
        cin>>instr>>key;
        if(instr == "add") tree.insert(key);
        else if (instr == "del") tree.remove(key);
        else if(instr == "find") {
            if(tree.find(key,null)) cout<<"True\n";
            else cout<<"False\n";
        }
        else if(instr == "height") cout<<tree.height(key)<<"\n";
        else if(instr == "range"){
            cin>>max;
            vector<treenode *> rangevals = tree.rangesearch(key,max);
            for (i=0;i<rangevals.size();i++) cout<<rangevals[i]->key<<" ";
            cout<<"\n";
        }
    }
    return 0;
}