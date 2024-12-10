#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "environment.h"
#include "process.h"


void test1(const std::string& command) {
  environment_set("TEST", "1");
  const std::string a = process_output(command);
  const std::string b = "1";
  if (a != b) throw std::runtime_error("Expected \"" + b + "\", received \"" + a + "\"");
}


void test2(const std::string& command) {
  environment_set("TEST", "1");
  environment_append("TEST", "2");
  const std::string a = process_output(command);
  const std::string b = "1" + PATHSEP + "2";
  if (a != b) throw std::runtime_error("Expected \"" + b + "\", received \"" + a + "\"");
}


void test3(const std::string& command) {
  environment_set("TEST", "1");
  environment_prepend("TEST", "0");
  const std::string a = process_output(command);
  const std::string b = "0" + PATHSEP + "1";
  if (a != b) throw std::runtime_error("Expected \"" + b + "\", received \"" + a + "\"");
}


void tests(const int test) {
#ifdef _WIN32
    const auto command = "cmd /c \"echo | set /p x=\"%TEST%\"\"";
#else
    const auto command = "bash -c \"echo -n $TEST\"";
#endif
    if (test == 1) {
      test1(command);
    } else if (test == 2) {
      test2(command);
    } else if (test == 3) {
      test3(command);
    } else {
      throw std::runtime_error("Failed to find test");
    }
}


int main(int argc, char* argv[]) {
  try {
    if (argc != 2) throw std::runtime_error("Test number was not provided");
    tests(std::stoi(argv[1]));
  } catch (const std::exception& exception) {
    std::cerr << exception.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
