#include "glPainter.h"

GLScopedColor::GLScopedColor()
{
	glGetFloatv(GL_CURRENT_COLOR,color);
}

GLScopedColor::~GLScopedColor()
{
	glColor4fv(color);
}