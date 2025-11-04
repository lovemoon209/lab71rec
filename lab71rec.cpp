#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void Create(int **a, const int ROW, const int COL, const int Low, const int High, int i = 0, int j = 0) {
    if (i < ROW) {
        if (j < COL) {
            a[i][j] = Low + rand() % (High - Low + 1);
            Create(a, ROW, COL, Low, High, i, j + 1);
        } else {
            Create(a, ROW, COL, Low, High, i + 1, 0);
        }
    }
}

void Print(int **a, const int ROW, const int COL, int i = 0, int j = 0) {
    if (i < ROW) {
        if (j < COL) {
            cout << setw(5) << a[i][j];
            Print(a, ROW, COL, i, j + 1);
        } else {
            cout << endl;
            Print(a, ROW, COL, i + 1, 0);
        }
    }
}

void ChangeCols(int **a, const int ROW, int c1, int c2, int i = 0) {
    if (i < ROW) {
        int tmp = a[i][c1];
        a[i][c1] = a[i][c2];
        a[i][c2] = tmp;
        ChangeCols(a, ROW, c1, c2, i + 1);
    }
}

void SortCols(int **a, const int ROW, const int COL, int pass = 0, int j = 0) {
    if (pass < COL - 1) {
        if (j < COL - pass - 1) {
            bool swapNeeded = false;
            if (a[0][j] > a[0][j + 1]) swapNeeded = true;
            else if (a[0][j] == a[0][j + 1]) {
                if (a[1][j] > a[1][j + 1]) swapNeeded = true;
                else if (a[1][j] == a[1][j + 1] && a[2][j] < a[2][j + 1]) swapNeeded = true;
            }
            if (swapNeeded) ChangeCols(a, ROW, j, j + 1);
            SortCols(a, ROW, COL, pass, j + 1);
        } else {
            SortCols(a, ROW, COL, pass + 1, 0);
        }
    }
}

void Calc(int **a, const int ROW, const int COL, int &S, int &k, int i = 0, int j = 0) {
    if (i < ROW) {
        if (j < COL) {
            if (a[i][j] % 2 == 0 && a[i][j] % 7 != 0) {
                S += a[i][j];
                k++;
                a[i][j] = 0;
            }
            Calc(a, ROW, COL, S, k, i, j + 1);
        } else {
            Calc(a, ROW, COL, S, k, i + 1, 0);
        }
    }
}

int main() {
    srand((unsigned)time(NULL));

    const int ROW = 9;
    const int COL = 6;
    const int Low = 18;
    const int High = 74;

    int **Z = new int*[ROW];
    for (int i = 0; i < ROW; i++) Z[i] = new int[COL];

    Create(Z, ROW, COL, Low, High);
    cout << "start:" << endl;
    Print(Z, ROW, COL);

    int S = 0, k = 0;
    
    Calc(Z, ROW, COL, S, k);
    cout << endl << "S = " << S << endl;
    cout << "k = " << k << endl;

    cout << endl << "reset:" << endl;
    Print(Z, ROW, COL);

    SortCols(Z, ROW, COL);
    cout << endl << "sort:" << endl;
    Print(Z, ROW, COL);

    for (int i = 0; i < ROW; i++) delete[] Z[i];
    delete[] Z;
    return 0;
}
