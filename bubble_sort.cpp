#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallel_bubble_sort(int arr[], int n) {
    #pragma omp parallel for shared(arr)
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

double measure_sequential_performance(int arr[], int n) {
    double start_time = omp_get_wtime();
    bubble_sort(arr, n);
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

double measure_parallel_performance(int arr[], int n) {
    double start_time = omp_get_wtime();
    parallel_bubble_sort(arr, n);
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

    // Sequential Bubble Sort Performance Measurement
    std::cout << "Sequential Bubble Sort Performance:" << std::endl;
    double sequential_time = measure_sequential_performance(random_arr, arr_size);
    std::cout << "Time taken for sequential bubble sort: " << sequential_time << " seconds" << std::endl;

    // Parallel Bubble Sort Performance Measurement
    std::cout << "\nParallel Bubble Sort Performance:" << std::endl;
    double parallel_time = measure_parallel_performance(random_arr, arr_size);
    std::cout << "Time taken for parallel bubble sort: " << parallel_time << " seconds" << std::endl;

    return 0;
}
