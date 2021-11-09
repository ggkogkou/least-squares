#pragma once

/**
 * @file LeastSquares.hpp
 * @author [ggkogkou](https://github.com/ggkogkou)
 * @brief Implement the least squares numerical method for approximation
 * @details [More about least squares method](https://en.wikipedia.org/wiki/Least_squares).
 * To form the least squares problem we need a set of points (x, y). Given the degree of the polynomial,
 * substitute the points and get a linear system A*x=B where unknowns are the coefficients of the polynomial, 
 * matrix A is the matrix with the substituted x points and matrix B of the y points. The least squares solution is
 * x = (AT*A)^(-1) * AT*B, where AT is A's transpose.
 * 
 */

#include "Matrix.hpp"

#include<iostream> /// for IO operations
#include<cmath> /// for mathematical functions
#include<vector> /// for std::vector container
#include<stdexcept> /// for throwing exceptions
#include<cstdio> /// for IO operations
#include<string> /// for std::string
#include<fstream> /// for reading files 

/**
 * @namespace least_squares
 * @brief contains class that implements least squares 
 * 
 */
namespace least_squares{

/**
 * @class LeastSquares
 * @brief implement least squares
 * 
 */
class LeastSquares {
    private:
        // Variables
        /**
         * @brief a vector with x points as given in the data.txt
         * @see data.txt
         */
        std::vector<double> x_values {};
        /**
         * @brief a vector with y points as given in the data.txt
         * @see data.txt
         */
        std::vector<double> y_values {};
        /**
         * @brief a vector that will store the coefficients of the polynomial
         * 
         */
        std::vector<double> coefficients {};
        /**
         * @brief matrix A is the one produced by the x values
         * 
         */
        Matrix<double> matrix_A = Matrix<double>({}, "This is matrix A");
        /**
         * @brief matrix B is produced by y values
         * 
         */
        Matrix<double> matrix_B = Matrix<double>({}, "This is matrix B");
        /**
         * @brief matrix AT is A's transpose
         * 
         */
        Matrix<double> matrix_AT = Matrix<double>({}, "This is matrix AT");
        /**
         * @brief degree of the polynomial, 2 by default
         * 
         */
        int polynomial_degree = 2;

        // Functions

        /**
         * @brief parse data from the data.txt
         * 
         */
        void parse_data();
        
        /**
         * @brief initialize matrix A that is composed by x's
         * 
         */
        void init_matrix_A();

        /**
         * @brief initialize matrix B that is composed by y's
         * 
         */
        void init_matrix_B();

        /**
         * @brief find transpose matrix of A
         * 
         */
        void init_matrix_AT();

        /**
         * @brief call the previous functions
         * 
         */
        void bind_all();

    public:
        /**
         * @brief Construct a new Least Squares object
         * 
         */
        LeastSquares();

        /**
         * @brief implementation of least squares method
         * 
         * @param polynomial_degree is the degree of the polynomial the user wants
         */
        void least_squares_implementation(int polynomial_degree);

        /**
         * @brief print the polynomial in a formatted output
         * 
         */
        void printf_polynomial();

}; // class LeastSquares
} // namespace least_squares
