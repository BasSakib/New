#include <iostream>
using namespace std;

void countingSort(int arr[], int n) {

    int k = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > k) {
            k = arr[i];
        }
    }
    int C[k + 1];
    for (int i = 0; i <= k; i++) {
        C[i] = 0;
    }
    for (int j = 0; j < n; j++) {
        C[arr[j]]++;
    }
    for (int i = 1; i <= k; i++) {
        C[i] += C[i - 1];
    }
    int B[n];
    for (int j = n - 1; j >= 0; j--) {
        B[C[arr[j]] - 1] = arr[j];
        C[arr[j]]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = B[i];
    }
}

int main() {
    int arr[] = {2, 6, 7, 3, 3, 1, 3, 2, 5, 7, 8, 2, 1, 9, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "The given array is: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    countingSort(arr, n);

    cout << "The Sorted array is : ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
