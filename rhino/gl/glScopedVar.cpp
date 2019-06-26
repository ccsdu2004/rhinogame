#include "glPainter.h"

GLScopedVariable::GLScopedVariable(int gl):
glvar(gl)
{
	enabled = glIsEnabled(glvar) == GL_TRUE;
	if(!enabled)
		glEnable(glvar);
}

GLScopedVariable::~GLScopedVariable()
{
	if(!enabled)
		glDisable(glvar);
}