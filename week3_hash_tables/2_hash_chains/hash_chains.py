# python3

class Query:

    def __init__(self, query):
        self.type = query[0]
        if self.type == 'check':
            self.ind = int(query[1])
        else:
            self.s = query[1]

class Node:
    def __init__(self,string,prev=None,next=None):
        self.string = string
        self.prev = prev
        self.next = next

class Chain:
    
    def __init__(self):
        self.head = None
    
    
    def find(self,string):
        it = self.head
        while(it != None):
            if (it.string == string): break
            it = it.next
        return it
        
    
    def add(self,string):
        it = self.find(string)
        if (it!=None): return
        
        newnode = Node(string,None,self.head)
        if self.head:
            self.head.prev = newnode
        self.head = newnode
        
    
    def delete(self,string):
        it = self.find(string)
        if(it != None):
            if (it == self.head):
                self.head = it.next
            else:
                it.prev.next = it.next
            if (it.next !=None):
                it.next.prev = it.prev
    


class QueryProcessor:
    _multiplier = 263
    _prime = 1000000007

    def __init__(self, bucket_count, file=None):
        self.bucket_count = bucket_count
        # store all strings in one list
        self.elems = list(Chain() for _ in range(self.bucket_count))
        self.infile = file

    def _hash_func(self, s):
        ans = 0
        for c in reversed(s):
            ans = (ans * self._multiplier + ord(c)) % self._prime
        return ans % self.bucket_count

    def write_search_result(self, was_found):
        print('yes' if was_found else 'no')

    def write_chain(self, chain):
        print(' '.join(chain))

    def read_query(self):
        return Query(input().split())
        #return Query(self.infile.readline().split())

    def process_query(self, query):
        if query.type == "check":
            words = []
            it = self.elems[query.ind].head
            while (it!=None):
                words.append(it.string)
                it = it.next
            self.write_chain(words)
            
        else:
            ind = self._hash_func(query.s)
            if query.type == 'find':
                self.write_search_result(self.elems[ind].find(query.s) != None)
            elif query.type == 'add':
                    self.elems[ind].add(query.s)
            else:
                self.elems[ind].delete(query.s)


    def process_queries(self):
        n = int(input())
        #n = int(self.infile.readline())
        for i in range(n):
            self.process_query(self.read_query())

if __name__ == '__main__':
    #cmds = open('/Users/rajgopalan/data_sc_sample_projects/data_structures/week3_hash_tables/2_hash_chains/tests/06','r')
    #line = cmds.readline()
    #bucket_count = int(line)
    bucket_count = int(input())
    proc = QueryProcessor(bucket_count)
    proc.process_queries()
    #cmds.close()