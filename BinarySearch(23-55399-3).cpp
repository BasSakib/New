#include <iostream>
using namespace std;

int BinarySearch(int arr[], int size, int item) {
    int m_index, position = -1, f_index = 0, l_index = size - 1;

    while (f_index <= l_index) {
        m_index = (f_index + l_index) / 2;

        if (item < arr[m_index]) {
            l_index = m_index - 1;
        }
        else if (item > arr[m_index]) {
            f_index = m_index + 1;
        }
        else {
            position = m_index;
            break;
        }
    }
    return position;
}

int main() {
    int arr[] = {10 , 2, 13, 7, 4, 5, 22, 43};
    int size = sizeof(arr) / sizeof(arr[0]);
    int item;

    cout << "Enter the element to search: ";
    cin >> item;

    int result = BinarySearch(arr, size, item);

    if (result != -1)
        cout << "Element found at index: " << result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
