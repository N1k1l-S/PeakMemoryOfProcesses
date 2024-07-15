#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <cstring> // for memset

int n, mini = 10000, co=0;
vector<int> order1;


void printVectorOfVectors(const vector<vector<int>>& vec) {
    for (const auto& innerVec : vec) {
        for (int num : innerVec) {
            cout << num << " ";
        }
        cout << endl;
    }
}

void printvec(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << "\n";
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

// void permutations(vector<int> &vec, int left, vector<vector<int>>& V){
//     int last = vec.size();
//     if(left == last){
//         V.push_back(vec);
//         return;
//     }

//     for(int i=left;i<last;i++){
//         swap(vec[left],vec[i]);
//         permutations(vec,left+1,V);
//         swap(vec[left],vec[i]);
//     }
// }

// Function to generate all orders recursively
void generateOrders(const vector<int>& elements, vector<int>& order, vector<bool>& chosen, vector<vector<int>>& orders, const vector<vector<int>> &mem) {
    if (order.size() == elements.size()) {
        orders.push_back(order);
        // cout << ">>>>>>"; co++;
        // printvec(order);
        if(!checkorder(order,mem)) {
            ;
            // cout << " -> ";
            // printvec(order);
        }
        else if(mini > peakmem(mem,order)){
            order1 = order;
            // printvec(order);
            mini = peakmem(mem,order);
        }
        // else mini = std::min(peakmem(mem,order),mini);
        return;
    }
    for (int i = 0; i < elements.size(); ++i) {
        if (!chosen[i]) {
            chosen[i] = true;
            order.push_back(elements[i]);
            generateOrders(elements, order, chosen, orders, mem);
            order.pop_back();
            chosen[i] = false;
        }
    }
}

// Function to generate all orders of elements
vector<vector<int>> generateAllOrders(vector<int>& elements,const vector<vector<int>> &mem, vector<vector<int>> &orders) {
    vector<int> order;
    vector<bool> chosen(elements.size(), false);
    generateOrders(elements, order, chosen, orders, mem);
    return orders;
}

int main(){
	   /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	// int n; // number of processes

	cin >> n;
    vector<vector<int>> orders;
    vector<int> el_list; // element list
    for(int i=0;i<n;i++){
        el_list.push_back(i);
    }
	
	// vector< int > memory;
    vector<vector<int>> mem;
	vector<int> temp_vec;
    int a;
    // int mem[n][100], rowsums[n], colsums[n], totsum=0;
    // memset(mem, 0, sizeof(mem));
    // memset(rowsums, 0, sizeof(rowsums));
    // memset(colsums, 0, sizeof(colsums));
	
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

    generateAllOrders(el_list,mem,orders);
	
	// PRINT 
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout << mem[i][j] << "  ";
    //     }
    //     cout << endl;
    // }
    // printVectorOfVectors(mem);
    // cout<<"mm\n";
    // printVectorOfVectors(orders);

  	cout << mini << endl;
    // printvec(order1);
  	// cout << co << endl;
	return 0;
}
