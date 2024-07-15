#include <iostream>
#include <vector>

using namespace std;

// Function to generate all orders recursively
void generateOrders(vector<int>& elements, vector<int>& order, vector<bool>& chosen, vector<vector<int>>& orders) {
    if (order.size() == elements.size()) {
        orders.push_back(order);
        return;
    }
    for (int i = 0; i < elements.size(); ++i) {
        if (!chosen[i]) {
            chosen[i] = true;
            order.push_back(elements[i]);
            generateOrders(elements, order, chosen, orders);
            order.pop_back();
            chosen[i] = false;
        }
    }
}

// Function to generate all orders of elements
vector<vector<int>> generateAllOrders(vector<int>& elements) {
    vector<vector<int>> orders;
    vector<int> order;
    vector<bool> chosen(elements.size(), false);
    generateOrders(elements, order, chosen, orders);
    return orders;
}

int main() {
    vector<int> elements = {1, 2, 3};

    vector<vector<int>> allOrders = generateAllOrders(elements);

    // Printing all orders
    for (const auto& order : allOrders) {
        for (int num : order) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
