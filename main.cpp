#include <iostream>
#include "Struct/Student.h"
#include "Utils/SortTestHelper.h"

using namespace std;

/**
 * 选择排序 O(n^2)
 */
template <typename T>
void selectionSort(T arr[], int n){

    for(int i = 0; i < n; ++ i){
        //标记最小值所在位置 初始为i 由于i之前的数已经被排序完成 所以循环将从i开始
        int minIndex = i;

        //每次循环找到最小值的位置
        for (int j = i + 1; j < n; ++ j) {
            //如果arr[j] < arr[minIndex] 说明j这个位置的元素更小 则更新minIndex
            if (arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        //当循环完毕 找到了最小值所在的位置 与arr[i]交换位置 i是从0-数组最后一位顺序遍历 所以保证前面数组一定排序完成
        swap(arr[i], arr[minIndex]);
    }
}

/**
 * 插入排序 O(n^2)
 * @tparam T
 * @param arr
 * @param n
 */
template <typename T>
void insertionSort(T arr[], int n){
    //循环 从1开始 后续对比从1开始 前一个元素与当前元素对比
    for (int i = 1; i < n; ++i) {
        //保存当前元素值
        T node = arr[i];
        //元素node应该在的位置
        int index;
        //循环 寻找元素arr[i]合适的插入位置 判断是否大于数组中第一个元素的位置 并且前一个元素大于当前元素
        for (index = i; index > 0 && arr[index - 1] > node; --index) {
            //如果满足index>0 并且前一个元素大与当前元素 则前一个元素向后移动一位 此时当前元素与前一个元素值相同
            arr[index] = arr[index-1];
        }

        //交换位置
        arr[index] = node;
    }
}

/**
 * 插入排序 [l...r]前闭后闭区间
 * @tparam T
 * @param arr
 * @param l
 * @param r
 */
template <typename T>
void insertionSort(T arr[], int l, int r){

    for (int i = l + 1; i <= r; ++i) {
        //寻找元素arr[i]合适的插入位置
        T node = arr[i];
        //元素node应该在的位置
        int j;

        for (j = i; j > l && arr[j - 1] > node; --j) {
            arr[j] = arr[j-1];
        }

        arr[j] = node;
    }
}

/**
 * 冒泡排序 O(n^2)
 * @tparam T
 * @param arr
 * @param n
 */
template <typename T>
void bubbleSort1(T arr[], int n){
    //[0...n]前闭后闭区间遍历
    for (int i = 0; i < n; ++i) {
        //每次循环把最大节点放在数组最后 则下次循环不需要访问后面i个元素的位置
        int times = n - i;
        //循环 当前元素与前一个元素对比 直到本轮最大值抵达(n - i)这个位置
        for (int j = 1; j < times; ++j) {
            //如果前一个元素大 则与后一位交换
            if (arr[j - 1] > arr[j]){
                //把最大的元素放到最后
                swap(arr[j - 1], arr[j]);
            }
        }
    }
}

/**
 * 优化 O(n^2)
 * @tparam T
 * @param arr
 * @param n
 */
template<typename T>
void bubbleSort2(T arr[] , int n){
    //临时标记值 相当于bubbleSort1中times
    int temp;
    do{
        //初始化临时标记
        temp = 0;
        //循环 首轮循环整个数组 长度为n 每轮循环结束后 相当于temp --
        //如果循环中没有满足arr[i - 1] > arr[i] 的情况 则直接结束
        for( int i = 1; i < n; i ++) {
            if(arr[i - 1] > arr[i]){
                swap(arr[i-1], arr[i]);
                temp = i;
            }
        }
        // 记录最后一次的交换位置 在此之后的元素在下一轮扫描中均不考虑
        n = temp;
        cout << temp << endl;
    }while(temp > 0);
}

template<typename T>
void __merge(T arr[] , int l, int mid, int r){
    //辅助数组大小 区间最大值 - 区间最小值 + 1
    int size = r - l + 1;
    T aux[size];

    //赋值 aux相当于一个子数组 并非全量大小 则需要从arr[l]的位置 拷贝到aux[0]的位置
    //进一步思考 aux => arr 有l个偏移量
    for (int i = l; i <= r; ++i) {
        aux[i - l] = arr[i];
    }

    //两数组进行归并分别记录两个子数组起始位置 与归并后数组第一个位置k 等于 l
    int i = l, j = mid + 1;

    //循环 k = l初始化 判断k <= 归并后数组最大值 依次递增
    for (int k = l; k <= r; ++k) {
        //如果i > mid 说明此时左侧子数组已经没有元素 则从右侧子数组继续
        if (i > mid){
            arr[k] = aux[j - l];
            j ++;
        } else if (j > r){ //如果j > r 说明此时右侧子数组已经没有元素 则从左侧子数组继续
            arr[k] = aux[i - l];
            i ++;
        } else if(aux[i - l] < aux[j - l]){
            //如果aux[i - l] < aux[j - l] 说明此时左侧子数组数值小 让归并后k的位置替换成相对小的元素
            arr[k] = aux[i - l];
            i ++;
        } else {
            //其他情况则说明aux[i - l] >= aux[j - l] 说明右侧子数组数值小
            arr[k] = aux[j - l];
            j ++;
        }
    }
}

//递归使用归并排序 对arr[l...r]前闭后闭的范围进行排序
template<typename T>
void __mergeSort(T arr[] , int l, int r){
    //如果该区间小于16个元素 则使用插入排序法
    if (r - l <= 15){
        //对该数组[l...r]区间进行排序
        insertionSort(arr, l, r);
        return;
    }

    //进入归并排序 计算出中值
    int mid = (l + r) / 2;

    //以中值切分 让其左数组进入新一轮归并排序[l...mid]
    __mergeSort(arr, l, mid);
    //以中值切分 让其右数组进入新一轮归并排序[mid + 1...r]
    __mergeSort(arr, mid + 1, r);

    //因为向上归并前 左右均以排序完成 则如果arr[mid] <= arr[mid + 1]的情况 则不需要归并排序
    //反之arr[mid] > arr[mid + 1] 则需要归并
    if (arr[mid] > arr[mid + 1])
        //实际归并操作
        __merge(arr, l, mid, r);
}

/**
 * 归并排序 O(nlog(n))
 * @tparam T
 * @param arr
 * @param n
 */
template<typename T>
void mergeSort(T arr[] , int n){
    //进行递归调用
    __mergeSort(arr, 0, n-1);
}

//自底向上的归并排序
template<typename T>
void mergeSortBu(T arr[] , int n){
    for (int sz = 1; sz < n; sz+=sz) {
        for (int i = 0; i < n; i += sz + sz) {
            //[i... i + sz -1] 与 [i + sz -1... i + 2sz -1] 归并
            __merge(arr, i, i + sz -1, min(i + sz + sz - 1, n -1));
        }
    }
}

int main() {
    int n = 1000000;
    int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);

    SortTestHelper::testSort("selection sort", mergeSortBu, arr1, n);

    delete[] arr1;

    return 0;
}