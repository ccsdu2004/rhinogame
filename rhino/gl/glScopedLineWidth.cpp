#include "glPainter.h"

GLScopedLineWidth::GLScopedLineWidth(float width)
{
	glLineWidth(width);
}

GLScopedLineWidth::~GLScopedLineWidth()
{
	glLineWidth(1.0f);
}