//
//  created by Sebastian Carter
//

void spyGlass(struct shotgun *gun, int currRound) {
    printf("You pick up the shotgun and rack the slide a little, just to see that...\n");
    sleep(2);
    printf("The next round is");
    if (gun->shells[currRound] == 1) {
        printf(" LIVE!\n");
    } else {
        printf(" BLANK!\n");
    }
    sleep(2);
    clearScreen();
}

void saw(struct shotgun * gameGun, int currentShell){
    printf("You snatch the gun off of the table and \n");
    printf("sawsawsawsawsawsaw\n");
    printf("you saw the end off of the shotgun.\n");
    // gives you double damage
    gameGun->shells[currentShell] *= 2;
    sleep(2);
    clearScreen();
}


void drinkBeer(struct shotgun *gun, int *currRound) {
    printf("GLUGGLUGGLUGGLUGGLUG\n");
    printf("You snatch the gun off of the table and \n");
    sleep(2);
    printf("CHICKA CHICKA\n");
    printf("Pump the action!\n");
    sleep(2);
    if (gun->shells[*currRound] == 1) {
        printf("A live");
    } else {
        printf("A blank");
    }
    printf(" round goes flying out onto the ground!\n");
    sleep(2);
    clearScreen();
    *currRound += 1;
}


void smokeCig(int *health) {
    printf("You grab your carton of cigarrettes and pull one out\n");
    printf("CLICK, CLICK, CLI-FWOOSH\n");
    printf("You bring your lighter to the cigarette and inhale deep!\n");
    if(*health < 4){
        *health += 1;
        printf("Your health is now %d\n", *health);
    }else{
        printf("You are already at max health, no change!");
    }
    sleep(2);
    clearScreen();
}






