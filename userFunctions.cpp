Mode programStartupModeSelection(int argCount, char* argValue[]){
    if(argCount > 1){
        if(strcmp(argValue[1], "log") == 0){
            return ERRORSINLOG;
        }
        else if(strcmp(argValue[1], "console") == 0){
            return ERRORSINCONSOLE;
        }
        else if(strcmp(argValue[1], "graphic") == 0){
            return GRAPHIC;
        }
    }
    return USERMODE;
}

void userMode(){
    printTitle();
    while(true){
        bool Enter = enterCoeffsAndGetAnswer();
        if(!Enter){
            printf("Enter the coefficients again:\n");
            continue;
        } 
        else{
            printf("Would you like to solve another one?(yes/no)\n");
            clearTheBuffer();
            bool more = handleAChoice();
            if(!more){
                break;
            }
        }
    }
}

void printTitle(){
    printf("Solving a quadratic equation\n");
    printf("Enter the coefficients:\n");
}

enum CountSol setCoeffs(double coeffs[]){
    int res = scanf("%lf %lf %lf", coeffs, coeffs + 1, coeffs + 2);
    if(res == 3){
        return DEFAULT_VALUE;
    }
    return INCORRECT_ENTER;
}

bool enterCoeffsAndGetAnswer(){
    double coeffs[] = {0, 0, 0};
    double firstSol = 0;
    double secondSol = 0;
    enum CountSol Enter = setCoeffs(coeffs);
    if(Enter != INCORRECT_ENTER){
        enum CountSol receivedCountSol = solveQuadraticEquation(coeffs, &firstSol, &secondSol);
        printAnswer(receivedCountSol, firstSol, secondSol);
        return true;
    }
    else{
        printAnswer(INCORRECT_ENTER, firstSol, secondSol);
        clearTheBuffer();
        return false;
    }
}

bool handleAChoice(){
    char reply[10] = {};
    scanf("%s",reply); 
    if( strcmp(reply, "yes") == 0 || strcmp(reply, "Yes") == 0){ 
        printf("Well, then introduce the coefficients again\n");
        return true;
    }
    else if(strcmp(reply, "no") == 0 || strcmp(reply, "No") == 0){ 
        printf("Thank you for use!");//
        return false;
    }
    else{
        printf("Re-entry error!!!!!");
        return false;
    }
}

void clearTheBuffer(){
    int bufer = getchar();
    while (bufer != '\n' && bufer != EOF){
        bufer = getchar();
    }
}


