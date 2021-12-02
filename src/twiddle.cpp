#include <iostream>
#include <vector>
#include "twiddle.h"


static constexpr int N = 100;
static constexpr int N_max = 300;





double Twiddle::Sum(std::vector<double> dp)
{
            double step = 0;
//Twiddle implementation
            
          
          for(int i=0; i<3; i++)
          {
            sum += dp[i];
          }

  return sum;
}
          
          //best_err = cte;
void Twiddle::Increment_Steps()
{
    step++;
}
          
         
void Twiddle::Error_Calc(double cte)
{
          if (step > N)
          {
          err += pow(cte,2);
          }

          if (step > N_max)
          {
            avg_err = err / (step-N);
            count_reached = true;
          }
}

void Twiddle::PerfTwiddle(PID &pid)
{

          p = {pid.Kp, pid.Ki, pid.Kd};
          dp = {0.05, 0.001, 0.05};
  double tol = 0.0001;
          //best_err = avg_err;
          while (Sum(dp) > tol)
          {
            for (int i = 0; i<3; i++)
            {
              p[i]+=dp[i];
              pid.Init(p[0], p[1],p[2]);
              i++;
              //break;
              
              
              if (avg_err < best_err)
              {
                best_err = avg_err;
                dp[i] *=1.1;
                p[i] += dp[i];
                i++;
                iter +=1;
                //break;
              }
              else
              {
                p[i] -= 2*dp[i];
                
                if (avg_err < best_err)
                {
                  best_err = avg_err;
                    dp[i]*=1.1;
                }
                else
                {
                  p[i] += dp[i];
                  dp[i] *= 0.9;
                }
                i++;
                iter +=1;
                p[i] += dp[i];
                break;
                
              }
                
              iter +=1;
            }
          }
         
          
          }
