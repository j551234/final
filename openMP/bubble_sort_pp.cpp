#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define THREAD_SIZE 8

void swap();
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


void swap(int *num1, int *num2)
{

	int temp = *num1;
	*num1 =  *num2;
	*num2 = temp;
}

int isSorted(int *a, int size){
   for(int i = 0; i < size - 1; i++)
      if(a[i] > a[i + 1])
        return 0;
   return 1;
}



int main () {

	std::vector<int> vecOfStr;
    // Get the contents of file in a vector
    bool result = getFileContent("test.txt", vecOfStr);
    int arr[vecOfStr.size()];

    if(result)
    {
        // Print the vector contents
   		std::copy(vecOfStr.begin(), vecOfStr.end(), arr);
	}

	int N = vecOfStr.size();
	int i=0, j=0; 
	int first;
	double start,end;
	omp_set_num_threads(THREAD_SIZE);//調整thread數量

	start=omp_get_wtime();
	for( i = 0; i < N; i++ )
	{
		first = i % 2; 
		#pragma omp parallel for default(none),shared(arr,first,N)
		for( j = first; j < N-1; j += 2 )
		{

			if( arr[ j ] > arr[ j+1 ] )
			{
				swap( &arr[ j ], &arr[ j+1 ] );
			}
		}

	}
    end=omp_get_wtime();
		printf("Thread is %d\n",THREAD_SIZE);
printf("\n------------------------- Time Parallel= %f \n",(end-start));


    assert(1 == isSorted(arr, N));

    fstream myFile;
    myFile.open("bubble_sorted_OpenMP.txt", ios::app);
    for (int i = 0; i < N;i++) {
          myFile <<   arr[i] << endl;
    }
 
   myFile.close();
return 0 ;
}