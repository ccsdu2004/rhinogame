#include <qopengl.h>
#include <QDebug>
#include <QString>
#include "glCheck.h"

void glCheckError(const char* file,unsigned int line,const char* expression)
{
    GLenum errorCode = glGetError();

    if(errorCode != GL_NO_ERROR)
    {
        QString fileString = file;
        QString error = "unknown error";
        QString description  = "no description";

        switch (errorCode)
        {
            case GL_INVALID_ENUM:
            {
                error = "GL_INVALID_ENUM";
                description = "An unacceptable value has been specified for an enumerated argument.";
                break;
            }

            case GL_INVALID_VALUE:
            {
                error = "GL_INVALID_VALUE";
                description = "A numeric argument is out of range.";
                break;
            }

            case GL_INVALID_OPERATION:
            {
                error = "GL_INVALID_OPERATION";
                description = "The specified operation is not allowed in the current state.";
                break;
            }

            case GL_STACK_OVERFLOW:
            {
                error = "GL_STACK_OVERFLOW";
                description = "This command would cause a stack overflow.";
                break;
            }

            case GL_STACK_UNDERFLOW:
            {
                error = "GL_STACK_UNDERFLOW";
                description = "This command would cause a stack underflow.";
                break;
            }

            case GL_OUT_OF_MEMORY:
            {
                error = "GL_OUT_OF_MEMORY";
                description = "There is not enough memory left to execute the command.";
                break;
            }

            /*case GLEXT_GL_INVALID_FRAMEBUFFER_OPERATION:
            {
                error = "GL_INVALID_FRAMEBUFFER_OPERATION";
                description = "The object bound to FRAMEBUFFER_BINDING is not \"framebuffer complete\".";
                break;
            }*/
        }

		fileString = fileString.mid(fileString.lastIndexOf("\\/")+1);

		qDebug() << "An internal OpenGL call failed in "
			<< fileString
			<< "(" << line << ")."
			<< "\nExpression:\n   " << expression
			<< "\nError description:\n   " << error << "\n   " << description;
    }
}


 