#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    int arr[] = {1,2,3,4,5};

    cout <<*cbegin(arr)+3 <<endl;
    return 0;
}