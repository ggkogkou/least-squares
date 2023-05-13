
# Least Squares

[![License](https://img.shields.io/badge/license-GPL--3.0-blue)](https://opensource.org/licenses/GPL-3.0)

Least Squares is a numerical method implementation for polynomial approximation. This library provides a convenient way to perform polynomial approximation using the least squares method.

## Features

- Read data from a file
- Perform least squares approximation for a given degree polynomial
- Print the polynomial coefficients

## Installation

To use the Least Squares library, follow these steps:

1. Clone the repository:

   ```shell
   git clone https://github.com/username/least-squares.git
   ```
2. Build the project:
```shell
cd least-squares
make
```
## Usage

To use the Least Squares library in your C++ project, follow these steps:

1. Create an instance of the `LeastSquares` class, providing the name of the data file:

   ```cpp
   #include "LeastSquares.hpp"

   int main() {
       least_squares::LeastSquares ls("data.txt");

       // Perform least squares approximation for a polynomial of degree 3
       ls.least_squares_implementation(3);

       // Print the polynomial coefficients
       ls.printf_polynomial();

       return 0;
   }
   ```
2. Compile and run the program:
	```shell
	g++ main.cpp -o app
	./app
	```
## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, please open an issue or submit a pull request.

## License

This project is licensed under the [GPL-3.0 License](LICENSE).


# Least Squares

[![License](https://img.shields.io/badge/license-GPL--3.0-blue)](https://opensource.org/licenses/GPL-3.0)

Least Squares is a numerical method implementation for polynomial approximation. This library provides a convenient way to perform polynomial approximation using the least squares method.

## Features

- Read data from a file
- Perform least squares approximation for a given degree polynomial
- Print the polynomial coefficients

## Installation

To use the Least Squares library, follow these steps:

1. Clone the repository:

   ```shell
   git clone https://github.com/username/least-squares.git
   ```
2. Build the project:
	```shell
	cd least-squares
	make
	```
## Usage

To use the Least Squares library in your C++ project, follow these steps:

1. Create an instance of the `LeastSquares` class, providing the name of the data file:

   ```cpp
   #include "LeastSquares.hpp"

   int main() {
       least_squares::LeastSquares ls("data.txt");

       // Perform least squares approximation for a polynomial of degree 3
       ls.least_squares_implementation(3);

       // Print the polynomial coefficients
       ls.printf_polynomial();

       return 0;
   }
   ```
2. Compile and run the program:
	```shell
	g++ main.cpp -o app
	./app
	```
## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, please open an issue or submit a pull request.

## License

This project is licensed under the [GPL-3.0 License](LICENSE).

