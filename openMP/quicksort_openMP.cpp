#include<stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// int arr[ARRAY_MAX_SIZE];


void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element
	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

bool getFileContent(std::string fileName, std::vector<int> & vecOfStrs)
{
    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;
        return false;
    }
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(stoi(str));
    }
    //Close The File
    in.close();
    return true;
}
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		// #pragma omp task firstprivate(arr,low,pi)
		#pragma omp parallel sections
		{
			#pragma omp section
			quickSort(arr,low, pi - 1);


			// #pragma omp task firstprivate(arr, high,pi)
			#pragma omp section
			quickSort(arr, pi + 1, high);

	    }
	}
}

/* Function to print an array */
// void printArray(int arr[], int size)
// {
// 	int i;
// 	for (i=0; i < size; i++)
// 		printf("%d ", arr[i]);
// 	printf("\n");
// }

// Driver program to test above functions
int main()
{
	double start_time, run_time;
	
    std::vector<int> vecOfStr;
    // Get the contents of file in a vector
    bool result = getFileContent("radom.txt", vecOfStr);
    int arr[vecOfStr.size()];
    if(result)
    {
        // Print the vector contents
   		std::copy(vecOfStr.begin(), vecOfStr.end(), arr);
	}
       
	int n = sizeof(arr)/sizeof(arr[0]);

		//int pi = partition(arr, 0, n-1);
/*#pragma omp parallel sections
{
		#pragma omp section
		{
			quickSort(arr,0, pi - 1);
		}
		#pragma omp section
		{
			quickSort(arr, pi + 1, n-1);
		}
	}*/
	omp_set_num_threads(16);//調整thread數量
	start_time = omp_get_wtime();

	#pragma omp parallel default(none) shared(arr,n)
	 {
	 	int id = omp_get_thread_num();
	    int nthrds = omp_get_num_threads();

		printf("Thread is %d\n",id);
		#pragma omp single nowait

		quickSort(arr, 0, n-1);
	}
		run_time = omp_get_wtime() - start_time;
		printf("\n Execution time was %lf seconds\n ",run_time);
		//printf("Sorted array: \n");
		//printArray(arr, n);
	  // printf("\n");
	  // int nthrds = omp_get_num_threads();
	  // printf("Number of threads %d\n", nthrds);

	    fstream myFile;
	    myFile.open("quick_sorted_openMP.txt", ios::app);
	    for (int i = 0; i < vecOfStr.size();i++) {
	          myFile <<   vecOfStr.at(i) << endl;
	    }
	 
	   myFile.close();
	           
		return 0;
}