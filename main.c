#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#if defined(_WIN32) || defined(__CYGWIN__)
    // Windows (x86 or x64)
    #include <windows.h>
    void clearScreen(){
        system("cls");
    }
#else
    #include <unistd.h>
    void clearScreen(){
        system("clear");
    }
#endif





struct shotgun{
    int shells[8];
    int length;
    bool loaded;
};

void loadGun(struct shotgun *gun){
    int loader, arrSize;
    // loading the first 2 shells (should always have at least 2 shells) 
    gun->shells[0] = rand() % 2;
    gun->shells[1] = rand() % 2;
    arrSize = 2;
    // initializing loader
    loader = 0;
    while(loader != 2){
        loader = rand() % 3;
        if(loader == 2){
            continue;
        }else if(arrSize == 8){
            break;
        }else{
            printf("loader is %d\n", loader);
            gun->shells[arrSize] = loader;
            arrSize += 1;
        }
    }

    gun->length = arrSize;
    gun->loaded = true;
}



int main(){
    int playerLife, enemyLife, currShell, input, dealerChoice;
    playerLife = 4;
    enemyLife = 4;
    currShell = 0;
    struct shotgun gameGun;
    
    


    srand(time(NULL));

    loadGun(&gameGun);
    while(playerLife != 0 && gameGun.length > currShell){
        sleep(2);
        clearScreen();
        // PLAYER TURN
        // resetting input
        input = 0;
        while(input > 2 || input < 1){
            printf("there are %d shells\n", (gameGun.length - currShell));
            printf("you have %d life\n", playerLife);
            printf("the dealer has %d life\n", enemyLife);
            printf("what would you like to do?\n");
            printf("1. shoot the enemy\n");
            printf("2. shoot yourself\n");
            scanf("%d", &input);
        } 
        clearScreen();
        printf("you nervously squeeze the trigger...\n");
        sleep(2);
        switch(input){
            case 1:{
                enemyLife -= gameGun.shells[currShell];
                currShell += 1;
                if(gameGun.shells[currShell-1] == 1){
                    printf("the shotgun blows a massive hole in the dealers face, you stand in horror at what you've done\n");
                }else{
                    printf("CLICK...\n");
                }
                break;
            }
            case 2:{
                playerLife -= gameGun.shells[currShell];
                currShell += 1;
                if(gameGun.shells[currShell-1] == 1){
                    printf("you stare down the barrel of the gun and BANG! you see a flash and then nothing...\n");
                }else{
                    printf("CLICK...\n");
                    continue;
                }
                break;
            }   
            default:
                continue;
        }

        // handling if you kill yourself or use all the shells
        if(currShell == gameGun.length || playerLife == 0){
            break;
        }
        sleep(2);

        clearScreen();
        printf("the dealer picks up the gun...\n");
        dealerChoice = rand() % 2;
        switch(dealerChoice){
            case 0:{
                printf("and turns it on you!\nYou watch, paralyzed in fear as his arms tense up and...\n");
                sleep(2);
                clearScreen();
                playerLife -= gameGun.shells[currShell];
                currShell += 1;
                if(gameGun.shells[currShell-1] == 1){
                    printf("BANG! you see a flash, and DIE!\n");
                }else{
                    printf("CLICK...\n");
                }
                break;
            }
            case 1:{
                printf("and turns it on himself!\nYou watch, paralyzed in fear as his arms tense up and...\n");
                sleep(2);
                clearScreen();
                enemyLife -= gameGun.shells[currShell];
                currShell += 1;
                if(gameGun.shells[currShell-1] == 1){
                    printf("BANG! you see a flash, and see his brains fly all over the room!\n");
                }else{
                    printf("CLICK...\n");
                }
                break;
            }

        }
    }

    printf("ROUND OVER\nThank you for playing!");
    return EXIT_SUCCESS;



}






