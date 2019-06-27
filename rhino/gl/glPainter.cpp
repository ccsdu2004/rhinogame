#include <qopengl.h>
#include <QDebug>
#include "glPainter.h"
#include "rhinoMath.h"
#include "world.h"

GLPainter::GLPainter()
{
}

GLPainter::~GLPainter()
{
}

void GLPainter::setColor(const QColor& color)
{
	glColor4f(color.redF(),color.greenF(),color.blueF(),color.alphaF());
}

void GLPainter::setBackgroundColor(const QColor& color)
{
	glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void GLPainter::setLineWidth(float width)
{
	glLineWidth(width);
}

float GLPainter::maximumLineWidth()
{
	GLfloat ret[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE,ret);
	return float(ret[1]);
}

float GLPainter::lineWidth()
{
	GLfloat ret;
	glGetFloatv(GL_LINE_WIDTH,&ret);
	return ret;
}

void GLPainter::drawLine(const QPointF& start,const QPointF& end)
{
	glBegin(GL_LINES);
	    glVertex2f(start.x(),start.y());
	    glVertex2f(end.x(), end.y());
	glEnd();
}

void GLPainter::drawLine(float x1,float y1,float x2,float y2)
{
	glBegin(GL_LINES);
	    glVertex2f(x1,y1);
	    glVertex2f(x2,y2);
	glEnd();
}

void GLPainter::drawRectangle(float x,float y,float width,float height,bool filled)
{
	if (filled)
	{
		glBegin(GL_POLYGON);
		    glVertex2f(x,y);
		    glVertex2f(x+width,y);
		    glVertex2f(x+width,y+height);
		    glVertex2f(x,y+ height);
		glEnd();
	}
	else
	{
		const float halfwidth = lineWidth() * 0.5f;
		
		glBegin(GL_LINES);
		    glVertex2f(x+halfwidth,y);
		    glVertex2f(x+halfwidth,y+height-halfwidth);
		    
			glVertex2f(x+width-halfwidth,y);
			glVertex2f(x+width-halfwidth,y+height-halfwidth);

			glVertex2f(x + halfwidth, y);
			glVertex2f(x + width - halfwidth, y);

			glVertex2f(x + width - halfwidth, y + height - halfwidth);
			glVertex2f(x + halfwidth, y + height - halfwidth);
		glEnd();
	}
}

void GLPainter::drawWrongNumber(const QPointF& point,float width)
{
	float half = width*0.5f;
	drawLine(point+QPointF(-half,-half),point+QPointF(half,half));
	drawLine(point+QPointF(-half,+half),point+QPointF(half,-half));
}

void GLPainter::drawTriangle(const QPointF& p1, const QPointF& p2, const QPointF& p3, bool filled)
{
	if (filled)
		glBegin(GL_TRIANGLES);
	else
		glBegin(GL_LINE_LOOP);

	glVertex2f(p1.x(), p1.y());
	glVertex2f(p2.x(), p2.y());
	glVertex2f(p3.x(), p3.y());
	glEnd();
}

void GLPainter::drawCircle(float x,float y,float r,int count)
{
	glBegin(GL_POINTS);
	for(int i = 0; i < count;i++)
	{
		glVertex2f(x+r*cos(2*PI*i/count),y+r*sin(2*PI*i/count));  
	}
	glEnd();
}

void GLPainter::drawGrid(float x,float y,float cellwidth,float cellheight,int col,int row)
{
	for (int i=0;i<= col;i++)
		drawLine(QPointF(x+cellwidth*i,y),QPointF(x+cellwidth*i,y+cellheight*col));

	for(int i=0;i<=row;i++)
		drawLine(QPointF(x, y+cellwidth*i),QPointF(x + cellwidth * col,y + cellwidth * i));
}

void GLPainter::drawHexGon(float x,float y,float size)
{
	const float k = R3 * size;
	
	drawLine(x+2.0*size,y,x+size,y+k);
	drawLine(x+2.0*size,y,x+size,y-k);
	drawLine(x+size,y+k,x-size,y+k);
	drawLine(x+size,y-k,x-size,y-k);
	drawLine(x-size,y+k,x-2*size,y);
	drawLine(x-size,y-k,x-2*size,y);
}

void GLPainter::drawHexGon(float x, float y, float size, const QColor& color)
{
	setColor(color);
	const float k = R3 * size;

	glBegin(GL_POLYGON);
	    glVertex2f(x + 2.0*size,y);
	    glVertex2f(x + size,y + k);
		glVertex2f(x - size,y + k);
		glVertex2f(x - 2.0*size,y);
		glVertex2f(x - size, y - k);
		glVertex2f(x + size, y - k);
		glVertex2f(x + 2.0*size, y);
	glEnd();
}

void GLPainter::drawHexGons(float x, float y,float size,int col,int row)
{
	auto viewport = World::getInstance().getViewport();

	size *= 0.5f;
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			float cx = x + 6.0*size*i - 3.0*size*j;
			float cy = y + size * j*R3;
			if(viewport->isContain(cx,cy))
				drawHexGon(cx, cy, size);
		}
	}
}

void GLPainter::drawTexture(uint32_t id,float* co,float* vertices)
{
	glBindTexture(GL_TEXTURE_2D,id);

	glBegin(GL_QUADS);
	for(int i = 0; i < 8; i++)
	{
		glTexCoord2f(co[i],co[i+1]);
		glVertex2f(vertices[i],vertices[i+1]);
		i++;
	}
	glEnd();
}