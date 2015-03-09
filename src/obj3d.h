/*
   Written by Pierluigi Passaro <info@phoenixsoftware.it>
*/

#ifndef _OBJ3D_H
#define _OBJ3D_H

#include "matrix.h"

extern int Obj3dVerticiesCount;
extern int Obj3dTrianglesCount;

extern Vertex* Obj3dVerticies;
extern Triangle* Obj3dTriangles;

extern float Obj3dMaxCoordinate;

int LoadObj3d(char* Obj3dFilename);

#endif /* _OBJ3D_H */
