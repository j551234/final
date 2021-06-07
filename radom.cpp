#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */
#define testSize  500  /*(max size to 32768) 2^15 - 1 */

#include <random>
using namespace std;


int main() {

  std::random_device rd;
  std::default_random_engine gen = std::default_random_engine(rd());
  std::uniform_int_distribution<int> dis(1,testSize);
	
	//int time count
	time_t c_start, t_start, c_end, t_end;
	
    // Open file
    fstream myFile;
    // delete if exists
    std::remove("test.txt");
    myFile.open("test.txt", ios::app);

    srand( time(NULL));
    
    c_start = clock(); //s 
	t_start = time(NULL);  //ms
    
   std::cout << "write start";
    for(int i = 0 ; i < testSize ;i++){
    	/* from  start =1 to endSize */
        int x = dis(gen);
        // Write to the file
        myFile <<  x << endl;
    }

    // Close file
    myFile.close();
    
    c_end   = clock();
	t_end	= time(NULL);
	
	printf("The pause used %f ms by clock()\n",difftime(c_end,c_start)); 
	printf("The pause used %f s by time()\n",difftime(t_end,t_start));
    
    
    std::cout << "write end";
    return 0;
 
}
