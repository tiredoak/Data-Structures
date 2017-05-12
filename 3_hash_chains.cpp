#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
private:    
    int bucket_count;
    // store all strings in one vector
    vector<vector<string> > hash_table;
    // Hash function
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
	QueryProcessor(int count)
    : bucket_count(count),
      hash_table(bucket_count, vector<string>(1, ""))
	{
	}
    /*
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
    	for (int i = 0; i < bucket_count; i++) {
    		vector<string> v_string(1);
    		hash_table.push_back(v_string);
    	}
    }
    */

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
        int hash = hash_func(query.s);
        if (query.type == "check") {
        	for (int i = 0; i < hash_table[query.ind].size(); i++) {
        		std::cout << hash_table[query.ind][i] << " ";
        	}
        	std::cout << std::endl;
        	return;
        } else {
            if (query.type == "find") {
            	for (int i = 0; i < hash_table[hash].size(); i++) {
            		if (hash_table[hash][i] == query.s) {
            			std::cout << "yes" << std::endl;
            			return;
            		}
            	}
            	std::cout << "no" << std::endl;
            	return;
        	} else if (query.type == "add") {
                // Check if string already in table
                for (int i = 0; i < hash_table[hash].size(); i++) {
            		if (hash_table[hash][i] == query.s) {
            			return;
            		}
            	}
            	// Add to table
            	hash_table[hash].insert(hash_table[hash].begin(), query.s);
            } else if (query.type == "del") {
                std::vector<string>::iterator new_end = std::remove(hash_table[hash].begin(), hash_table[hash].end(), query.s);
                hash_table[hash].erase(new_end, hash_table[hash].end());
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
    std::cout << std::endl;
    proc.processQueries();
    return 0;
}
