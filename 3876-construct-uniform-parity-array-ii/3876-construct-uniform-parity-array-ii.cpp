class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());
        // Find min because it has no smaller element to subtract,
        // and for other elements, subtracting min gives result >= 1 (if
        // larger).

        if (mn % 2 != 0) {
            return true; // cause we can make other elements odd:
                         // odd → keep it, even - odd = odd
        }

        // Now we are checking whether the array is a combination of
        // odd + even or only even. If odd comes, we can't make it even,
        // because the smallest odd element has no smaller odd element to
        // subtract.

        for (int val : nums1) {
            if (val % 2 != 0) {
                return false;
            }
        }

        // If no odd element means the whole array is even, so true.
        return true;
    }
};