#python3
import sys

class StackWithMax():
    def __init__(self):
        self.__stack = []
        self.aux = []

    def Push(self, a):
        self.__stack.append(a)
        if (len(self.aux)==0 or self.aux[-1]<=a):
            self.aux.append(a)

    def Pop(self):
        assert(len(self.__stack))
        if (self.__stack.pop() == self.aux[-1]):
            self.aux.pop()

    def Max(self):
        return self.aux[-1]


if __name__ == '__main__':
    stack = StackWithMax()

    num_queries = int(sys.stdin.readline())
    for _ in range(num_queries):
        query = sys.stdin.readline().split()

        if query[0] == "push":
            stack.Push(int(query[1]))
        elif query[0] == "pop":
            stack.Pop()
        elif query[0] == "max":
            print(stack.Max())
        else:
            assert(0)
