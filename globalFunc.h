enum Mode{
    USERMODE,
    ERRORSINLOG,
    ERRORSINCONSOLE,
    GRAPHIC
};

enum CountSol {
    ZERO_SOL = 0,
    ONE_SOL = 1,
    TWO_SOL = 2,
    INFINITY_SOL = 3,
    INCORRECT_ENTER = 4,
    DEFAULT_VALUE = 5
};

enum Coefficients{
    FIRST_COEFF = 0,
    SECOND_COEFF = 1,
    THIRD_COEFF = 2
};

bool isEqual(double a, double b);
bool isZero(double a);
enum CountSol solveLinearEquation(double firstCoeff, double secondCoeff, double* x);
enum CountSol solveQuadraticEquation(double coeffs[], double* firstSol,double* secondSol);
void printAnswer(enum CountSol sol,double firstSol,double secondSol);
