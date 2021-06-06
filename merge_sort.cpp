// C++ code
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>  
const int Max = 10000000;
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

void Merge(std::vector<int> &array, int front, int mid, int end){

    // 利用 std::vector 的constructor, 
    // 把array[front]~array[mid]放進 LeftSub[]
    // 把array[mid+1]~array[end]放進 RightSub[]
    std::vector<int> LeftSub(array.begin()+front, array.begin()+mid+1),
                     RightSub(array.begin()+mid+1, array.begin()+end+1);

    LeftSub.insert(LeftSub.end(), Max);      // 在LeftSub[]尾端加入值為 Max 的元素
    RightSub.insert(RightSub.end(), Max);    // 在RightSub[]尾端加入值為 Max 的元素

    int idxLeft = 0, idxRight = 0;

    for (int i = front; i <= end; i++) {

        if (LeftSub[idxLeft] <= RightSub[idxRight] ) {
            array[i] = LeftSub[idxLeft];
            idxLeft++;
        }
        else{
            array[i] = RightSub[idxRight];
            idxRight++;
        }
    }
}

void MergeSort(std::vector<int> &array, int front, int end){
                                         // front與end為矩陣範圍
    if (front < end) {                   // 表示目前的矩陣範圍是有效的
        int mid = (front+end)/2;         // mid即是將矩陣對半分的index
        MergeSort(array, front, mid);    // 繼續divide矩陣的前半段subarray
        MergeSort(array, mid+1, end);    // 繼續divide矩陣的後半段subarray
        Merge(array, front, mid, end);   // 將兩個subarray做比較, 並合併出排序後的矩陣
    }
}



int main() {
	
	
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
    
 
	c_start = clock(); //s 
	
	
	t_start = time(NULL);  //ms


    MergeSort(vecOfStr, 0, vecOfStr.size());
    
   	c_end   = clock();
	t_end	= time(NULL);

	printf("The pause used %f ms by clock()\n",difftime(c_end,c_start)); 
	printf("The pause used %f s by time()\n",difftime(t_end,t_start));

//	for(int i=0 ;i <vecOfStr.size();i++){
//		       cout << vecOfStr.at(i);
//	         cout << "\n";
//	}


//write out to fuke

    fstream myFile;
    myFile.open("merge_sorted.txt", ios::app);
    for (int i = 0; i < vecOfStr.size();i++) {
          myFile <<   vecOfStr.at(i) << endl;
    }
 
   myFile.close();


    return 0;
}
