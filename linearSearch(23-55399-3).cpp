// uploading to git

#include <iostream>
using namespace std;

int Search(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {10 , 2, 13, 7, 4, 5, 22, 43};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x;

    cout << "Enter the element to search: ";
    cin >> x;

    int result = Search(arr, n, x);

    if (result != -1)
        cout << "Element found at index: " << result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
