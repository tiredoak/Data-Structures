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
