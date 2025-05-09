#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int findMinimumLengthSubarray(int arr_count, int* arr, int k) {
    int left = 0;
    int min_length = arr_count + 1;
    int distinct_count = 0;

    // Allocate a frequency array for counting occurrences, assuming arr[i] <= 1,000,000
    int freq[1000001] = {0};


    for (int right = 0; right < arr_count; ++right) {
        // Add the current element at the right end to the window
        if (freq[arr[right]] == 0) {
            ++distinct_count;
        }
        ++freq[arr[right]];

        // Shrink the window from the left while we have at least `k` distinct elements
        while (distinct_count >= k) {
            // Update the minimum length if the current window is smaller
            int current_length = right - left + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }

            // Remove the element at the left end from the window
            --freq[arr[left]];
            if (freq[arr[left]] == 0) {
                --distinct_count;
            }
            ++left;
        }
    }

    // If no valid subarray was found, return -1
    return (min_length == arr_count + 1) ? -1 : min_length;
}

int main() {
    int arr[] = {2, 2, 1, 1, 3};
    int k = 3;
    int arr_count = sizeof(arr) / sizeof(arr[0]);

    int result = findMinimumLengthSubarray(arr_count, arr, k);
    if (result != -1) {
        printf("Minimum length of subarray with at least %d distinct integers is: %d\n", k, result);
    } else {
        printf("No subarray with %d distinct integers exists.\n", k);
    }

    return 0;
}
