//
// Created by Eddie Lee on 2018/10/15.
//

#ifndef ALGORITHM_SORTTESTHELPER_H
#define ALGORITHM_SORTTESTHELPER_H

#include <iostream>
#include <cassert>

using namespace std;

namespace SortTestHelper{

    /**
     * 生成近乎有序的数组
     * @param n
     * @param rangeL
     * @param rangeR
     * @return
     */
    int* generateNearlyOrderRandomArray(int n, int swapTimes){

        int* arr = new int[n];

        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }

        srand(time(NULL));

        for (int j = 0; j < swapTimes; ++j) {
            int posx = rand() % n;
            int posy = rand() % n;
            swap(arr[posx], arr[posy]);
        }

        return arr;
    };

    /**
     * 这个函数将生成n个在[rangeL,rangeR]范围中
     * @param n
     * @param rangeL
     * @param rangeR
     * @return
     */
    int* generateRandomArray(int n, int rangeL, int rangeR){

        assert(rangeL <= rangeR);

        int *arr = new int[n];

        srand(time(NULL));

        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }

        return arr;
    };

    template <typename T>
    void printArray(T arr[], int n){

        for (int i = 0; i < n; ++i) {

            cout << arr[i] << " ";

        }

        cout << endl;

        return;
    }

    template <typename T>
    bool isSorted(T arr[], int n){

        for (int i = 0; i < n - 1; ++i) {

            if (arr[i] > arr[i + 1]) {
                return false;
            }

        }

        return true;
    }

    template <typename T>
    void testSort(string sortName, void(*sort)(T arr[], int), T arr[], int n){

        clock_t startTime = clock();

        sort(arr, n);

        clock_t endTime = clock();

        assert(isSorted(arr, n));

        cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

    }

    int* copyArray(int arr[], int n){

        int* array = new int[n];
        copy(arr, arr + n, array);

        return array;
    }
}

#endif //ALGORITHM_SORTTESTHELPER_H
