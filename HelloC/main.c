//usr/bin/make -s "${0%.*}" && ./"${0%.*}" "$@"; s=$?; rm ./"${0%.*}"; exit $s

// use "bash ./main.c" to build and run the executable

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
