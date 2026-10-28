#include <stdio.h>
#include <stdlib.h>
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int * leftArray = malloc(n1 * sizeof(int));
    int * rightArray = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = arr[mid + 1 + j];
    }
    int i = 0; 
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {  
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
    free(leftArray);
    free(rightArray);
}
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
int main(void) {
    int numbers[] = {6, 11, 1, 10, 19, 4, 25, 3, 9, 8};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    printf("Original array: ");
    printArray(numbers, size);
    mergeSort(numbers, 0, size - 1);
    printf("Sorted array: ");
    printArray(numbers, size);
    return 0;
}