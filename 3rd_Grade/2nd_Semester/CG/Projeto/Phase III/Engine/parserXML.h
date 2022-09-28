#ifndef ENGINE_PARSERXML_H
#include <GL/glew.h>
#include <GL/glut.h>
#include "dataStructs.h"
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#define ENGINE_PARSERXML_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <unistd.h>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

bool parseInput(const char* file_name, World *w, vector<float> *vert);

#endif //ENGINE_PARSERXML_H
