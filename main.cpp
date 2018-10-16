#include <iostream>
#include "Struct/Student.h"
#include "Utils/SortTestHelper.h"

using namespace std;

/**
 * 选择排序
 * @tparam T
 * @param arr
 * @param n
 */
template <typename T>
void selectionSort(T arr[], int n){

    for(int i = 0; i < n; ++ i){

        int minIndex = i;

        for (int j = i + 1; j < n; ++ j) {

            if ( arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}

template <typename T>
void insertionSort(T arr[], int n){

    for (int i = 1; i < n; ++i) {
        //寻找元素arr[i]合适的插入位置
        T node = arr[i];
        //元素node应该在的位置
        int j;

        for (j = i; j > 0 && arr[j - 1] > node; --j) {
            arr[j] = arr[j-1];
        }

        arr[j] = node;
    }
}

template <typename T>
void bubbleSort(T arr[], int n){

    for (int i = 0; i < n; ++i) {

        int temp = i;

        for (int j = i; j < n; ++j) {

            if (arr[temp] > arr[j]){

                temp = j;

            }
        }

        swap(arr[temp], arr[i]);
    }

}

int main() {
    int n = 100000;
    int *arr1 = SortTestHelper::generateNearlyOrderRandomArray(n, 1000);
    int *arr2 = SortTestHelper::copyArray(arr1, n);
    int *arr3 = SortTestHelper::copyArray(arr1, n);

    SortTestHelper::testSort("selection sort", selectionSort, arr1, n);

    SortTestHelper::testSort("insertion sort", insertionSort, arr2, n);

    SortTestHelper::testSort("bubble sort", bubbleSort, arr1, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
}