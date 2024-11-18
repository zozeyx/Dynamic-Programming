#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

#define INF std::numeric_limits<int>::max()
#define MAX_MATRICES 100

using namespace std;

// 파일에서 행렬 정보를 읽어오는 함수
int parseMatrixDimensions(ifstream& inputFile, int matrixSizes[][2]) {
    int matrixCount = 0;
    int currentRows = 0, currentCols = 0;
    string line;

    while (getline(inputFile, line)) {
        if (line.find("[") != string::npos) {
            currentRows++;
        }

        if (currentRows == 1) { // 첫 번째 행에서 열의 개수 계산
            size_t startPos = line.find("[[");
            line = (startPos != string::npos) ? line.substr(startPos + 1) : line;
            stringstream ss(line);
            string token;

            while (ss >> token) {
                if (token != "[" && token != "]") {
                    currentCols++;
                }
            }
        }

        if (line.find("]]") != string::npos) { // 행렬의 끝을 만났을 때
            matrixSizes[matrixCount][0] = currentRows;
            matrixSizes[matrixCount][1] = currentCols;
            matrixCount++;

            currentRows = 0;
            currentCols = 0;
        }
    }

    return matrixCount;
}

// 최적의 행렬 곱셈 순서를 계산하는 함수
int calculateMinMultiplications(int matrixSizes[][2], int dpTable[][MAX_MATRICES], int count) {
    for (int i = 0; i <= count; i++) {
        dpTable[i][i] = 0; // 자기 자신을 곱하는 비용은 0
    }

    for (int chainLength = 1; chainLength <= count - 1; chainLength++) {
        for (int i = 0; i <= count - chainLength; i++) {
            int j = i + chainLength;
            dpTable[i][j] = INF;

            for (int k = i; k <= j - 1; k++) {
                int cost = dpTable[i][k] + dpTable[k + 1][j] +
                           matrixSizes[i][0] * matrixSizes[k][1] * matrixSizes[j][1];
                if (cost < dpTable[i][j]) {
                    dpTable[i][j] = cost;
                }
            }
        }
    }

    return dpTable[0][count - 1];
}

// DP 테이블 출력 함수
void displayDpTable(int dpTable[][MAX_MATRICES], int matrixCount) {
    printf("DP Table\n");
    printf("     ");
    for (int i = 1; i <= matrixCount; i++) {
        printf("%-10d", i);
    }
    printf("\n");

    for (int i = 1; i <= matrixCount; i++) {
        printf("%-5d", i);
        for (int j = 1; j <= matrixCount; j++) {
            if (j < i) {
                printf("          ");
            } else {
                printf("%-10d", dpTable[i - 1][j - 1]);
            }
        }
        printf("\n");
    }
}

int main() {
    ifstream inputFile("matrix_input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open the file.\n";
        return 1;
    }

    int matrixSizes[MAX_MATRICES][2] = {0};
    int matrixCount = parseMatrixDimensions(inputFile, matrixSizes);

    int dpTable[MAX_MATRICES][MAX_MATRICES];
    int minOperations = calculateMinMultiplications(matrixSizes, dpTable, matrixCount);

    displayDpTable(dpTable, matrixCount);
    printf("Minimum number of multiplications: %d\n", minOperations);

    return 0;
}
