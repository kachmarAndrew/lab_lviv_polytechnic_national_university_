#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

/* 1. СОРТУВАННЯ ВИБОРОМ */
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        swap(arr[i], arr[minIndex]);
    }
}

/* 2. КОКТЕЙЛЬНЕ СОРТУВАННЯ */
void cocktailSort(vector<int>& arr) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;

    while (swapped) {

        swapped = false;

        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        start++;
    }
}

/* 3. СОРТУВАННЯ КОМІРКАМИ (Bucket Sort) */
void bucketSort(vector<int>& arr) {

    int maxVal = *max_element(arr.begin(), arr.end());
    int bucketCount = 10;

    vector<vector<int>> buckets(bucketCount);

    for (int i = 0; i < arr.size(); i++) {
        int index = (arr[i] * bucketCount) / (maxVal + 1);
        buckets[index].push_back(arr[i]);
    }

    arr.clear();

    for (int i = 0; i < bucketCount; i++) {
        sort(buckets[i].begin(), buckets[i].end());

        for (int num : buckets[i])
            arr.push_back(num);
    }
}

/* 4. СОРТУВАННЯ ЗЛИТТЯМ */

void merge(vector<int>& arr, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* ФУНКЦІЯ ДЛЯ ВИМІРЮВАННЯ ЧАСУ */
long long testSort(void (*sortFunc)(vector<int>&), vector<int> arr) {

    auto start = high_resolution_clock::now();

    sortFunc(arr);

    auto stop = high_resolution_clock::now();

    return duration_cast<milliseconds>(stop - start).count();
}

int main() {

    const int SIZE = 20000;

    vector<int> data(SIZE);

    for (int i = 0; i < SIZE; i++)
        data[i] = rand() % 10000;

    vector<int> arr1 = data;
    vector<int> arr2 = data;
    vector<int> arr3 = data;
    vector<int> arr4 = data;

    cout << "Selection Sort time: "
         << testSort(selectionSort, arr1) << " ms\n";

    cout << "Cocktail Sort time: "
         << testSort(cocktailSort, arr2) << " ms\n";

    cout << "Bucket Sort time: "
         << testSort(bucketSort, arr3) << " ms\n";

    auto start = high_resolution_clock::now();
    mergeSort(arr4, 0, arr4.size() - 1);
    auto stop = high_resolution_clock::now();

    cout << "Merge Sort time: "
         << duration_cast<milliseconds>(stop - start).count()
         << " ms\n";

    return 0;
}