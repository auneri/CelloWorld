#include <cstdlib>
#include <iostream>


int main(int, char *[]) {

  std::cout << "hello, world" << std::endl;

#if __cplusplus >= 201103L
  std::cout << "C++11 is supported!" << std::endl;
#endif

  return EXIT_SUCCESS;
}
