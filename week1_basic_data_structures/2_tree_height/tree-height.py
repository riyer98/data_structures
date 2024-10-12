# python3

import sys, threading
sys.setrecursionlimit(10**7) # max depth of recursion
threading.stack_size(2**27)  # new thread will get stack of such size

from collections import deque

class TreeHeight:
        def read(self):
                self.n = int(sys.stdin.readline())
                self.parent = list(map(int, sys.stdin.readline().split()))

        def compute_height(self):
                # Replace this code with a faster implementation
                nodedepths = dict([[i,0] for i in range(self.n)])
                
                for vertex in range(self.n):
                        height = 0
                        i = vertex
                        queue=deque()

                        while self.parent[i] != -1:
                                queue.append(i)
                                childindex=i
                                i = self.parent[i]
                                self.parent[childindex]=-1
                                height += 1
                        
                        while len(queue)>0:
                                nodedepths[queue.popleft()] = height + nodedepths[i]
                                height -= 1

                        
                return 1+max([nodedepths[i] for i in range(self.n)]);

def main():
  tree = TreeHeight()
  tree.read()
  print(tree.compute_height())

threading.Thread(target=main).start()
