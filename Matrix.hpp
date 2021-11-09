#pragma once

/**
 * @file Matrix.hpp
 * @author [ggkogkou](https://github.com/ggkogkou)
 * @brief an implementation of class Matrix
 *
 * 
 */

#include "matrix_algebra.hpp"

#include<vector> /// for std::vector container
#include<iostream> /// for IO operations
#include<cstdint> /// for integer allocation operations
#include<cmath> /// for mathematical functions
#include<string> /// for std::string
#include<stdexcept> /// for throwing exceptions

/**
 * @brief a template Matrix class for 
 * 
 * @tparam T 
 */
template<class T>
class Matrix {
private:
    long m, n; // dimensions mxn
    /**
     * @brief the matrix
     * 
     */
    std::vector<std::vector<T>> matrix {};
    /**
     * @brief the transpose of the matrix
     * 
     */
    std::vector<std::vector<T>> transpose {};
    /**
     * @brief the inverse of the matrix
     * 
     */
    std::vector<std::vector<double>> inverse {};
    /**
     * @brief a short description of the matrix object created
     * 
     */
    std::string description;

public:
    /**
     * @brief Construct a new Matrix object
     * 
     * @param matrix is the matrix 
     * @param desc is a brief description of the matrix
     */
    Matrix(std::vector<std::vector<T>> a, std::string desc){
        // Get the dimensions of the matrix
        // Be aware that matrix can be an empty vector
        m = a.size();
        if(m > 0)
            n = a[0].size();
        else n = 0;

        description = desc;

        // Get the rows and the columns of the matrix
        for(auto i : a){
            matrix.push_back(i);
        }
    }

    /**
     * @brief add a row in a specific position
     * 
     * @param row is the row we want to add
     * @param position is the position of the new row 
     */
    void add_row_in_position(std::vector<T> const &row, std::uint32_t position){
        auto it = matrix.emplace(matrix.begin() + position, row);
        m = matrix.size();
        n = matrix[0].size();
    }

    /**
     * @brief add a new row in the bottom of the matrix
     * 
     * @param row is the vector of the row we want to add
     */
    void push_back_row(std::vector<T> const &row){
        matrix.push_back(row);
        m = matrix.size();
        n = matrix[0].size();
    }

    /**
     * @brief add a column in the end of the matrix
     * @details notice that adding a column is equivalent to adding a row 
     * to the transpose
     * 
     * @param column is the column we want to add
     */
    void add_column(std::vector<T> const &column){
        // Add the column as a new row to the transpose
        // Firstly, update transpose variable
        transpose = get_transpose();
        transpose.push_back_row(column);
        // Transpose the new transposed matrix to get the desired 
        matrix = matrix_algebra::transpose(transpose);
        // Update dimensions
        m = matrix.size();
        n = matrix[0].size();
    }

    /**
     * @brief Get the matrix object
     * 
     * @return auto 
     */
    auto get_matrix(){
        return matrix;
    }

    /**
     * @brief Get the transpose object
     * 
     * @return auto 
     */
    auto get_transpose(){
        transpose = matrix_algebra::transpose(matrix);
        return transpose;
    }

    /**
     * @brief Get the inverse object
     * 
     * @return auto 
     */
    auto get_inverse(){
        if(m != n) throw std::invalid_argument("Matrix has to be square");
        inverse = matrix_algebra::inverse(matrix);
        return inverse;
    }

    /**
     * @brief Get the m dimension (number of rows)
     * 
     * @return auto 
     */
    auto get_m(){
        return m;
    }

    /**
     * @brief Get the n dimension (number of columns)
     * 
     * @return auto 
     */
    auto get_n(){
        return n;
    }

    // Overload operators +, -, *, ^ to perform matrix operations

    /**
     * @brief overload operator + to perform the addition of two matrices
     * 
     * @param obj is the right parameter of the operator
     * @return the result of the addition
     */
    Matrix operator+ (Matrix const &obj){
        Matrix<double> temp = Matrix<double>(matrix_algebra::add(this->matrix, obj.matrix), "Addition result");
        return temp;
    }

    /**
     * @brief overload operator - to perform sutraction of two matrices
     * 
     * @param obj is the right parameter of the operator
     * @return the result of subtraction
     */
    Matrix operator- (Matrix const &obj){
        Matrix<double> temp = Matrix<double>(matrix_algebra::subtract(this->matrix, obj.matrix), "Subtraction result");
        return temp;
    }

    /**
     * @brief overload operator * to perform multiplication of two matrices
     * 
     * @param obj is the right parameter of the operator
     * @return the result of multiplication 
     */
    Matrix operator* (Matrix const &obj){
        Matrix<double> temp = Matrix<double>(matrix_algebra::multiply(this->matrix, obj.matrix), "Multiplication result");
        return temp;
    }

}; // class Matrix
