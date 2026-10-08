enum CountSol solveQuadraticEquation(double coeffs[], double* firstSol, double* secondSol){
    enum CountSol sol = DEFAULT_VALUE;
    if(isZero(coeffs[FIRST_COEFF])){  
        sol  = solveLinearEquation(coeffs[SECOND_COEFF], coeffs[THIRD_COEFF], firstSol) ;
    }
    else{
        double d = coeffs[SECOND_COEFF] * coeffs[SECOND_COEFF] - 4 * coeffs[FIRST_COEFF] * coeffs[THIRD_COEFF];
        if(d < 0){
            sol = ZERO_SOL;
        }
        else if(isZero(d)){
            *firstSol = -coeffs[SECOND_COEFF] / ( 2 * coeffs[FIRST_COEFF]);
            sol = ONE_SOL;
        }
        else{
            double disc = coeffs[SECOND_COEFF] * coeffs[SECOND_COEFF] - 4 * coeffs[FIRST_COEFF] * coeffs[THIRD_COEFF];
            assert(disc > 0);
            double sqrtD = sqrt(disc);
            *firstSol = (-coeffs[SECOND_COEFF] + sqrtD) / ( 2 * coeffs[FIRST_COEFF]);
            *secondSol = (-coeffs[SECOND_COEFF] - sqrtD) / ( 2 * coeffs[FIRST_COEFF]);
            sol = TWO_SOL;
        }
    }
    return sol;
}

enum CountSol solveLinearEquation(double firstCoeff, double secondCoeff, double* x){
    if(isZero(firstCoeff)){
        if(isZero(secondCoeff)){
            return INFINITY_SOL; 
        }
        else{
            return ZERO_SOL;
        }
    }
    else{
        *x = -secondCoeff / firstCoeff;
        return ONE_SOL;
    }
}
