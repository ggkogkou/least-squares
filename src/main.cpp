#include "../inc/LeastSquares.hpp"

#include<cstdlib> /// for std::atoi
#include<string> // for std::string

/**
 * @brief Main function
 * 
 * @param argc command line argument count (ignored)
 * @param argv command line array of arguments (ignored)
 * @return 0 on exit
 */
int main(int argc, char** argv){
    // Initialize polynomial degree and filename of data file
    int polynomial_degree = 3;
    std::string filename = "datafiles/data1.txt";

    if(argc == 2) polynomial_degree = std::atoi(argv[1]);
    if(argc == 3){
        polynomial_degree = std::atoi(argv[1]);
        filename = argv[2];
    } 

    // Declare least_squares::LeastSquares object 
    least_squares::LeastSquares approx = least_squares::LeastSquares(filename);

    // Execute least squares
    approx.least_squares_implementation(polynomial_degree);

    // Print the polynomial
    approx.printf_polynomial();

    return 0;
}
