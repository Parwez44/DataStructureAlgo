class Solution {
public:
    string reverseParentheses(string s) {
        string ans;

        for (char c : s) {
            if (c == '(') {
                ans.push_back(c);
            } else if (c == ')') {
                string temp;

                while (ans.back() != '(') {
                    temp += ans.back();
                    ans.pop_back();
                }

                ans.pop_back();

                for (char x : temp)
                    ans.push_back(x);
            } else {
                ans.push_back(c);
            }
        }

        return ans;
    }
};