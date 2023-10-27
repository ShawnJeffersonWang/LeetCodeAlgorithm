#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int> &nums) {
        int sum = 0;
        int start = 0;
        int subLength;
        int result = INT32_MAX;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            while (sum >= target) {
                subLength = i - start + 1;
                //bug 之前先sum-=nums[start++],导致start++后subLength算的不对
                sum -= nums[start++];
                result = subLength < result ? subLength : result;
            }
        }
        return result == INT32_MAX ? 0 : result;
    }
};