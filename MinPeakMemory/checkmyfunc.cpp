#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void printMapOfVectorOfVector(const map<int, vector<vector<int>>>& myMap) {
    for (const auto& entry : myMap) {
        cout << "Key: " << entry.first << endl;
        cout << "Value:" << endl;
        for (const auto& vec : entry.second) {
            cout << "    ";
            for (int num : vec) {
                cout << num << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void printVectorOfVectors(const vector<vector<int>>& vec) {
    for (const auto& innerVec : vec) {
        for (int num : innerVec) {
            cout << num << " ";
        }
        cout << endl;
    }
}

void unionVectorsOfVectors(vector<vector<int>>& existingVector, const vector<vector<int>>& newVector) {
    // Reserve space in the existing vector to avoid frequent reallocations
    existingVector.reserve(existingVector.size() + newVector.size());
    
    // Insert all elements from the new vector into the existing vector
    existingVector.insert(existingVector.end(), newVector.begin(), newVector.end());
}

vector<vector<int>> recfunc(const vector<int> &elements, int subs, vector<int> &perm, map<int, vector<vector<int>>> &dp){
    int n = elements.size();
    // int min_peak_mem = 100000;

    // vector<vector<int>> temp2;
    if(dp.find(subs) != dp.end()){
        // cout << "dp atleast used\n";
        // for(int i=0; i<dp[subs].size();i++){
        //     for (auto j:perm){
        //         cout << j << " ";
        //     }
        //     // temp2.push_back({perm[perm.size()-1]});
        //     for (auto j:dp[subs][i]){
        //         // temp2[i].push_back(j);
        //         cout << j << " ";
        //     }
        //     cout << endl;
        // }
        return dp[subs];
    }

    vector<vector<int>> temp;

    if(perm.size() == n){
        temp.push_back({});
        dp[subs] = temp;
        return temp;
    }

    vector<vector<int>> temp3;
    for (int i=0; i < n; i++){
        if((subs & (1<<i))){
            // temp3.push_back({elements[n-1-i]});
            perm.push_back(elements[n-1-i]);
            int subs2 = subs - (1<<i);
            temp3 = recfunc(elements,subs2,perm,dp);
            // if(temp3.size()==0){
            //     temp.push_back({elements[n-1-i]});
            // }
            // unionVectorsOfVectors(temp,recfunc(elements,subs2,perm,dp));          
            for(auto j:temp3){
                temp.push_back({elements[n-1-i]});
                for (auto k:j){
                    // temp2[i].push_back(j);
                    temp[temp.size()-1].push_back(k);
                }
            }            
            perm.pop_back();
        }
    }

    dp[subs] = temp;

    return temp;
    
    // if(dp.find(subs) != dp.end()){
    //     return dp[subs];
    // }

    // if(){

    // }

    // for (int mask = 1; mask < subs; ++mask) {
    //     // Check if the current mask is a subset of the given subset
    //     if ((mask | subs) == mask && (mask & subs) != 0) {
    //         // bool isFirst = true;
    //         // Iterate over each bit in the mask
    //         for (int i = 0; i <= subs; ++i) {
    //             if (mask & (1 << i)) {
    //                 elements[i];
    //             }
    //         }
    //     }
    // }
}

vector<vector<int>> myfunc(vector<int> &elements){
    vector<vector<int>> result;
    map<int, int> dp; // for a given subset to max peak mem
    int subs = (1 << elements.size()) - 1;
    // cout<<"---"<<subs<<"---"<<endl;//dummy
    vector<int> perm;
    result = recfunc(elements, subs, perm,dp);
    // printMapOfVectorOfVector(dp);
    printVectorOfVectors(result);
    return result;
    // return;
}

int main() {
    int n;
    // vector<vector<int>> permutations = myfunc(nums);

    cin >> n;
    vector<vector<int>> orders;
    vector<int> el_list; // element list
    for(int i=0;i<n;i++){
        el_list.push_back(i);
    }

    // printVectorOfVectors(myfunc(el_list,mem));
    myfunc(el_list);

    // cout << min_MEM << endl;

    return 0;
}
