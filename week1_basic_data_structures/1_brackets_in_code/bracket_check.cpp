#include<iostream>
#include<string>
//#include<ctime>
#include<fstream>

struct node{
    char data;
    node *next;
    int position;

    node(char character, node* next, int position):
    data(character), next(next), position(position){};
};

struct charstack{
    node * head;

    charstack(): head(nullptr){};

    bool empty(){
        return (head==nullptr);
    }

    void push_back(char character, int bracposition){
        node * newnode = new node(character,head,bracposition);
        head = newnode;
    }

    char pop(){
        if (head==nullptr){
            return '\0';
        }
        char popout = head->data;
        head = head->next;
        return popout;
    }

    int openposition(){return head->position;}
};

int main(int argc, char** argv){
    std::string text;

    if(argc==2){
    std::ifstream strfile(argv[1]);
    std::getline(strfile,text);
    strfile.close();
    }
    else{
    std::cout<<"Enter input string: ";
    std::cin>>text;
    }
    
    //clock_t start =clock();

    charstack brackets; int strposition=1; char bractype;

    for (char c: text){
        switch(c){
            case '(': case '{': case '[':
            brackets.push_back(c,strposition);
            break;

            case ')':
            bractype = brackets.pop();
            if (bractype!='(') {
                std::cout<<strposition<<std::endl;
                //std::cout<<"Time elapsed: "<<(float)(clock()-start)/1000000<<" s\n";
                return 0;
            }
            break;

            case '}':
            bractype = brackets.pop();
            if (bractype!='{') {
                std::cout<<strposition<<std::endl;
                //std::cout<<"Time elapsed: "<<(float)(clock()-start)/1000000<<" s\n";
                return 0;
            }
            break;

            case ']':
            bractype = brackets.pop();
            if (bractype!='[') {
                std::cout<<strposition<<std::endl;
                //std::cout<<"Time elapsed: "<<(float)(clock()-start)/1000000<<" s\n";
                return 0;
            }
            break;

            default: break;
        }
        ++strposition;
    }
    if (brackets.empty()) std::cout<<"Success\n";
    else std::cout<<brackets.openposition()<<std::endl;
    //std::cout<<"Time elapsed: "<<(float)(clock()-start)/1000000<<" s\n";

    return 0;
}