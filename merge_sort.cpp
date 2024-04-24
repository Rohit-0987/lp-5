#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

void merge(int arr[], int start, int mid, int end) {
    int left_size = mid - start + 1;
    int right_size = end - mid;

    int* left = new int[left_size];
    int* right = new int[right_size];

    for (int i = 0; i < left_size; ++i) {
        left[i] = arr[start + i];
    }
    for (int j = 0; j < right_size; ++j) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = start;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            ++i;
        } else {
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }

    while (i < left_size) {
        arr[k] = left[i];
        ++i;
        ++k;
    }

    while (j < right_size) {
        arr[k] = right[j];
        ++j;
        ++k;
    }

    delete[] left;
    delete[] right;
}

void merge_sort(int arr[], int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void parallel_merge_sort(int arr[], int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallel_merge_sort(arr, start, mid);

            #pragma omp section
            parallel_merge_sort(arr, mid + 1, end);
        }
        merge(arr, start, mid, end);
    }
}

double measure_sequential_performance(int arr[], int n) {
    double start_time = omp_get_wtime();
    merge_sort(arr, 0, n - 1);
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

double measure_parallel_performance(int arr[], int n) {
    double start_time = omp_get_wtime();
    parallel_merge_sort(arr, 0, n - 1);
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

int main() {
    const int arr_size = 10000;
    int random_arr[arr_size];
    srand(time(nullptr));
    for (int i = 0; i < arr_size; ++i) {
        random_arr[i] = rand() % 1000;
    }

    // Sequential Merge Sort Performance Measurement
    std::cout << "Sequential Merge Sort Performance:" << std::endl;
    double sequential_time = measure_sequential_performance(random_arr, arr_size);
    std::cout << "Time taken for sequential merge sort: " << sequential_time << " seconds" << std::endl;

    // Parallel Merge Sort Performance Measurement
    std::cout << "\nParallel Merge Sort Performance:" << std::endl;
    double parallel_time = measure_parallel_performance(random_arr, arr_size);
    std::cout << "Time taken for parallel merge sort: " << parallel_time << " seconds" << std::endl;

    return 0;
}
