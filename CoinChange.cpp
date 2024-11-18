#include <iostream>
#include <vector>
#include <climits>  // INT_MAX를 위해 포함
#include <iomanip>  // setw를 위해 포함

using namespace std;

int DPCoinChange(vector<int>& coins, int n) {
    // C[j]는 금액 j를 만들기 위해 필요한 최소 동전 개수를 나타냄
    vector<int> C(n + 1, INT_MAX);
    
    C[0] = 0;  // 금액 0을 만들기 위해 필요한 최소 동전 개수는 0

    // 1부터 n까지의 금액을 고려
    for (int j = 1; j <= n; j++) {
        // 주어진 동전 집합에서 각 동전을 고려
        for (int i = 0; i < coins.size(); i++) {
            int coin = coins[i];
            if (coin <= j && C[j - coin] != INT_MAX) {
                C[j] = min(C[j], C[j - coin] + 1);
            }
        }
    }

    // DP 테이블 출력 (위에는 금액, 아래는 최소 동전 개수)
    cout << "\nDP 테이블:" << endl;
    // 금액을 위에 출력
    cout << "j   ";
    for (int i = 1; i <= n; i++) {
        cout << setw(4) << i;  // setw를 사용해 간격 조정
    }
    cout << endl;

    // 구분선 출력
    cout << "---------------------";
    for (int i = 1; i <= n; i++) {
        cout << "----";  // 고정 폭으로 구분선 출력
    }
    cout << endl;

    // 최소 동전 개수를 아래에 출력
    cout << "c   ";
    for (int i = 1; i <= n; i++) {
        cout << setw(4) << (C[i] == INT_MAX ? "N/A" : to_string(C[i]));  // 최소 동전 개수 출력, 불가능하면 "N/A"
    }
    cout << endl;

    return C[n];  // 최소 동전 개수를 반환
}

int main() {
    // 동전의 종류 (액면가)
    vector<int> coins = {16, 10, 5, 1};
    // 목표 금액
    int n = 20;

    // 최소 동전 개수 계산
    int result = DPCoinChange(coins, n);

    if (result != -1) {
        cout << "\n" << n << "원을 만들기 위한 최소 동전 개수: " << result << endl;
    } else {
        cout << n << "원을 만들 수 없습니다." << endl;
    }

    return 0;
}
