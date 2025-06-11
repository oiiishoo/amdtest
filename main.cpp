#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include<thread>
volatile bool locked = 1;
alignas(64) size_t p1 = 0;
alignas(64) size_t p2 = 0; 
volatile int shifted = 0;
void task(
    //bool& locked,size_t& p1
) {
    SetThreadAffinityMask(GetCurrentThread(), 1<<(shifted+5));
    while (locked) {
        p1++;
    }
}
void task2(//bool& locked,size_t& p2
) {
    SetThreadAffinityMask(GetCurrentThread(), 1<<4);
    while (locked) {
        p2++;
    }
}
int main() {
    for (size_t i = 0; i < 2; i++)
    {

        if (i) shifted = 1;
        std::thread d(task
            
        ), v(task2
            )
            ;
        Sleep(1000);
        locked = 0;
        if (i)std::cout<<"second core test\n"; else std::cout<<"single core test\n";
        std::cout << "timed both " << p1 << " " << p2 << "\n";

        d.join();
        v.join();
        locked = 1;
        if (shifted)break;
        Sleep(1000);
        p1 =0;
        p2 = 0;
    }
}
