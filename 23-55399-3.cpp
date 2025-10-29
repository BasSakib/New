#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int a[], int n) {
    int pass, j, flag;
    for (pass = 1; pass < n; pass++) {
        flag = 0;
        for (j = 0; j < (n - pass); j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0) break;
    }
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {4, 44, 5, 12, 32, 21, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array is : ";
    printArray(arr, n);

    bubble(arr, n);

    cout << "The Sorted array is : ";
    printArray(arr, n);

    return 0;
}

