bool isZero(double a){
    return isEqual(a, 0);
}

bool isEqual(double a, double b){
    double EPSILON = 0.001;
    return (fabs((a - b)) < EPSILON);
}

void printAnswer(enum CountSol sol,double firstSol,double secondSol){
    assert(sol != DEFAULT_VALUE);
    
    switch(sol){
    case ZERO_SOL : printf("No solutions\n");
        break;
    case ONE_SOL : printf("One solve: %lg\n", firstSol);
        break;
    case TWO_SOL : printf("Two solves: %lg , %lg\n", firstSol, secondSol);
        break;
    case INFINITY_SOL : printf("Infinitely many solutions\n");
        break;
    case INCORRECT_ENTER : printf("Invalid data\n");
        break;
    case DEFAULT_VALUE:
        break;
    default:
        break;
    }
}