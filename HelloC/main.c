#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  printf("hello, world\n");

#if __STDC_VERSION__ >= 201112L
  printf("C11 is supported!\n");
#endif

  return EXIT_SUCCESS;
}
