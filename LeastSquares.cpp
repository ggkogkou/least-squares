#include "LeastSquares.hpp"

least_squares::LeastSquares::LeastSquares(std::string file){
    filename = file;
}

void least_squares::LeastSquares::parse_data(){
    std::fstream read_data;
    read_data.open(filename);

    if(!read_data){
        std::cout << "Error... data.txt couldn't open\n";
        exit(1);
    }

    double input;

    int counter = 0;
    read_data >> input;
    while (!read_data.eof()){
        if(counter%2 == 0) x_values.push_back(input);
        if(counter%2 == 1) y_values.push_back(input);
        counter++;
        read_data >> input;
    }
    y_values.push_back(input);
    read_data.close();
}

void least_squares::LeastSquares::init_matrix_A(){
    for(auto i : x_values){
        std::vector<double> temp_row {};
        for(int j=0; j<=polynomial_degree; j++){
            if(j == 0) temp_row.push_back((double) 1);
            else temp_row.push_back(std::pow(i, j));
        }
        matrix_A.push_back_row(temp_row);
    }
}

void least_squares::LeastSquares::init_matrix_B(){
    for(auto x : y_values){
        std::vector<double> temp {};
        temp.push_back(x);
        matrix_B.push_back_row(temp);
    }
}

void least_squares::LeastSquares::init_matrix_AT(){
    std::vector<std::vector<double>> temp = matrix_A.get_transpose();
    for(auto i : temp) matrix_AT.push_back_row(i);
}

void least_squares::LeastSquares::bind_all(){
    parse_data();
    init_matrix_A();
    init_matrix_B();
    init_matrix_AT();
}

void least_squares::LeastSquares::least_squares_implementation(int polynomial_degree){
    this->polynomial_degree = polynomial_degree;
    bind_all(); // init matrices A, B and AT

    // Find product AT*A
    Matrix<double> product_ATA = Matrix<double>((matrix_AT * matrix_A).get_matrix(), "This is product AT*A");
    // Find product AT*B
    Matrix<double> product_ATB = Matrix<double>((matrix_AT * matrix_B).get_matrix(), "This is product AT*B");
    // Find inverse of AT*A
    Matrix<double> inverse_ATA = Matrix<double>(product_ATA.get_inverse(), "This is inverse of product AT*A");
    // Find product (AT*A)^-1*AT*B
    Matrix<double> solution_x = Matrix<double>((inverse_ATA * product_ATB).get_matrix(), "This is solution of least squares equations");
    // If dimensions are mxn with n>1 then throw exception
    if(solution_x.get_n() > 1) throw std::invalid_argument("Solution x of least squares equation has to be a mx1 vector");
    // else find coeeficients
    for(auto i : solution_x.get_matrix()){
        for(auto j : i) coefficients.push_back(j);
    }
}

void least_squares::LeastSquares::printf_polynomial(){
    std::printf("\nThe polynomial is the below:\np(x) = ");

    double temp;
    for(int power=0; power<polynomial_degree+1; power++){
        temp = coefficients.at(power);

        if(power != polynomial_degree && temp >= 0)
            std::printf("+ %lf * X^%d ", temp, power);
        else if(power != polynomial_degree && temp < 0)
            std::printf("- %lf * X^%d ", std::abs(temp), power);
        else if(temp >= 0)
            std::printf("+ %lf * X^%d\n", temp, power);
        else
            std::printf("- %lf * X^%d\n", std::abs(temp), power);
    }
}
