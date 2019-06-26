#ifndef RHINO_GLPAINTER_H
#define RHINO_GLPAINTER_H
#include <cstdint>
#include <QPoint>
#include <QRect>
#include <QColor>
#include <QOpengl.h>
#include "rhino.h"

class RHINO_EXPORT GLScopedColor
{
public:
	GLScopedColor();
	~GLScopedColor();
private:
	GLfloat color[4];
};

class RHINO_EXPORT GLScopedLineWidth
{
public:
	GLScopedLineWidth() = delete;
	GLScopedLineWidth(float width);
	~GLScopedLineWidth();
};

/* var only for followings
GL_BLEND
GL_CULL_FACE
GL_DEPTH_TEST
GL_DITHER
GL_POLYGON_OFFSET_FILL
GL_SAMPLE_ALPHA_TO_COVERAGE
GL_SAMPLE_COVERAGE
GL_SCISSOR_TEST
GL_STENCIL_TEST*/
class RHINO_EXPORT GLScopedVariable
{
public:
	GLScopedVariable() = delete;
	GLScopedVariable(int glvar);
	~GLScopedVariable();
private:
	bool enabled;
	int glvar;
};

class RHINO_EXPORT GLPainter
{
public:
	GLPainter();
	~GLPainter();
public:
	void setBackgroundColor(const QColor& color);
	void setColor(const QColor& color);

	void setLineWidth(float width);
	float maximumLineWidth();
	float lineWidth();

	void drawLine(float x1,float y1,float x2,float y);
	void drawLine(const QPointF& start,const QPointF& end);
	void drawTriangle(const QPointF& p1,const QPointF& p2,const QPointF& p3,bool filled);
	void drawRectangle(float x,float y,float width,float height,bool filled);
	void drawWrongNumber(const QPointF& point,float width);
	void drawCircle(float x,float y,float r,int count = 90);
	void drawGrid(float x,float y,float cellwidth,float cllheight,int col,int row);

	void drawHexGon(float x,float y,float size);
	void drawHexGons(float x,float y,float size,int col,int row);

	void drawTexture(uint32_t id,float* co,float* vertices);
};

#endif