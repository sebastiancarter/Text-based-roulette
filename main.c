#include <stdlib.h>
#include <time.h>
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
};

void loadGun(struct shotgun *gun){
    int loader, arrSize, live, blank;
    // loading the first 2 shells (should always have at least 2 shells) 
    gun->shells[0] = rand() % 2;
    gun->shells[1] = rand() % 2;
    arrSize = 2;

    live = 0;
    blank = 0;
    if(gun->shells[0] == 1){
        live += 1;
    }else{
        blank += 1;
    }
    if(gun->shells[1] == 1){
        live += 1;
    }else{
        blank += 1;
    }
        


    // initializing loader
    loader = 0;
    while(loader != 2){
        loader = rand() % 3;
        if(loader == 2){
            continue;
        }else if(arrSize == 8){
            break;
        }else{
            if(loader == 1){
                live += 1;
            }else{
                blank += 1;
            }
            gun->shells[arrSize] = loader;
            arrSize += 1;
        }
    }
    // if no live rounds, add 1 in a random spot and take away a blank or vice versa for no blanks
    if(live < 1){
        live += 1;
        blank -= 1;
        gun->shells[rand()%arrSize] = 1;
    }else if(blank < 1){
        live -= 1;
        blank += 1;
        gun->shells[rand()%arrSize] = 0;
    }



    gun->length = arrSize;
    printf("%d live rounds loaded\n", live);
    printf("%d blank rounds loaded\n", blank);
    sleep(2);
}



int main(){
    int playerLife, enemyLife, currShell, input, dealerChoice;
    playerLife = 4;
    enemyLife = 4;
    struct shotgun gameGun;
    
    


    srand(time(NULL));
    while(playerLife > 0 && enemyLife > 0){
        currShell = 0;
        loadGun(&gameGun);
        while(playerLife > 0 && enemyLife > 0 && gameGun.length > currShell){
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
                        printf("BANG! The shotgun blows a massive hole in the dealers face\n");
                    }else{
                        printf("CLICK...\n");
                    }
                    break;
                }
                case 2:{
                    playerLife -= gameGun.shells[currShell];
                    currShell += 1;
                    if(gameGun.shells[currShell-1] == 1){
                        printf("You stare down the barrel of the gun and BANG! You see a flash and then nothing...\n");
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
            // DEALER TURN
            // TODO: make the dealer skip your turn if he manages to not kill himself
            printf("the dealer picks up the gun...\n");
            dealerChoice = rand() % 2;
            sleep(2);
            clearScreen();
            switch(dealerChoice){
                case 0:{
                    printf("and turns it on you!\n");
                    sleep(2);
                    clearScreen();
                    printf("You watch, paralyzed in fear as his arms tense up and...\n");
                    sleep(4);
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
                    printf("and turns it on himself!\n");
                    sleep(2);
                    clearScreen();
                    printf("You watch, paralyzed in fear as his arms tense up and...\n");
                    sleep(4);
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
        sleep(2); 
        clearScreen();
        printf("ROUND OVER\n");
        sleep(2);
        clearScreen();
    }
    if(playerLife < 1){
        printf("YOU LOSE\n");
    }else{
        printf("YOU WIN!\n");
    }
    printf("Thank you for playing!");
    return EXIT_SUCCESS;

}

