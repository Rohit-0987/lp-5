#include <iostream>
#include <omp.h>

const int N = 10000;
int arr[N];

// Function to initialize the array with random values
void initializeArray() {
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 1000;
    }
}

// Function to find the minimum value in the array
int findMin() {
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for (int i = 0; i < N; ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

// Function to find the maximum value in the array
int findMax() {
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < N; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

// Function to calculate the sum of values in the array
int findSum() {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += arr[i];
    }
    return sum;
}

// Function to calculate the average of values in the array
double findAverage() {
    int sum = findSum();
    return static_cast<double>(sum) / N;
}

int main() {
    srand(time(nullptr));

    // Initialize the array with random values
    initializeArray();

    // Find and print the minimum value in the array
    int min_val = findMin();
    std::cout << "Minimum value in the array: " << min_val << std::endl;

    // Find and print the maximum value in the array
    int max_val = findMax();
    std::cout << "Maximum value in the array: " << max_val << std::endl;

    // Find and print the sum of values in the array
    int sum = findSum();
    std::cout << "Sum of values in the array: " << sum << std::endl;

    // Find and print the average of values in the array
    double avg = findAverage();
    std::cout << "Average of values in the array: " << avg << std::endl;

    return 0;
}

