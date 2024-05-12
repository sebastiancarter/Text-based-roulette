#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#if defined(_WIN32) || defined(__CYGWIN__)
// Windows (x86 or x64)
void clearScreen () 
 {
  system("cls");
 }
#else
// linux or unix based OS
void clearScreen () 
 {
  system("clear");
 }

void sleep(int number){
    system("sleep 2");
}

#endif
struct shotgun {
    int shells[8];
    int length;
};




