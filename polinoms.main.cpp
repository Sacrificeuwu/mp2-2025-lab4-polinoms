#include "Header.h"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

int main() {
  Polinom ans;
  Polinom polinom;
  Polinom polinom2;
  while (true) {
    std::string input;
    std::vector<char> toEnter;
    int choice;
    std::cout << "1. Enter a polinom" << std::endl;
    std::cout << "2. Convert to postfix form" << std::endl;
    std::cout << "3. Enter variable values" << std::endl;
    std::cout << "4. Evaluate the expression" << std::endl;
    std::cout << "Select action: ";
    system("cls");
    double valInp;
    std::string nameInp;
    while (input != "0") {
      std::cout << "Enter monom in format: coefficent degree(where 100 is "
                   "degree x, 10 degeree y, 1 degree z)         '0' for exit "
                << std::endl;
      std::getline(std::cin, input);
      if (input.empty()) {
        continue;
      }
      if (input == "0") {
        break;
      }
      try {
        std::istringstream iss(input);
        double coefficient;
        int degree;
        std::string trash;
        if (iss >> coefficient >> degree) {
          Monom *m = new Monom(coefficient, degree);
          polinom.ptr_add_new_monom(m);

        } else {
          std::cout << "Error: Invalid input format" << std::endl;
          std::cout << "Try again" << std::endl;
        }
        if (iss >> trash) {
          std::cout << "only two first numbers would be used" << std::endl;
        }
        polinom.print();
        std::cout << std::endl;
      } catch (const std::string &error) {
        std::cout << "Error: " << error << std::endl;
        std::cout << "Try again" << std::endl;
      }
    }
    std::cout << "Polinom successfully installed : ";
    polinom.print();
    std::cout << std::endl;
    std::cout << "enter operation(+, -, *)" << std::endl;
    std::string operation1;
    std::getline(std::cin, operation1);
    std::istringstream iss(operation1);
    std::string firstWord;
    char operation = ' ';
    if (iss >> firstWord) {

      operation = firstWord[0];
      if (operation == '+' || operation == '-' || operation == '*')
        std::cout << "Operation successfully installed: " << operation
                  << std::endl;
      else
        std::cout << "Anknown operation";
    } else {
      std::cout << "Error: Invalid operation format" << std::endl;
    }
    input.clear();
    std::cout << "Enter enother polinom" << std::endl;
    while (input != "0") {
      std::cout << "Enter monom in format: coefficent degree(where 100 is "
                   "degree x, 10 degeree y, 1 degree z)         '0' for exit "
                << std::endl;
      std::getline(std::cin, input);
      if (input.empty()) {
        continue;
      }
      if (input == "0") {
        break;
      }
      try {
        std::istringstream iss(input);
        double coefficient;
        int degree;

        if (iss >> coefficient >> degree) {
          Monom *m = new Monom(coefficient, degree);
          polinom2.ptr_add_new_monom(m);

        } else {
          std::cout << "Error: Invalid input format" << std::endl;
        }
        polinom2.print();
        std::cout << std::endl;
      } catch (const std::string &error) {
        std::cout << "Error: " << error << std::endl;
      }
    }
    std::cout << "Polinom successfully installed : ";
    polinom.print();
    std::cout << std::endl;
    switch (operation) {
    case '+':
      ans = polinom + polinom2;
      std::cout << "Answer: ";
      ans.print();
      break;
    case '-':
      ans = polinom - polinom2;
      std::cout << "Answer: ";
      ans.print();
      break;
    case '*':
      ans = polinom * polinom2;
      std::cout << "Answer: ";
      ans.print();
      break;
    }
    break;
  }

  return 0;
}