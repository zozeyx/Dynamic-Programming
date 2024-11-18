#include <iostream>
#include <vector>
#include <climits>  // for INT_MAX
#include <iomanip>  // for setw

using namespace std;

int DPCoinChange(vector<int>& coins, int n) {
    // C[j] represents the minimum number of coins required to make amount j
    vector<int> C(n + 1, INT_MAX);
    
    C[0] = 0;  // Minimum coins required to make amount 0 is 0

    // Consider amounts from 1 to n
    for (int j = 1; j <= n; j++) {
        // Consider each coin in the given set
        for (int i = 0; i < coins.size(); i++) {
            int coin = coins[i];
            if (coin <= j && C[j - coin] != INT_MAX) {
                C[j] = min(C[j], C[j - coin] + 1);
            }
        }
    }

    // Print the DP table (amounts on top, minimum coins below)
    cout << "\nDP Table:" << endl;
    // Print amounts on top
    cout << "j   ";
    for (int i = 1; i <= n; i++) {
        cout << setw(4) << i;  // Adjust spacing with setw
    }
    cout << endl;

    // Print separator line
    cout << "-----------------------------";
    for (int i = 1; i <= n; i++) {
        cout << "----";  // Fixed-width separator
    }
    cout << endl;

    // Print minimum number of coins below
    cout << "c   ";
    for (int i = 1; i <= n; i++) {
        cout << setw(4) << (C[i] == INT_MAX ? "N/A" : to_string(C[i]));  // Print minimum coins or "N/A" if not possible
    }
    cout << endl;

    return C[n];  // Return minimum number of coins
}

int main() {
    // Types of coins (denominations)
    vector<int> coins = {16, 10, 5, 1};
    // Target amount
    int n = 20;

    // Calculate the minimum number of coins
    int result = DPCoinChange(coins, n);

    if (result != -1) {
        cout << "\nMinimum number of coins to make change for " << n << ": " << result << endl;
    } else {
        cout << "It is not possible to make change for " << n << "." << endl;
    }

    return 0;
}
