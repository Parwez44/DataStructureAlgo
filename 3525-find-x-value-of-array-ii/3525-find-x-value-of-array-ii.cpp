class Solution {
    struct Node {
        int prod = 1;
        int cnt[5] = {};
    };

    int k;
    vector<Node> tree;

    Node merge(const Node& a, const Node& b) {
        Node res;
        res.prod = a.prod * b.prod % k;

        for (int i = 0; i < k; i++)
            res.cnt[i] = a.cnt[i];

        for (int i = 0; i < k; i++)
            res.cnt[a.prod * i % k] += b.cnt[i];

        return res;
    }

    void build(int node, int l, int r, const vector<int>& nums) {
        if (l == r) {
            int x = nums[l] % k;
            tree[node].prod = x;
            tree[node].cnt[x] = 1;
            return;
        }

        int mid = (l + r) >> 1;

        build(node << 1, l, mid, nums);
        build(node << 1 | 1, mid + 1, r, nums);

        Node res = merge(tree[node << 1], tree[node << 1 | 1]);
        tree[node].prod = res.prod;

        for (int i = 0; i < k; i++)
            tree[node].cnt[i] = res.cnt[i];
    }

    void update(int node, int l, int r, int pos, int val) {
        if (l == r) {
            val %= k;
            tree[node].prod = val;

            for (int i = 0; i < k; i++)
                tree[node].cnt[i] = 0;

            tree[node].cnt[val] = 1;
            return;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid)
            update(node << 1, l, mid, pos, val);
        else
            update(node << 1 | 1, mid + 1, r, pos, val);

        Node res = merge(tree[node << 1], tree[node << 1 | 1]);
        tree[node].prod = res.prod;

        for (int i = 0; i < k; i++)
            tree[node].cnt[i] = res.cnt[i];
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) >> 1;

        if (qr <= mid)
            return query(node << 1, l, mid, ql, qr);

        if (ql > mid)
            return query(node << 1 | 1, mid + 1, r, ql, qr);

        Node left = query(node << 1, l, mid, ql, qr);
        Node right = query(node << 1 | 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();
        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            update(1, 0, n - 1, q[0], q[1]);

            Node res = query(1, 0, n - 1, q[2], n - 1);

            ans.push_back(res.cnt[q[3]]);
        }

        return ans;
    }
};