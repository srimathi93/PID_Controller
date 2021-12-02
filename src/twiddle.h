#include "PID.h"




class Twiddle {
  
 private:
  double err;
  int param_index;
  std::vector<double>p{};
  std::vector<double>dp{};
  //int iter = 0;
  double best_error;
   //double err = 0;
    double iter = 0;
  double sum = 0;

  double avg_err = 0;
  
 public:
  double Sum(std::vector<double> dp);
  void Error_Calc(double cte);
  void PerfTwiddle(PID& pid);
  void Increment_Steps();
  bool count_reached = false;
  


  
  
};
  

