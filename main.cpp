#include <iostream>

using namespace std;
// G++ command used to compile main.cpp --> g++ main.cpp -o main
int main()
{
    printf("Program started...\r\n");

    for (int i = 0; i < 5; i++)
    {
        printf("Program iteration [ %d ] \r\n", i);
    }

    printf("Program ended...\r\n");

    return 0;
}