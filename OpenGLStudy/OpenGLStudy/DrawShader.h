#pragma once

#include "CommonDefine.h"

GLFWwindow* CreateGLFWwindow();
void ShaderWithVSAndFSFile();   //颜色通过shader控制
void ShaderWithColorVAO();      //颜色通过顶点位置、顶点颜色控制
void Shader();
