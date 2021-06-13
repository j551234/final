// C++ code
#include <assert.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>


#define TASK_SIZE 100
#define THREAD_SIZE 2
const int Max = 500000;
using namespace std;

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

//Merging 2 sorted subarrays into one tmp array
void merge(int * X, int n, int * tmp) {
   int i = 0;
   int j = n/2;
   int ti = 0;
	//i will iterate till first  half anf J will iterate for 2nd half of array
   while (i<n/2 && j<n) {
      if (X[i] < X[j]) {
         tmp[ti] = X[i];
         ti++; i++;
      } else {
         tmp[ti] = X[j];
         ti++; 
	 j++;
      }
   }
   while (i<n/2) { /* finish up lower half */
      tmp[ti] = X[i];
	ti++;
	i++;
   }
      while (j<n) { /* finish up upper half */
         tmp[ti] = X[j];
         ti++; 
	 j++;
   }
	//Copy sorted array tmp back to  X (Original array)
   memcpy(X, tmp, n*sizeof(int));

} // end of merge()

void mergesort(int * X, int n, int * tmp)
{
   if (n < 2) return;

   #pragma omp task shared(X) if (n > TASK_SIZE)
   mergesort(X, n/2, tmp);

   #pragma omp task shared(X) if (n > TASK_SIZE)
   mergesort(X+(n/2), n-(n/2), tmp + n/2);

   #pragma omp taskwait
   merge(X, n, tmp);
}

int isSorted(int *a, int size){
   for(int i = 0; i < size - 1; i++)
      if(a[i] > a[i + 1])
        return 0;
   return 1;
}


int main() {
	
    time_t c_start, t_start, c_end, t_end;

	double start, stop;


    std::vector<int> vecOfStr;
    // Get the contents of file in a vector
    bool result = getFileContent("test.txt", vecOfStr);
    int N = vecOfStr.size();
	int*X = (int*) malloc(N * sizeof(int));
    int*tmp = (int*) malloc(N * sizeof(int));

    	if(!X || !tmp)
    	{ 
           if(X) free(X);
	   if(tmp) free(tmp);
           return (EXIT_FAILURE);
    	}

 
    if(result)
    {
    
        // Print the vector contents
   		std::copy(vecOfStr.begin(), vecOfStr.end(), X);
	}

      omp_set_dynamic(0);     
      omp_set_num_threads(THREAD_SIZE);//調整thread數量/調整thread數量

    start = omp_get_wtime();
    #pragma omp parallel
        {
            #pragma omp single
            mergesort(X, N, tmp);
        }
    stop = omp_get_wtime();

    printf("\nTime: %g\n",stop-start);




    assert(1 == isSorted(X, N));


    fstream myFile;
    std::remove("merge_sorted_openMP.txt");
    myFile.open("merge_sorted_openMP.txt", ios::app);
    for (int i = 0; i < vecOfStr.size();i++) {
          myFile <<   X[i] << endl;
    }

 
   myFile.close();

    return 0;
}
