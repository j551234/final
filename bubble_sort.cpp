#include <iostream>

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

int main()
{

    int nums[8] = { 24, 17, 39, 2, 13, 26, 5, 10 };
    doBubbleSort(nums, 8);

    for (int i = 0; i < 8;i++) {
        cout << nums[i];
        cout << ",";
    }
    cout << "\n";
    cout << "Hello World";

    return 0;
}