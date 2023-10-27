#include <string>
#include <stack>
#include<vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> st;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                int num1 = st.top();
                st.pop();
                int num2 = st.top();
                st.pop();
                if (tokens[i] == "+") {
                    st.push(num2 + num1);
                }
                if (tokens[i] == "-") {
                    st.push(num2 - num1);
                }
                if (tokens[i] == "*") {
                    st.push(num2 * num1);
                }
                if (tokens[i] == "/") {
                    st.push(num2 / num1);
                }
            } else {
                st.push(stoi(tokens[i]));
            }
        }
        int result = st.top();
        st.pop();
        return result;
    }
};

int main() {
    Solution sol;
    vector<string> tokens = {"4", "13", "5", "/", "+"};
    int res = sol.evalRPN(tokens);
    cout << "res: " << res << endl;
}