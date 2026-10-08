struct Test{
    double coeff1;
    double coeff2;
    double coeff3;
    enum CountSol expCountSol;
    double expSol1;
    double expSol2;
};

enum whatTypeOfSolution{
    YOUR,
    EXPECTED
};

void runAllTests();
void outputTheExpectedInConsole(enum CountSol expCountSol, double expfirstSol, double expsecondSol);
bool compareReceivedAndExpected(double firstSol, double secondSol, enum CountSol countSol, double expFirstSol, double expSecondSol, enum CountSol expCountSol);
bool runTest(double coeff1, double coeff2, double coeff3, enum CountSol expCountSol, double expSol1, double expSol2);
void printReceivedSolutionsInLog(FILE* testErrorsFile, CountSol countSol, double firstSol, double secondSol);
void printExpSolutionsinLog(FILE* testErrorsFile, CountSol expCountSol, double expSol1, double expSol2);
int runAllTestsWithLog(const char nameFileForRead[], const char nameErrorFile[]);
void printSolutionInFile(FILE* testErrorsFile, CountSol countSol, double sol1, double sol2, whatTypeOfSolution type);
