#include <cassert>
#include <cstdlib>
#include <iostream>


int main(int, char *[]) {

  assert(__cplusplus >= 201103L);

  std::cout << "hello, world" << std::endl;

  return EXIT_SUCCESS;
}
