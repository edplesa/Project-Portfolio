#include <stdio.h>
#include <stdlib.h>

//Code by: Edward Plesa, Spring 2021, CS211


//
//  makeArrayCopy: give 2 references to arrays and their size, this
//  function copies the contents of "fromArray" to the "toArray"
//
void makeArrayCopy(int fromArray[], int toArray[], int size)
{
    for (int i = 0; i < size; i++)
    {
        toArray[i] = fromArray[i];
    }
}


//
//  myFavoriteSort: given an array by reference and its size, 
//  this function will sort the array in descending order.
//
void myFavoriteSort(int arr[], int size)
{
    int temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

//
//  indexComparison, given an unsorted and sorted array (by reference),
//  this function will compare each index and count how many elements have
//  changed from their original position and return this value back to the
//  user.
//
void indexComparison(int unsortedArray[], int sortedArray[], int size, int* counter)
{
    for (int i = 0; i < size; i++)
    {
        if (unsortedArray[i] == sortedArray[i])
        {
            *counter += 1;
        }
    }
}


//
//  targetSum: given a sorted array (and its size) along with the target,
//  sets two pointers at the beginning and the end of the array, then starts 
//  moving the pointers inward while checking their sum. If itâ€™s exactly
//  the â€œtargetâ€, then we are done, and return 1. If it exceeds the â€œtargetâ€ value, then
//  any sum using the larger element is too large, so move the pointer corresponding to that
//  element inward. If the sum is less than â€œtargetâ€ value, then any sum using the lower
//  element is too small, so move the pointer corresponding to that element inwards. If you
//  are done with scanning the array and cannot find any two elements that sum up to
//  â€œtargetâ€ value, returns -1.
//
int targetSum(int arr[], int size, int target, int* index1, int* index2)
{
    *index1 = 0;
    *index2 = size - 1;

    for (int i = 0; i < size-1; i++)
    {
        if (arr[*index1] + arr[*index2] == target)
        {
            return 1;
        }
        else if (arr[*index1] + arr[*index2] > target)
        {
            *index2 -= 1;
        }
        else if (arr[*index1] + arr[*index2] < target)
        {
            
            *index1 += 1;
        }   
    }

    return -1;
}



int main()
{
    int* darr;
    int allocated = 4;
    darr = (int*)malloc(allocated * sizeof(int));

    /* prompt the user for input */
    printf("Enter in a list of numbers to be stored in a dynamic array.\n");
    printf("End the list with the terminal value of -999\n");

    /* loop until the user enters -999 and plug values into array*/
    int val;
    int count = 0;

    scanf("%d", &val);

    while (val != -999)
    {
        if (count >= allocated)
        {
            int* temp = darr;
            darr = (int*)malloc(allocated * 2 * sizeof(int));
            for (int i = 0; i < allocated; i++)
            {
                darr[i] = temp[i];
            }
            free(temp);
            allocated = allocated * 2;
        }
        darr[count] = val;
        count++;
        scanf("%d", &val);
    }

    int *arrCopy = (int*)malloc(count * sizeof(int));

    makeArrayCopy(darr, arrCopy, count); //populate the copy of the original array

    myFavoriteSort(arrCopy, count); //sort the copied array in ascending order


    int choice;
    printf("Enter 1 to perform index comparison, enter 2 to perform target sum.\n");
    scanf("%d", &choice);

    while (choice != 1 && choice != 2)
    {
        printf("Invalid input. Enter 1 or 2.\n");
        scanf("%d", &choice);
    }


    if (choice == 1)
    {
        int indexesCompared = 0;
        indexComparison(darr, arrCopy, count, &indexesCompared); //compare all changed indexes and return the amount

        if (indexesCompared == 0)
        {
            printf("All elements change location in the sorted array.\n");
        }
        else
        {
            printf("%d values are in the same location in both arrays.\n", indexesCompared);
        }
    }
    else  if (choice == 2)
    {
        int targetSumToFind;
        printf("Enter in a list of numbers to use for searching.\n");
        printf("End the list with a terminal value of -999\n");
        scanf("%d", &targetSumToFind);
        int index1 = 0;
        int index2 = 0;
        while (targetSumToFind != -999)
        {            
            int sumFound = targetSum(arrCopy, count, targetSumToFind, &index1, &index2);

            if (sumFound == 1)
            {
                printf("Success! Elements at indices %d and %d add up to %d\n", index1, index2, targetSumToFind);                
            }
            else
            {
                printf("Target sum failed!\n");                
            }
            scanf("%d", &targetSumToFind);
        }
    }    

    printf("Good bye");

    free(darr);

    free(arrCopy);

    return 0;
}