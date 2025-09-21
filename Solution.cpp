#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> donquarist = nums1; // storing the input midway as required
        
        auto vecToStr = [&](const vector<int>& v) -> string {
            stringstream ss;
            for (int num : v) {
                ss << num << ",";
            }
            return ss.str();
        };

        string target = vecToStr(nums2);
        if(vecToStr(nums1) == target) return 0;
        
        queue<pair<vector<int>, int>> q;
        unordered_set<string> seen;
        q.push({nums1, 0});
        seen.insert(vecToStr(nums1));
    
        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            vector<int> cur = front.first;
            int steps = front.second;
            
            for(int L = 0; L < n; L++){
                for(int R = L; R < n; R++){
                    vector<int> sub(cur.begin() + L, cur.begin() + R + 1);
                    vector<int> rem;
                    for(int i = 0; i < L; i++) rem.push_back(cur[i]);
                    for(int i = R + 1; i < n; i++) rem.push_back(cur[i]);
                    int m = rem.size();
                    for(int pos = 0; pos <= m; pos++){
                        vector<int> next;
                        next.insert(next.end(), rem.begin(), rem.begin() + pos);
                        next.insert(next.end(), sub.begin(), sub.end());
                        next.insert(next.end(), rem.begin() + pos, rem.end());
                        if(next == cur) continue;
                        string key = vecToStr(next);
                        if(seen.find(key) != seen.end()) continue;
                        if(key == target) return steps + 1;
                        seen.insert(key);
                        q.push({next, steps + 1});
                    }
                }
            }
        }
        return -1;
    }
};

// The below main() function is for local testing and can be removed on LeetCode.
#ifdef LOCAL
#include <iostream>
int main(){
    Solution sol;
    vector<int> nums1 = {1,1,2,3,4,5};
    vector<int> nums2 = {5,4,3,2,1,1};
    cout << sol.minSplitMerge(nums1, nums2) << endl;  // Expected output: 3
    return 0;
}
#endif
