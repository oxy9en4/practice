#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <Windows.h>
#include <map>
#include <unordered_map>


#define PI (3.141592f)
#define EPSILON (0.0001f)
#define RadianToDegree(radian) (radian * ( 180.0f / PI))
#define DegreeToRadian(degree) (degree * ( PI / 180.0f ))
#define randstep(fmin, fmax) ((float)fmin + ((float)fmax - (float)fmin)* rand() / RAND_MAX)