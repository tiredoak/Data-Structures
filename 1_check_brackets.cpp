/*
	Reviews an input text to establish if it uses brackets
	correctly. 
	Input is scanned, adding all brackets in the text to a stack
	for easy identification of possible mistmatches.

	Input: one string S which consists of big and small latin
		   letters, digits and punctuation marks
	Output: "Success" if brackets are used correctly and if not
			output 1-based index of the first unmatched closing
			bracket. If there are no unmatched closing brakets,
			output the 1-based index of the first unmatched 
			opening bracket
*/

#include <iostream>
#include <stack>
#include <string>

struct Bracket {
	Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
	
    std::string text;
    getline(std::cin, text);
    
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        // Add opening brackets to stack
        if (next == '(' || next == '[' || next == '{') {
			Bracket temp(next, position + 1);
            opening_brackets_stack.push(temp);
        }
        // Check if there is a matching closing bracket
        if (next == ')' || next == ']' || next == '}') {
            // Nothing has been added yet
            if (opening_brackets_stack.empty()) {
            	std::cout << position + 1 << std::endl;
            	return position + 1;
            }

            Bracket temp = opening_brackets_stack.top();
            if (temp.Matchc(next)) {
            	// Remove bracket from stack
            	opening_brackets_stack.pop();
            } else {
            	std::cout << position + 1 << std::endl;
            	return position + 1;
            }
        }
    }
    bool result = opening_brackets_stack.empty();
    if (result) {
    	std::cout << "Success" << std::endl;
    } else {
    	std::cout << opening_brackets_stack.top().position << std::endl;
    }
}
