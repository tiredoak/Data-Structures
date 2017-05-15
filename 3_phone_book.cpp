/*
    Implements a phone book using a direct addressing scheme.

    Input: single integer N in the first line - the number of
           queries. It's followed by N lines each of them 
           containing a query in the specified format.
           1 <= N <= 10^5
    Output: prints the result of each find query.
*/

#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<string> contacts(10000000);
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            contacts[queries[i].number] = queries[i].name;
        } else if (queries[i].type == "del") {
            contacts[queries[i].number] = "";
        } else {
            string response = "not found";
            if (contacts[queries[i].number] == "") {
            	result.push_back(response);
            } else {
            	result.push_back(contacts[queries[i].number]);
            }
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
