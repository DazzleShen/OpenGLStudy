#include "Shader.h"

void Shader() 
{
	int nrAttributes = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vartex attributes supported: " << nrAttributes << std::endl;
}