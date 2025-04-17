#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <glew/include/GL/glew.h>

#include "typedefs.h"


GLuint createShader(const std::string& vertexPath, const std::string& fragmentPath);