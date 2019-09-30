#include <iostream>

using namespace std;

/*
 * Compute B = A for CSR matrix A, CSC matrix B
 *
 * Also, with the appropriate arguments can also be used to:
 *   - compute B = A^t for CSR matrix A, CSR matrix B
 *   - compute B = A^t for CSC matrix A, CSC matrix B
 *   - convert CSC->CSR
 *
 * Input Arguments:
 *   I  n_row         - number of rows in A
 *   I  n_col         - number of columns in A
 *   I  Ap[n_row+1]   - row pointer
 *   I  Aj[nnz(A)]    - column indices
 *   T  Ax[nnz(A)]    - nonzeros
 *
 * Output Arguments:
 *   I  Bp[n_col+1] - column pointer
 *   I  Bj[nnz(A)]  - row indices
 *   T  Bx[nnz(A)]  - nonzeros
 *
 * Note:
 *   Output arrays Bp, Bj, Bx must be preallocated
 *
 * Note:
 *   Input:  column indices *are not* assumed to be in sorted order
 *   Output: row indices *will be* in sorted order
 *
 *   Complexity: Linear.  Specifically O(nnz(A) + max(n_row,n_col))
 *
 */

void SPARSE_TRANSPOSE(const int m, const int n, const int k, const int *R, const int *C, const int *V,
                      int *tR, int *tC, int *tV) {

    //compute number of non-zero entries per column of A 
    std::fill(tR, tR + n, 0);

    for (int i = 0; i < k; i++){
        tR[C[i]]++;
    }

    //cumsum the number of non zero per column to get tR[]
    for(int col = 0, cumsum = 0; col < n; col++){
        int temp  = tR[col];
        tR[col] = cumsum;
        cumsum += temp;
    }
    tR[n] = 100;

    for(int row = 0; row < m; row++){
        for(int jj = R[row]; jj < R[row+1]; jj++){
            int col  = C[jj];
            int dest = tR[col];

            tC[dest] = row;
            tV[dest] = V[jj];

            tR[col]++;
        }
    }  

    for(int col = 0, last = 0; col <= n; col++){
        int temp  = tR[col];
        tR[col] = last;
        last    = temp;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    int R[] = {0, 2, 3, 5};
    int C[] = {1, 3, 2, 0, 1};
    int V[] = {9, 1, 1, 3, 8};

    int n_row = 3;
    int n_col = 4;

    auto *Rt = new int[n_col + 1];
    auto *Ct = new int[5];
    auto *Vt = new int[5];

    SPARSE_TRANSPOSE(n_row, n_col, 5, R, C, V, Rt, Ct, Vt);

    for (int i = 0; i < n_col + 1; ++i) {
        cout << Rt[i] << ", ";
    }
    cout << endl;

    for (int j = 0; j < 5; ++j) {
        cout << Ct[j] << ", ";
    }
    cout << endl;

    for (int k = 0; k < 5; ++k) {
        cout << Vt[k] << ", ";
    }

    cout << endl;


    delete[] Rt;
    delete[] Ct;
    delete[] Vt;

    return 0;
}