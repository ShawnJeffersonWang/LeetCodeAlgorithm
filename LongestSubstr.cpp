#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> set;
        int left = 0;
        int maxStr = 0;
        for (int i = 0; i < s.size(); i++) {
            while (set.find(s[i]) != set.end()) {
                set.erase(s[left]);
                left++;
            }
            maxStr = max(maxStr, i - left + 1);
            set.insert(s[i]);
        }
        return maxStr;
    }
};