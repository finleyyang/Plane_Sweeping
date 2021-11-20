#include "CalculateRT.h"
#include "PlaneSweeping.h"

int main() {
    CalculateRT CRT;
    CRT.run();
    PlaneSweeping PS;
    PS.LoadInformation(CRT.Getleft(), CRT.Getright(), CRT.GetK(), CRT.GetR(), CRT.Gett());
    PS.EstimateDepth();
}
