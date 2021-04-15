#include <iostream>
#include <thread>

// antal element i arrayen som ska sorteras
#define MAX 20

// antal maximala tr�dar
#define THREAD_MAX 4

using namespace std;
using namespace std::chrono;

// array med storleken MAX
int array_to_sort[MAX];
int part = 0;

//Metod som byter tv� tal
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Funktion som implementerar bubblesort
void bubbleSort(int arr[], int start, int end)
{
    int i, j;
    for (i = start; i < end; i++)
        // Last i elements are already in place 
        for (j = start; j < end; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}



//Metod som skriver ut arrayen
void printArray(int arr[], int start, int end)
{
    int i;
    for (i = start; i < end; i++)
        cout << arr[i] << " ";
    cout << endl;
}


int main()
{

    //Fyll arrayen med slumpade tal mellan 0 - 99
    for (int i = 0; i < MAX; i++)
        array_to_sort[i] = rand() % 100;

    //F� total storlek av arrayen
    //int n = sizeof(array_to_sort) / sizeof(array_to_sort[0]);
    cout << "Osorted array: " << endl;
    printArray(array_to_sort, 0, MAX);

    auto start = high_resolution_clock::now();
    //Utf�r bubbelsortering med en tr�d (som inte �r huvudtr�den)
    thread t = thread(bubbleSort, array_to_sort, 0, MAX/2);
    t.join();
    thread y = thread(bubbleSort, array_to_sort, MAX / 2, MAX);
    y.join();

    cout << "Sorterad array: " << endl;
    printArray(array_to_sort, 0, MAX);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
        << duration.count() << " microseconds" << endl;

    return 0;
}


