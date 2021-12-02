#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"
#include <numeric>

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;

  PID pid;
  PID pid_speed;
  pid.Init(0.5,1,1);
  pid_speed.Init(1,1,1);
  /**
   * TODO: Initialize the pid variable.
   */
  
  double cte;

  //double p_error;
  //double i_error;
  //double d_error;
  

  //double N = 100;

  h.onMessage([&pid, &pid_speed](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));
      double err = 0;
      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           
           The simulator will provide you the cross track error (CTE) and the velocity (mph) in order to compute the appropriate steering angle
           */
          //************* Begin **************//
          
          //P Controller

          /*double it = 0;
          //double Kp = 1;
  		  //double Ki = 1;
  		  //double Kd = 1;
          double p[3] = {0,0,0};
  		  double dp[3] = {1,1,1};
          double N = 100;
  		  //double best_error = 0;
  		  double tol = 0.6;
          err += pow(cte,2);
          double best_error = err/N;
          */
          
          pid.UpdateError(cte);
          steer_value += pid.TotalError();
          /*double des_speed = 40;
          double speed_err = speed - des_speed;
          pid_speed.UpdateError(speed_err);
          double throttle_value = pid_speed.TotalError();
          if (throttle_value < -1)
          {
            throttle_value = -1;
          }
          if (throttle_value > 1)
          {
            throttle_value = 1;
          }
*/
          
          
            //Twiddle implementation
         /* double sum = std::accumulate(dp, dp + 3, sum);
          while (std::accumulate(dp, dp + 3, sum) > tol)
          {
            std::cout << "Sum" << std::accumulate(dp, dp + 3, sum) << " Best error: " << best_error 
                    << std::endl;
            for (int i = 0; i <= 3 ; i++)
            {
              p[i] += dp[i];
              pid.UpdateError(err);
              Kp = p[0];
              Ki = p[1];
              Kd = p[2];
              steer_value += pid.TotalError();
              
              if (err < best_error)
              {
                best_error = err;
                dp[i]*=1.1;
              }
              else
              {
                	p[i] -= 2*dp[i];
                	pid.UpdateError(err);
                    Kp = p[0];
                    Ki = p[1];
                    Kd = p[2];
                 	steer_value += pid.TotalError();
 
                	if (err < best_error)
                	{
                  	best_error = err;
                  	dp[i] *=1.1;
                	}
                	else
                	{
                  	p[i] +=dp[i];
                  	dp[i] *=0.9;
                	}
                
                
              }
            }
            it +=1;
          }

       pid.UpdateError(err);
                     Kp = p[0];
                     Ki = p[1];
                     Kd = p[2];    
          steer_value += pid.TotalError();
          
          */
          
          
          
          //************ End *************//
          // DEBUG
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value 
                    << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = 0.4;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}