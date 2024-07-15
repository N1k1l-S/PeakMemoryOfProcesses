#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <cstring> // for memset

void permutations(vector<int> &vec, int left, vector<vector<int>>& V){
    int last = vec.size();
    if(left == last){
        V.push_back(vec);
        return;
    }

    for(int i=left;i<last;i++){
        swap(vec[left],vec[i]);
        permutations(vec,left+1,V);
        swap(vec[left],vec[i]);
    }
}

void printvecofvec (vector<vector<int>>& V){
    for(int i=0; i<V.size(); i++){
        for(int j=0; j<V[i].size(); j++){
            cout << V[i][j] << " ";
        }
        cout << endl;
    }
}
 
int main(){
    vector<vector<int>> V;
    vector<int> v = {1,2,3};
    permutations(v,0,V);
    printvecofvec(V);

}
