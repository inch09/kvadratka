void runAllTests(){
    printf("Tests:\n");

    FILE* textTests = fopen("textTests.txt", "r"); 
    assert(textTests != NULL);

    double coeff1 = 0;
    double coeff2 = 0;
    double coeff3 = 0;
    int expCountSol = 0;
    double  expSol1 = 0;
    double  expSol2 = 0;

    while(fscanf(textTests, "%lf %lf %lf %d %lf %lf", &coeff1, &coeff2, &coeff3, &expCountSol, &expSol1, &expSol2) == 6){
        CountSol expCountSol1 = DEFAULT_VALUE;

        switch(expCountSol){
            case 0 : expCountSol1 = ZERO_SOL;
                break;
            case 1 : expCountSol1 = ONE_SOL;
                break;
            case 2 : expCountSol1 = TWO_SOL;
                break; 
            case 3 : expCountSol1 = INFINITY_SOL;
                break;
            default:
                break;
        }

        assert(expCountSol1 != INCORRECT_ENTER);
        assert(expCountSol1 != DEFAULT_VALUE);

        runTest(coeff1, coeff2, coeff3, expCountSol1, expSol1, expSol2);
    }
    fclose(textTests);
}

bool runTest(double coeff1, double coeff2, double coeff3, enum CountSol expCountSol, double expSol1, double expSol2){
    double coeffs[3] = {coeff1, coeff2, coeff3};
    double firstSol = 0, secondSol = 0;
    enum CountSol countSol = solveQuadraticEquation(coeffs, &firstSol, &secondSol);

    bool compare = compareReceivedAndExpected(firstSol, secondSol, countSol, expSol1, expSol2, expCountSol);
    if(compare){
        printf("Yes\n");
        return true;
    }
    else{
        printf("\n");
        printf("Test FAILED!!!!!\n");
        printf("%lg, %lg, %lg\n", coeff1, coeff2, coeff3);
        outputTheExpectedInConsole(expCountSol, expSol1, expSol2);
        printf("Your:\n");
        printAnswer(countSol, firstSol, secondSol);
        printf("\n");
        return false;
    }
}

void outputTheExpectedInConsole(enum CountSol expCountSol, double expfirstSol, double expsecondSol){
    assert(expCountSol != INCORRECT_ENTER);
    assert(expCountSol != DEFAULT_VALUE);

    switch(expCountSol){
    case ZERO_SOL : printf("Expected:\nno solutions\n");
        break;
    case ONE_SOL : printf("Expected:\none solve: %lf\n", expfirstSol);
        break;
    case TWO_SOL : printf("Expected:\ntwo solves: %lf , %lf\n", expfirstSol, expsecondSol);
        break;
    case INFINITY_SOL : printf("Expected:\ninfinitely many solutions\n");
        break;
    case INCORRECT_ENTER :
    case DEFAULT_VALUE :
    default:
        break;
    }
}

bool compareReceivedAndExpected(double firstSol, double secondSol, enum CountSol countSol, double expFirstSol, double expSecondSol, enum CountSol expCountSol){
    assert(expCountSol != INCORRECT_ENTER);
    assert(expCountSol != DEFAULT_VALUE);
    assert(countSol != INCORRECT_ENTER);
    assert(countSol != DEFAULT_VALUE);

    switch(expCountSol){
    case ZERO_SOL :
        return (countSol == expCountSol);   
    case ONE_SOL :
        if(countSol == expCountSol){
            return (isEqual(firstSol, expFirstSol));
        }
        else{
            return false;
        }
    case TWO_SOL :
        if(countSol == expCountSol){
            return((isEqual(expFirstSol, firstSol) && isEqual(expSecondSol, secondSol)) || (isEqual(expFirstSol, secondSol) && isEqual(expSecondSol, firstSol)));
        }
        else{
            return false;
        }
    case INFINITY_SOL : 
        return (countSol == expCountSol);
    case INCORRECT_ENTER :
    case DEFAULT_VALUE :
    default:
        return false;
    }
}

int runAllTestsWithLog(const char nameFileForRead[],const char nameErrorFile[]){ 
    FILE* testErrorsFile = fopen(nameErrorFile, "w");
    FILE* textTests = fopen(nameFileForRead, "r");
    assert(textTests != NULL);
    assert(testErrorsFile != NULL);    

    double coeff1 = 0, coeff2 = 0, coeff3 = 0;
    double  expSol1 = 0, expSol2 = 0;
    double firstSol = 0, secondSol = 0;
    int expCountSol = 0;
    while(fscanf(textTests, "%lf %lf %lf %d %lf %lf", &coeff1, &coeff2, &coeff3, &expCountSol, &expSol1, &expSol2) == 6){
        CountSol expCountSol1 = DEFAULT_VALUE;

        switch(expCountSol){
            case 0 : expCountSol1 = ZERO_SOL;
                break;
            case 1 : expCountSol1 = ONE_SOL;
                break;
            case 2 : expCountSol1 = TWO_SOL;
                break; 
            case 3 : expCountSol1 = INFINITY_SOL; 
                break;
            default:;
        }

        assert(expCountSol1 != INCORRECT_ENTER);
        assert(expCountSol1 != DEFAULT_VALUE);

        if(runTest(coeff1, coeff2, coeff3, expCountSol1, expSol1, expSol2)){
            continue;
        }

        double coeffs[3] = {coeff1, coeff2, coeff3};
        enum CountSol countSol = solveQuadraticEquation(coeffs, &firstSol, &secondSol);
        fprintf(testErrorsFile, "\n");
        fprintf(testErrorsFile, "Test FAILED!!!!!\n");
        fprintf(testErrorsFile, "coeffs: %lg, %lg, %lg\n", coeff1, coeff2, coeff3);
        printSolutionInFile(testErrorsFile, expCountSol1, expSol1, expSol2, EXPECTED);
        printSolutionInFile(testErrorsFile, countSol, firstSol, secondSol, YOUR);
        fprintf(testErrorsFile, "\n");
    }

    fclose(testErrorsFile);
    fclose(textTests);
    
    return 0;
}

void printSolutionInFile(FILE* testErrorsFile, CountSol countSol, double sol1, double sol2, whatTypeOfSolution type){
    if(type == YOUR){
        fprintf(testErrorsFile, "Your:\n");
    }
    else{
        fprintf(testErrorsFile, "Expected:\n");
    }

    assert(type == YOUR || type == EXPECTED);
    assert(countSol != DEFAULT_VALUE);

    switch(countSol){
    case ZERO_SOL : fprintf(testErrorsFile, "No solutions\n");
        break;
    case ONE_SOL : fprintf(testErrorsFile, "One solve: %lg\n", sol1);
        break;
    case TWO_SOL : fprintf(testErrorsFile, "Two solves: %lg , %lg\n", sol1, sol2);
        break;
    case INFINITY_SOL : fprintf(testErrorsFile, "Infinitely many solutions\n");
        break;
    case INCORRECT_ENTER : fprintf(testErrorsFile, "Invalid data\n");
        break;
    case DEFAULT_VALUE:
        break;
    default:
        break;
    }

}

