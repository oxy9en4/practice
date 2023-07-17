#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
int k = 2;

//asdsadsadsdsadsadsdasad
int main() {
    vector<pair<int, int>> vp;
    vector<int> nums = { 1, 1, 1, 2, 2, 3 };
    unordered_map<int, int> umap;
    // 비교 함수 정의
    for (auto a : nums) {
        umap[a]++;
    }
    for (auto a : umap) {
        vp.push_back({ a.second, a.first});
    }
    sort(vp.rbegin(), vp.rend());
    vector<int> ans;
    
    for (int i = 0; i < k; i++) {
        ans.push_back(vp[i].second);
    }

    return ans;
}