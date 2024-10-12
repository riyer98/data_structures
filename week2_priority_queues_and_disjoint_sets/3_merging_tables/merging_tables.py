# python3


class Database:
    def __init__(self, row_counts):
        self.row_counts = row_counts
        self.max_row_count = max(row_counts)
        n_tables = len(row_counts)
        self.ranks = [1] * n_tables
        self.parents = list(range(n_tables))

    def merge(self, src, dst):
        src_parent = self.get_parent(src)
        dst_parent = self.get_parent(dst)

        if src_parent == dst_parent:
            return False

        # merge two components
        # use union by rank heuristic
        # update max_row_count with the new maximum table size
        path=[]
        while(dst_parent!=dst):
            path.append(dst)
            dst = dst_parent
            dst_parent = self.get_parent(dst_parent)
        
        while(len(path)>0):
            self.parents[path.pop()]=dst
        
        while(src_parent!=src):
            self.parents[src]=dst
            src = src_parent
            src_parent = self.get_parent(src_parent)
        
        self.row_counts[dst]+=self.row_counts[src]
        self.row_counts[src]=0
        self.parents[src]=dst
        self.max_row_count = max(self.max_row_count,self.row_counts[dst])

        return True

    def get_parent(self, table):
        # find parent and compress path
        return self.parents[table]


def main():
    n_tables, n_queries = map(int, input().split())
    #data = open("tests/116","r")
    #n_tables, n_queries = map(int, data.readline().split())
    counts = list(map(int, input().split()))
    #counts = list (map(int, data.readline().split()))
    assert len(counts) == n_tables
    db = Database(counts)
    for i in range(n_queries):
        dst, src = map(int, input().split())
        #dst, src = map(int, data.readline().split())
        db.merge(dst - 1, src - 1)
        print(db.max_row_count)
    
    #data.close()


if __name__ == "__main__":
    main()
