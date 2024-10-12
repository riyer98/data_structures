#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<unordered_set>

using std::string;
using std::vector;
using std::cin;
using std::unordered_set;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;

    struct hash_func{
        int bucket_count;
        hash_func(): bucket_count(1000){}
        hash_func(int count): bucket_count(count){}

        const size_t operator()(const string & s) const {
            static const size_t multiplier = 263;
            static const size_t prime = 1000000007;
            unsigned long long hash = 0;
            for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
                hash = (hash * multiplier + s[i]) % prime;
            return (const size_t)(hash % bucket_count);
        }
    };

    unordered_set<string, hash_func> elems;

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {       
        elems = unordered_set<string, hash_func> (bucket_count,hash_func(bucket_count));
    }
    

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        
        if (query.type == "check") {
            for (auto it = elems.begin(query.ind); it!= elems.end(query.ind); it++)
                std::cout<< *it <<" ";
            std::cout << "\n";
        } 
        
        else {
            auto it = elems.find(query.s);
            
            if (query.type == "find"){
                writeSearchResult(it != elems.end());
            }
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.insert(query.s);
            } else if (query.type == "del") {
                elems.erase(query.s);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
