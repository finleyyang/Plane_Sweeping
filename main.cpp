#include "CalculateRT.h"
#include "PlaneSweeping.h"
#include <chrono>

int main() {
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    CalculateRT CRT;
    CRT.run();
    PlaneSweeping PS;
    PS.LoadInformation(CRT.Getleft(), CRT.Getright(), CRT.GetK(), CRT.GetR(), CRT.Gett());
    //std::cout<<CRT.GetR()<<std::endl;
    PS.EstimateDepth();
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
    std::cout<<time_used.count()<<" second."<<std::endl;

}
