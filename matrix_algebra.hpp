#pragma once

/**
 * @file matrix_algebra.hpp
 * @author [ggkogkou](https://github.com/ggkogkou)
 * @brief 
 * 
 */

#include<iostream> /// for IO operations
#include<vector> /// for std::vector container
#include<cstdio> /// for IO operations

/**
 * @namespace matrix_algebra
 * @brief perform various matrix algebra operations such as multiplication, inversion etc.
 * 
 */
namespace matrix_algebra {
    /**
     * @brief transpose a matrix
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is the matrix to be transposed
     * @return auto the transpose
     */
    template<typename T> std::vector<std::vector<T>> transpose(std::vector<std::vector<T>> const &a){
        int m = a.size();
        int n = a[0].size();
        std::vector<std::vector<T>> transpose {};
        for(int j=0; j<n; j++){
            std::vector<T> temp;
            for(int i=0; i<m; i++)
                temp.push_back(a[i].at(j));
            transpose.push_back(temp);
        }
        return transpose;
    }

    /**
     * @brief find the dot product of two vectors
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is vector a
     * @param b is vector a
     * @return auto the result of the dot product
     */
    template<typename T> auto dot_product(std::vector<T> const &a, std::vector<T> const &b){
        T product = 0;
        if(a.size() != b.size()) throw std::invalid_argument("Vectors have to be in the same dimensions");
        for(int i=0; i<(int) a.size(); i++)
            product += a[i] * b[i];
        return product;
    }

    /**
     * @brief multiply two matrices
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is a matrix a
     * @param b is a matrix b
     * @return auto the multiplication matrix a*b
     */
    template<typename T> auto multiply(std::vector<std::vector<T>> const &a, std::vector<std::vector<T>> const &b){
        std::vector<std::vector<T>> temp {};

        if(a[0].size() != b.size()) throw std::invalid_argument("Matrix A columns have to be equal to B's rows");

        // In order to calculate the proper dot products i will have to find b's transpose
        std::vector<std::vector<T>> bt = transpose(b);
        for(auto i : a){
            std::vector<T> another_temp {};
            for(auto j : bt){
                another_temp.push_back(dot_product(i, j));
            }
            temp.push_back(another_temp);
        }
        return temp;
    }

    /**
     * @brief add two matrices
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is a matrix a
     * @param b is a matrix b
     * @return auto the addition matrix a+b
     */
    template<typename T> auto add(std::vector<std::vector<T>> const &a, std::vector<std::vector<T>> const &b){
        std::vector<std::vector<T>> temp(a.size());
        if((a.size() != b.size()) || (a[0].size() != b[0].size())) throw std::invalid_argument("Matrices have to be in the same dimensions");
        for(int i=0; i<a.size(); i++){
            for(int j=0; j<a[0].size(); j++) temp[i].push_back(a[i].at(j) + b[i].at(j));
        }
        return temp;
    }

    /**
     * @brief subtract two matrices
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is a matrix a
     * @param b is a matrix b
     * @return auto the subtraction matrix a-b
     */
    template<typename T> auto subtract(std::vector<std::vector<T>> const &a, std::vector<std::vector<T>> const &b){
        std::vector<std::vector<T>> temp(a.size());
        if((a.size() != b.size()) || (a[0].size() != b[0].size())) throw std::invalid_argument("Matrices have to be in the same dimensions");
        for(int i=0; i<a.size(); i++){
            for(int j=0; j<a[0].size(); j++) temp[i].push_back(a[i].at(j) - b[i].at(j));
        }
        return temp;
    }

/**
 * @namespace find_inverse
 * @brief necessary functions to calculate inverse of a matrix
 * @details this namespace consists of functions that perform various operations 
 * to matrices in order to find the inverse of a matrix by the method of the 
 * adjugate. In order to accomplish that, there exist functions that find the submatrix,
 * the C factor, the adjugate and the determinant 
 * 
 */
namespace find_inverse {
    /**
     * @brief find submatrix of matrix a
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is the matrix 
     * @param N is a's dimensions
     * @param b is the submatrix that will occur. It is chenges hence it's not a const
     * @param disabledRow is the row that we disable 
     * @param disabledColumn is the column that we disable
     */
    template<typename T> void find_submatrix(std::vector<std::vector<T>> const &a, int N, std::vector<std::vector<T>> &b, int disabledRow, int disabledColumn){
        int i=0;

        // Store in matrix b the NxN elements of the (N+1)x(N+1) matrix a, by eliminating the elements of
        // the row and column disabled

        // WARNING: The a matrix is the original matrix so i keep track of the elements i need
        // for creating the submatrix by the use of the N index that represents the dimensions of the submatrix 
        // that i want to create.
        b.clear();
        b.resize(N);
        for(int row=0; row<N; row++){
            for(int col=0; col<N; col++){
                // Check if the element doesn't belong to the eliminated row or column
                if(row != disabledRow && col != disabledColumn){
                    b[i].push_back(a[row].at(col));
                }
                // When the index hits the maximum of the submatrix column elements 
                // start storing elements of the next row... increase i index
                if (b[i].size() == (unsigned int) N-1) i++;    
            }
        }
    }

    /**
     * @brief find the determinant of a square matrix
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is the matrix
     * @param N is the size of the square matrix
     * @return auto the determinant
     */
    template<typename T> auto determinant(std::vector<std::vector<T>> const &a, int N){
        // Initialize the determinant variable
        T det = 0;

        // Terminal conditions for the recursion
        if(N == 1) return a[0].at(0);
        if(N == 2){
            T temp = a[0].at(0) * a[1].at(1) - a[1].at(0) * a[0].at(1);
            return temp;
        }

        // Declare a matrix that will be processed to find the sybmatrix
        std::vector<std::vector<T>> submatrix(N);
        int sign = 1; // 1: positive sign, -1: negative sign

        // Recursion loop --->
        // Loop through the first row (first element of vector) of the matrix, find the submatrix through
        // the findSubmatrix method and store it in the submatrix vector variable. This submatrix
        // pass it as argument in the recursive call of determinant so that each time it loops through the first
        // row of the existing submatrix.
        for(int i=0; i<N; i++){
            find_submatrix(a, N, submatrix, 0, i);
            // a[0].at(i) as i always need to loop through the first row of the submatrix
            det += sign * a[0].at(i) * determinant(submatrix, N-1); // recursive call
            sign = -sign; // Update sign for the next pivot element
        }

        return det;
    }

    /**
     * @brief calculate the factors Ci,j that form the adjugate
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a a is the matrix
     * @param i the row of the C factor
     * @param j the column of the C factor
     * @return auto C factor
     */
    template<typename T> auto calculateCFactor(std::vector<std::vector<T>> const &a, int i, int j){
        double c_factor = 0;
        double sign = 1;

        // Define the sign 
        if((i+j)%2 == 0) sign = (double) 1;
        else sign = (double) -1;

        std::vector<std::vector<T>> temp {};
        // The subMatrix has dimensions (N-1)x(N-1) so with the way that findSubmatrix is implemented
        // the function will return a vector with size: 3 but only 2 elements in it as it will have zeros in 
        // the extra positions. 
        int submatrix_dimensions = a.size();
        find_submatrix(a, submatrix_dimensions, temp, i, j);

        // The real size of the temp is temp.size-1
        c_factor =  sign * determinant(temp, --submatrix_dimensions);

        return c_factor;
    }

    /**
     * @brief find the adjugate of a matrix
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is the matrix
     * @return auto the adjugate
     */
    template<typename T> auto adjugate(std::vector<std::vector<T>> const &a){
        int N = a.size(); // dimensions of the matrix
        std::vector<std::vector<T>> temp {}; // vector to be returned

        for(int i=0; i<N; i++){
            std::vector<T> another_temp {};
            for(int j=0; j<N; j++)
                another_temp.push_back(calculateCFactor(a, i, j));
            temp.push_back(another_temp);
        }

        std::vector<std::vector<T>> transposed_temp = matrix_algebra::transpose(temp);
        return transposed_temp;
    }

} // namespace find_inverse

    /**
     * @brief inverse a matrix
     * 
     * @tparam T is the type of the elements of the matrices
     * @param a is the matrix to be inverted
     * @return auto the inverse
     */
    template<typename T> auto inverse(std::vector<std::vector<T>> const &a){
        // Declare the vector that will store the inverse matrix to be returned. It contains only double types
        std::vector<std::vector<double>> inverse_matrix {};

        // Calculate the determinant of the matrix
        T detA = find_inverse::determinant(a, a.size());

        // Throw exception if determinant is zero then matrix is not invertible
        if(detA == 0){
            std::printf("The matrix is not invertible.. det(matrix) = 0\n");
            // return {}; // empty vector
            throw std::invalid_argument("Determinant is zero (=0), thus matrix is not invertible");
        }

        // As known A^-1 = 1/det(A) * adj(A)
        double invDet = (double) 1 / (double) detA;
        std::vector<std::vector<double>> adjA = find_inverse::adjugate(a);

        // Insert in the inverted matrix the elements typecasted into doubles
        double element;
        for(auto i : adjA){
            std::vector<double> another_temp {};
            for(auto j : i){
                element = (double)invDet * (double) j;
                another_temp.push_back(element);
            }
            inverse_matrix.push_back(another_temp);
        }

        return inverse_matrix;
    }

} // namespace matrix_algebra
