#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>

using namespace std;

int min_MEM = 100000;

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

void printMapI2I(const map<int, int>& myMap) {
    for (const auto& entry : myMap) {
        cout << "Key: " << std::bitset<sizeof(entry.first) * 8>(entry.first) << endl;
        cout << "Value:" << entry.second << endl;
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

void printvector(const vector<int>& vec) {
    for(auto j:vec){
        cout << j << " ";
    }
    cout << endl;
}

void unionVectorsOfVectors(vector<vector<int>>& existingVector, const vector<vector<int>>& newVector) {
    // Reserve space in the existing vector to avoid frequent reallocations
    existingVector.reserve(existingVector.size() + newVector.size());
    
    // Insert all elements from the new vector into the existing vector
    existingVector.insert(existingVector.end(), newVector.begin(), newVector.end());
}

vector<vector<int>> orderVectorOfVectors(const vector<vector<int>>& vecOfVec, const vector<int>& order) {
    vector<vector<int>> orderedVecOfVec(vecOfVec.size());
    for (size_t i = 0; i < order.size(); ++i) {
        orderedVecOfVec[i] = vecOfVec[order[i]];
    }
    return orderedVecOfVec;
}

bool checkorder(const vector<int> &order,const vector<vector<int>> &mem){
    for(int i=0;i<order.size()-1;i++){
        for(int j=i+1;j<order.size();j++){
            // if(i==j) continue;
            if(order[j] < order[i] && mem[order[j]][order[i]] != 0){
                return false;
            }
        }
    }
    return true;
}

int peakmem(const vector<vector<int>> &m,const vector<int> &order){
    int n = order.size();
    int max = -1;
    vector<vector<int>> mem = orderVectorOfVectors(m,order);
    for(int k=0;k<n;k++){
        // int k = order[kk];
        int sum=mem[k][order[k]];

        for(int i=0; i<k; i++){
            // int i = order[ii];
            sum += mem[i][order[k]];
        }

        for(int i=k+1; i<order.size(); i++){
            // int i = order[ii];
            sum += mem[k][order[i]];
        }

        for(int i=0; i<k; i++){
            for(int j=k+1; j<order.size(); j++){
                // int j = order[j];
                // int i = order[i];
                sum += mem[i][order[j]];
            }
        }

        max = std::max(max, sum);
    }
    return max;
}

int memreq(const vector<vector<int>> &mem,const vector<int> &order,int k){
    int n = order.size();
    int max = -1;
    // vector<vector<int>> mem = orderVectorOfVectors(m,order);
    // printvector(order);
    // cout << "<><><> \n";

    int sum=mem[order[k]][order[k]];

    for(int i=0; i<k; i++){
        // int i = order[ii];
        sum += mem[order[i]][order[k]];
    }

    for(int i=k+1; i<order.size(); i++){
        // int i = order[ii];
        sum += mem[order[k]][order[i]];
    }

    for(int i=0; i<k; i++){
        for(int j=k+1; j<order.size(); j++){
            // int j = order[j];
            // int i = order[i];
            sum += mem[order[i]][order[j]];
        }
    }

    return sum;
}

// int compute_max(int maxmem, vector<int> perm, vector<int> subset, int index, const vector<vector<int>> &mem){
//     int peak_mem = mem[subset[index]][subset[index]];
//     for(auto j:perm){

//     }
// }

int recfunc(const vector<int> &elements, int subs, vector<int> &perm, map<int,int> &dp, const vector<vector<int>> &mem){
    int n = elements.size();
    // int min_peak_mem = 100000;

    if(dp.find(subs) != dp.end()){
        return dp[subs];
    }

    // vector<vector<int>> temp;

    if(perm.size() == n){
        // if (checkorder(perm,mem)){
        //     temp.push_back(perm);
        //     min_MEM = std::min(min_MEM,peakmem(mem,perm));
        // }
        dp[subs] = -1;
        return -1;
    }

    vector<int> the_subset;
    int curmin = 100000;
    for (int i=0; i < n; i++){
        if((subs & (1<<i))){
            the_subset.push_back(elements[n-1-i]);
        }
    }
    // printvector(the_subset);

    for(int i=0;i<the_subset.size();i++){
        bool flag=true; // indicate whether current element can be push_backed into perm
        for(int j=i+1;j<the_subset.size();j++){ // checking dependency
            if( i!=j && !(mem[the_subset[i]][the_subset[j]] == 0 && mem[the_subset[j]][the_subset[i]] == 0) ){
                flag = false;
                // cout<<"i:"<<i<<"   j:"<<j<<endl;
                // cout<<"sub i:"<<the_subset[i]<<"   sub j:"<<the_subset[j]<<"\n"<<endl;
                break;
            }
        }
        if(flag){
            vector<int> order;
            order = perm;
            order.push_back(the_subset[i]);
            int index = order.size() -1;
            for(int k=0;k<the_subset.size();k++){
                if(k!=i){
                    order.push_back(the_subset[k]);
                }
            }
            int curmax = memreq(mem,order,index);
            perm.push_back(the_subset[i]);
            // cout<<"curr subset"<<subs<<"   sub i:"<<the_subset[i]<<"   next subset"<<subs-(1<<(elements.size()-the_subset[i]-1))<<"\n"<<endl;
            curmax = max(curmax,recfunc(elements,subs-(1<<(elements.size()-the_subset[i]-1)),perm,dp,mem));
            perm.pop_back();
            curmin = min(curmin,curmax);
        }
    }
    // cout<<"whatever"<<endl;
    dp[subs] = curmin;
    // if (subs == 4){
    //     printvector(perm);
    // }
    return curmin;

    // for (int i=0; i < n; i++){
    //     if((subs & (1<<i))){
    //         perm.push_back(elements[n-1-i]);
    //         int subs2 = subs - (1<<i);
    //         unionVectorsOfVectors(temp,recfunc(elements,subs2,perm,dp,mem));
    //         perm.pop_back();
    //     }
    // }

    // dp[subs] = temp;

    // return temp;
    
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

int myfunc(const vector<int> &elements, const vector<vector<int>> &mem){
    int result;
    map<int, int> dp; // for a given subset to max peak mem
    int subs = (1 << elements.size()) - 1;
    // cout<<"---"<<subs<<"---"<<endl; //dummy
    vector<int> perm;
    result = recfunc(elements, subs, perm,dp,mem);
    // printMapI2I(dp);
    return result;
    // return;
}

int main() {
    int n;
    // vector<vector<int>> permutations = myfunc(nums);

    cin >> n;
    // vector<vector<int>> orders;
    vector<int> el_list; // element list
    for(int i=0;i<n;i++){
        el_list.push_back(i);
    }

    vector<vector<int>> mem;
	vector<int> temp_vec;
    int a;

	for(int i=0; i<n; i++){
        temp_vec.clear();
		for(int j=0; j<n; j++){
			cin >> a;
            temp_vec.push_back(a);
			// mem[i][j] = a;
			// totsum += a;
            // rowsums[i] += a;
            // colsums[j] += a;
		}
        mem.push_back(temp_vec);
	}
    temp_vec.clear();

    // printVectorOfVectors(myfunc(el_list,mem));
    int ers = myfunc(el_list,mem);

    cout << ers << endl;

    return 0;
}
