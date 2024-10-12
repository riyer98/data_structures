#include <algorithm>
#include <iostream>
#include <vector>
#include<queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;
    int depth;

    Node() {
      this->parent = NULL;
      this->depth = 0;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
  int parentindex, maxHeight=0;

  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0; 
    std::queue<int> path;

    for (Node *v = &nodes[leaf_index]; v->parent != NULL; v = v->parent){
      path.push(v->key);
      parentindex = v->parent->key;
      height++;
    }
    while(!path.empty()){
      nodes[path.front()].depth = height + nodes[parentindex].depth;
      nodes[path.front()].parent = NULL;
      path.pop();
      height--;
    }
  }
  for (int i=0;i<n;i++){
    maxHeight = std::max(maxHeight,nodes[i].depth);
  }
  std::cout << 1+maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
