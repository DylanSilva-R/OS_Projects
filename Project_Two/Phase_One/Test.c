#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Define the Student struct
typedef struct {
    char name[MAX_NAME_LENGTH];
    float grade;
} Student;

// Function to merge two halves
void merge(Student *array, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    Student *L = (Student *)malloc(n1 * sizeof(Student));
    Student *R = (Student *)malloc(n2 * sizeof(Student));

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    // Merge the temporary arrays back into array[left..right]
    i = 0; // Initial index of first sub-array
    j = 0; // Initial index of second sub-array
    k = left; // Initial index of merged sub-array
    while (i < n1 && j < n2) {
        if (L[i].grade <= R[j].grade) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    free(L);
    free(R);
}

// Function to implement merge sort
void mergeSort(Student *array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        // Merge the sorted halves
        merge(array, left, mid, right);
    }
}

// Function to print the array
void printArray(Student *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Grade: %.2f\n", array[i].name, array[i].grade);
    }
}

// Main function
int main() {
    Student students[] = {
        {"Alice", 85.5},
        {"Bob", 92.0},
        {"Charlie", 78.0},
        {"David", 90.0},
        {"Eve", 88.0}
    };

    int size = sizeof(students) / sizeof(students[0]);

    printf("Original array:\n");
    printArray(students, size);

    mergeSort(students, 0, size - 1);

    printf("\nSorted array (by grade):\n");
    printArray(students, size);

    return 0;
}
