#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;


void doBubbleSort(int nums[], int length) {

    int a, b, temp;
    for (int a = 0;a < length - 1; a++) {
        for (int b = 0; b < length - 1 - a; b++) {
            if (nums[b] > nums[b + 1]) {
                temp = nums[b];
                nums[b] = nums[b + 1];
                nums[b + 1] = temp;
            }

        }

    }



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


int main()
{

time_t c_start, t_start, c_end, t_end;
    std::vector<int> vecOfStr;
    // Get the contents of file in a vector
    bool result = getFileContent("radom.txt", vecOfStr);
    int array[vecOfStr.size()];
 
    if(result)
    {
    
        // Print the vector contents
   		std::copy(vecOfStr.begin(), vecOfStr.end(), array);
	}
	//s 
 	 c_start = clock(); 
	 //ms
	t_start = time(NULL); 
	
    doBubbleSort(array, vecOfStr.size());
    
    c_end   = clock();
	t_end	= time(NULL);
	
	printf("The pause used %f ms by clock()\n",difftime(c_end,c_start)); 
	printf("The pause used %f s by time()\n",difftime(t_end,t_start));

//    for (int i = 0; i < vecOfStr.size();i++) {
//        cout << arr[i];
//          cout << "\n";
//    }

//write out to fuke

    fstream myFile;
    myFile.open("bubble_sorted.txt", ios::app);
    for (int i = 0; i < vecOfStr.size();i++) {
          myFile <<   array[i] << endl;
    }
 
   myFile.close();
    return 0;
}


