//usr/bin/make -s "${0%.*}" && ./"${0%.*}" "$@"; s=$?; rm ./"${0%.*}"; exit $s

// use "bash ./main.cc" to build and run the executable

#include <cstdlib>
#include <iostream>


int main(int, char *[]) {

  std::cout << "hello, world" << std::endl;

#if __cplusplus >= 201103L
  std::cout << "C++11 is supported!" << std::endl;
#endif

  return EXIT_SUCCESS;
}
