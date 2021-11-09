#include "LeastSquares.hpp"

#include<cstdlib> /// for std::atoi

/**
 * @brief Main function
 * 
 * @param argc command line argument count (ignored)
 * @param argv command line array of arguments (ignored)
 * @return 0 on exit
 */
int main(int argc, char** argv){
    // Initialize polynomial degree
    int polynomial_degree = 3;
    if(argc == 2) polynomial_degree = std::atoi(argv[1]);

    // Declare least_squares::LeastSquares object 
    least_squares::LeastSquares approx = least_squares::LeastSquares();

    // Execute least squares
    approx.least_squares_implementation(polynomial_degree);

    // Print the polynomial
    approx.printf_polynomial();

    return 0;
}
