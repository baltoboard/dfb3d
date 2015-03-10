/*
   Written by Pierluigi Passaro <info@phoenixsoftware.it>
*/

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "obj3d.h"

#define OBJ3D_TOKEN " "
#define OBJ3D_LINE_LEN_MAX 80

int Obj3dVerticiesCount = 0;
int Obj3dTrianglesCount = 0;

Vertex* Obj3dVerticies = 0;
Triangle* Obj3dTriangles = 0;

float Obj3dMaxCoordinate = 0;

static void SetMaxCoordinate(void)
{
  int vertex;
  float coordinate;

  for (vertex = 0; vertex < Obj3dVerticiesCount; vertex ++) {
    coordinate = fabsf(Obj3dVerticies[vertex].x);
    if (Obj3dMaxCoordinate < coordinate)
      Obj3dMaxCoordinate = coordinate;
    coordinate = fabsf(Obj3dVerticies[vertex].y);
    if (Obj3dMaxCoordinate < coordinate)
      Obj3dMaxCoordinate = coordinate;
    coordinate = fabsf(Obj3dVerticies[vertex].z);
    if (Obj3dMaxCoordinate < coordinate)
      Obj3dMaxCoordinate = coordinate;
  }
}

static void ParseObj3d(FILE* fp, char* Obj3dFilename)
{
  char line[OBJ3D_LINE_LEN_MAX];
  char* pch = NULL;
  int vertex = 0;
  int triangle = 0;

  /* round 1: scan the file to count vertex and triangle */
  while (fgets(line, OBJ3D_LINE_LEN_MAX, fp) != NULL) {
    pch = strtok(line, OBJ3D_TOKEN);
    if (pch == NULL)
      continue;
    else if (strcmp(pch, "v") == 0) {
      Obj3dVerticiesCount++;
    } else if (strcmp(pch, "f") == 0) {
      Obj3dTrianglesCount++;
    }
  }
  Obj3dVerticies = calloc(Obj3dVerticiesCount, sizeof(Vertex));
  Obj3dTriangles = calloc(Obj3dTrianglesCount, sizeof(Triangle));

  printf("Found %dv, %dt\n", Obj3dVerticiesCount, Obj3dTrianglesCount);

  /* round 2: rescan the file to populate vertex and triangle */
  if (fseek(fp, 0, SEEK_SET) != 0) {
    printf("%s %d: fseek error %d, trying reopening\n", __func__, __LINE__, errno);
    fclose(fp);
    fp = fopen(Obj3dFilename, "r");
    if (fp == NULL) {
      printf("%s %d: error %d reopening %s\n", __func__, __LINE__, errno, Obj3dFilename);
      exit(0);
    }
  }
  while (fgets(line, OBJ3D_LINE_LEN_MAX, fp) != NULL) {
    pch = strtok(line, OBJ3D_TOKEN);
    if (pch == NULL)
      continue;
    else if (strcmp(pch, "v") == 0) {
      if (vertex == Obj3dVerticiesCount) {
        printf("Found %s %d: ignoring unexpected line %s\n", __func__, __LINE__, line);
        continue;
      }
      Obj3dVerticies[vertex].x = atof(strtok(NULL, OBJ3D_TOKEN));
      Obj3dVerticies[vertex].y = atof(strtok(NULL, OBJ3D_TOKEN));
      Obj3dVerticies[vertex].z = atof(strtok(NULL, OBJ3D_TOKEN));
      vertex++;
    } else if (strcmp(pch, "f") == 0) {
      if (triangle == Obj3dTrianglesCount) {
        printf("%s %d: ignoring unexpected line %s\n", __func__, __LINE__, line);
        continue;
      }
      Obj3dTriangles[triangle].a = atoi(strtok(NULL, OBJ3D_TOKEN)) - 1;
      Obj3dTriangles[triangle].b = atoi(strtok(NULL, OBJ3D_TOKEN)) - 1;
      Obj3dTriangles[triangle].c = atoi(strtok(NULL, OBJ3D_TOKEN)) - 1;
      triangle++;
    }
  }

  printf("Loaded %dv, %dt\n", vertex, triangle);

}

int LoadObj3d(char* Obj3dFilename)
{
  FILE* fp = NULL;

  if ((Obj3dFilename == NULL) || (strlen(Obj3dFilename) == 0)) {
    printf("%s %d: Obj3dFilename NULL or empty\n", __func__, __LINE__);
    return -1;
  } else if ((fp = fopen(Obj3dFilename, "r")) == NULL) {
    printf("%s %d: Unable to open file %s\n", __func__, __LINE__, Obj3dFilename);
    return -1;
  }

  ParseObj3d(fp, Obj3dFilename);
  fclose(fp);
  SetMaxCoordinate();

  return 0;
}

