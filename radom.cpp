#include <iostream>
#include <fstream>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */
using namespace std;


int main() {
    // Open file
    fstream myFile;
    myFile.open("test.txt", ios::app);

    srand( time(NULL));
 
    for(int i = 0 ; i < 100000 ;i++){
           int x = rand() % (100000 - 1 + 1) + 1;
        myFile <<  x << endl;
    }
    // Write to the file
   
    // Close file
    myFile.close();

    return 0;
}
