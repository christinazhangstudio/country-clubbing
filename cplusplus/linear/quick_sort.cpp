#include <iostream>

using namespace std;

int partition(int *array, int low, int high) {
    int pivot = array[low]; // pivot initially 0
    int i = low;
    int j = high + 1;

    // [p/i] [] [] [] [] [] [] (j)
    // [p] [i] [] [] [] [j]     move i up while it is less than pivot or equal value
    // [p] [] [i] [] [j] []     when i is no longer smaller than pivot, and when j is no longer bigger than pivot, swap the two

    // [p] [] [j_val] [] [i_val] []     using the j index as above, we sort the partitions of 0-j, and (j+1)-(len-1) this way 

    // [j_val] [] [p_val] [] [*] []     swap the first value of partition with j value (which we know to be the smallest)
                                       // * is our new pivot on the next call      


    while(i < j) {
        do{
            i++;
        }while(array[i] <= pivot);

        do{
            j--;
        }while(array[j] > pivot);

        if(i < j) {
            int tmp=array[i];
            array[i] = array[j];
            array[j]=tmp;   // allows us to break the two while loops
        }
    }

    // at the very end, swap the first value of this partition and j, which we know to be smallest of this partition
    int tmp=array[low];
    array[low] = array[j];
    array[j]=tmp;

    return j;
}

void quick(int *array, int low, int high) {
    if(high > low) {
        int cnst = partition(array, low, high);
        quick(array, low, cnst - 1);
        quick(array, cnst + 1, high);
    }
}

int main() {
    int array[] = {5, 1, 4, 2, 3, 9, 0};

    quick(array, 0, (sizeof(array)/sizeof(int)) - 1);
    for(int a : array) {
        cout << a;
    }
    cout << endl;
}