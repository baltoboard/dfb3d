#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "obj3d.h"


int main (int argc, char *argv[])
{
  char* Obj3dFilename = NULL;
  int n;

  for (n = 1; (n < argc) && (Obj3dFilename == NULL); n++) {
    if (strcmp(argv[n], "--obj3d") == 0) {
      Obj3dFilename = argv[n + 1];
    }
  }
  LoadObj3d(Obj3dFilename);

  return 0;
}
