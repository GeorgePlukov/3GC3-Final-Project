#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <vector>
#include <algorithm>
#include <string>

#include "StarfoxUtils.h"
#include "PMath/PPoint.h"
#include "PMath/PVector.h"

#include "PPMLoader.h"

#include "Material.h"
#include "Light.h"