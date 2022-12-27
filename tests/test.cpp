#include "../inc/LeastSquares.hpp"

#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

TEST_CASE("Test 1", "[vector]"){
    // Declare least_squares::LeastSquares object 
    least_squares::LeastSquares approx = least_squares::LeastSquares("../datafiles/data1.txt");

    // Execute least squares
    approx.least_squares_implementation(3);
    auto test1 = approx.get_coefficients();
    std::vector<double> test_equal {10.7670245551, -6.6622179143, 1.554143056, -0.0703723034};
    REQUIRE(test1.size() == test_equal.size());
    for(auto x=1; x<(int) test1.size(); x++){
        REQUIRE(test1[x] == Approx(test_equal[x]));
    }
}

TEST_CASE("Test 2", "[vector]"){
    // Declare least_squares::LeastSquares object 
    least_squares::LeastSquares approx = least_squares::LeastSquares("../datafiles/data2.txt");

    // Execute least squares
    approx.least_squares_implementation(3);
    auto test1 = approx.get_coefficients();
    std::vector<double> test_equal {0.5333941, 2.840975, -0.1837601, 0.0034871};
    REQUIRE(test1.size() == test_equal.size());
    for(auto x=1; x<(int) test1.size(); x++){
        REQUIRE(test1[x] == Approx(test_equal[x]));
    }
}

TEST_CASE("Test 3", "[vector]"){
    // Declare least_squares::LeastSquares object 
    least_squares::LeastSquares approx = least_squares::LeastSquares("../datafiles/data3.txt");

    // Execute least squares | Second degree polynomial
    approx.least_squares_implementation(2);
    auto test1 = approx.get_coefficients();
    std::vector<double> test_equal {7.3189862, -0.6210657, 0.0176575};
    REQUIRE(test1.size() == test_equal.size());
    for(auto x=1; x<(int) test1.size(); x++){
        REQUIRE(test1[x] == Approx(test_equal[x]));
    }
}
