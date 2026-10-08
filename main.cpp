#include <TXLib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "globalFunc.h"
#include "testFunc.h"
#include "userFunc.h"

#include "globalFunctions.cpp"
#include "testFuncFile.cpp"
#include "userFunctions.cpp"
#include "functionsForSolvingEq.cpp"
#include "graphics.cpp"

int main(int argc, char* argv[]){
    Mode selectedMode = programStartupModeSelection(argc, argv);

    switch(selectedMode){
        case ERRORSINLOG: runAllTestsWithLog("textTests.txt", "testErrors.log");
            break;
        case ERRORSINCONSOLE: runAllTests();
            break;
        case USERMODE: userMode();
            break;
        case GRAPHIC: graphicMode();
            break;
        default:
            break;
    }

    return 0;
}














































//     FILE* fp;
//     fp = fopen("textTests.txt", "r");
//     double coeff1 = 0;
//     double coeff2 = 0;
//     double coeff3 = 0;
//     int expCountSol = 0;
//     double  expSol1 = 0;
//     double  expSol2 = 0;
//     while(fscanf(fp,"%lf %lf %lf %d %lf %lf", &coeff1, &coeff2, &coeff3, &expCountSol, &expSol1, &expSol2) == 6){
//         CountSol expCountSol1 = DEFAULT_VALUE;
//         switch(expCountSol){
//             case 0 : expCountSol1 = ZERO_SOL;
//             case 1 : expCountSol1 = ONE_SOL;
//             case 2 : expCountSol1 = TWO_SOL;
//             case 3 : expCountSol1 = INFINITY_SOL;
//             default:
//         runTest(coeff1, coeff2, coeff3, expCountSol1, expSol1, expSol2);
//         }

//         // printf("%lg\n", coeff1);
//         // printf("%lg\n", coeff2);
//         // printf("%lg\n", coeff3);
//         // printf("%d\n", expCountSol);
//         // printf("\n");
//     }


//     // while(ch != EOF){
//     //     if(ch == ' '){

//     //         continue;
//     //     }
//     //     if(ch >= '0' && ch <='9'){
//     //     printf("%c\n", ch);
//     //     }
//     //     ch = getc(fp);
//     // }