#include <chrono>
#include <iostream>
using namespace std;

const int n = 50000;
void fillArr(int*, int*);
void restoreArr(int*, int*);
int findpivot(int, int, int*);
int partition(int, int, int, int*);
void quicksort(int, int, int*);
void insertsort(int*);

int main() {
    int* A = new int[n];
    int* B = new int[n];
    fillArr(A, B);
    chrono::steady_clock::time_point beg;
    chrono::steady_clock::time_point end;
    beg = chrono::steady_clock::now();
    insertsort(A);
    end = chrono::steady_clock::now();
    cout << "Time of insertion sort: " << chrono::duration_cast<chrono::milliseconds>(end - beg).count() << "ms." << endl;

    restoreArr(A, B);
    
    beg = chrono::steady_clock::now();
    quicksort(0, n - 1, A);
    end = chrono::steady_clock::now();
    cout << endl << "Time of quick sort: " << chrono::duration_cast<chrono::milliseconds>(end - beg).count() << "ms." << endl;
    return 0;
}

void fillArr(int* A, int* B) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = (int)rand();
        B[i] = A[i];
    }
}

void restoreArr(int* A, int* B) {
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}

int findpivot(int i, int j, int* A) {
    int fk;
    fk = A[i];
    for (int k = i + 1; k <= j; k++) {
        if (A[k] > fk)
            return k;
        else if (A[k] < fk)
            return i;
    }
    return -1;
}

int partition(int i, int j, int pivot, int* A) {
    int l, r;
    l = i;
    r = j;
    do {
        swap(A[l], A[r]);
        while (A[l] < pivot)
            l++;
        while (A[r] >= pivot)
            r--;
    } while (l <= r);
    return l;
}

void quicksort(int i, int j, int* A) {
    int pivot;
    int pivotindex;
    int k;
    pivotindex = findpivot(i, j, A);
    if (pivotindex != -1) {
        pivot = A[pivotindex];
        k = partition(i, j, pivot, A);
        quicksort(i, k - 1, A);
        quicksort(k, j, A);
    }
}

void insertsort(int* A) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (A[j] < A[j - 1]) {
            swap(A[j], A[j - 1]);
            if (--j == 0)
                break;
        }
    }
}