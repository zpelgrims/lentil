#include "../../Eigen/Eigen/Core"
#include "../../Eigen/Eigen/LU"
#include <iostream>


int main(){
    double eps = 1e-16;
    Eigen::Vector2d p(0.0, 0.0);
    
    double x = 0.1; // initial guess
    double y = 2.0; // initial guess

    double f1 = 1e9;
    double f2 = 1e9;
    double sqr_err = 1e30;

    unsigned int count = 0;
    double weighting_tau = 0.72;

    double ap_x = 2;
    double ap_y = 3;

    while (sqr_err > eps){
        std::cout << "count : " << count << std::endl;

        // f1 = x*x - 10*x + y*y - 10*y + 34;
        // f2 = x*x - 22*x + y*y - 10*y + 130;
        f1 = x*x - y*y - 4*x + 6;
        f2 = 2*x*y + 4*y - 2;

        std::cout << "f1: " << f1 << ", f2: " << f2 << std::endl;
                
        const Eigen::Vector2d delta(ap_x - f1, ap_y - f2);
        sqr_err = delta[0]*delta[0]+delta[1]*delta[1];
        std::cout << "sqr_err: " << sqr_err << std::endl;

        // double A = 2*x - 10;
        // double B = 2*y - 10;
        // double C = 2*x - 22;
        // double D = 2*y - 10;
        double A = 2*(x-2);
        double B = -2*y;
        double C = 2*y;
        double D = 2*(x+2);
        Eigen::Matrix2d J;
        J << A, B, C, D;


    // W4-method
        Eigen::Matrix2d J_U_inv;
        J_U_inv << J(0,0) -J(0,1)*J(1,0)/J(1,1),   J(0,1),
                     0.0,                          J(1,1);
        J_U_inv = J_U_inv.inverse().eval();

        Eigen::Matrix2d J_L_inv;
        J_L_inv << 1.0,                             0.0, 
                   J(1,0)/J(1,1),                   1.0;
        J_L_inv = J_L_inv.inverse().eval();


        Eigen::Vector2d f3(f1, f2);

        // if (count == 0) p = -(1.0 - 2*weighting_tau) * J_U_inv * delta;
        Eigen::Vector2d E = weighting_tau * J_L_inv * p;
        p =  -(1.0 - 2*weighting_tau)  * J_U_inv * delta;

        x += E(0);
        y += E(1);

        
    // newton-raphson as in polynomial optics implementation
        // Eigen::Vector2d E = J.inverse().eval() * delta;
        // x += E(0);
        // y += E(1);

        std::cout << "x, y: " << x << ", " << y << std::endl;

        ++count;

    }
}
