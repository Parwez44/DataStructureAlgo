class Solution {
    string s;
    int pos;

    set<string> parseExpression() {
        set<string> res = parseTerm();

        while (pos < s.size() && s[pos] == ',') {
            pos++;
            set<string> cur = parseTerm();
            res.insert(cur.begin(), cur.end());
        }

        return res;
    }

    set<string> parseTerm() {
        set<string> res = {""};

        while (pos < s.size() && s[pos] != '}' && s[pos] != ',') {
            set<string> cur;

            if (s[pos] == '{') {
                pos++;
                cur = parseExpression();
                pos++;
            } else {
                cur.insert(string(1, s[pos]));
                pos++;
            }

            set<string> next;

            for (const string& a : res)
                for (const string& b : cur)
                    next.insert(a + b);

            res = move(next);
        }

        return res;
    }

public:
    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        set<string> res = parseExpression();

        return vector<string>(res.begin(), res.end());
    }
};