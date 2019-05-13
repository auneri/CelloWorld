#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  assert(__STDC_VERSION__ >= 201112L);

  printf("hello, world\n");

  return EXIT_SUCCESS;
}
