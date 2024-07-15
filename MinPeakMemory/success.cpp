#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> generatePermutations(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    
    // Base case: If the vector is empty, return an empty permutation
    if (n == 0) {
        result.push_back({});
        return result;
    }
    
    // Dynamic programming to generate permutations
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1));
    dp[0][0] = {{}};
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0) {
                dp[i][j] = {{}};
            } else if (j == 1) {
                dp[i][j] = {{nums[i - 1]}};
            } else {
                for (const auto& perm : dp[i - 1][j - 1]) {
                    for (int k = 0; k <= perm.size(); ++k) {
                        vector<int> new_perm = perm; // Corrected this line
                        new_perm.insert(new_perm.begin() + k, nums[i - 1]);
                        dp[i][j].push_back(new_perm);
                    }
                }
            }
        }
    }
    
    // Concatenate all permutations
    for (int i = 0; i <= n; ++i) {
        for (const auto& perm : dp[n][i]) {
            result.push_back(perm);
        }
    }
    
    return result;
}

int main() {
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> permutations = generatePermutations(nums);
    
    // Print all permutations
    for (const auto& perm : permutations) {
        for (int num : perm) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    return 0;
}
