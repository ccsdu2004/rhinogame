#ifndef RHINO_GLCHECK_H
#define RHINO_GLCHECK_H

#ifdef RHINO_DEBUG
    #define glCheck(expr) do { expr; glCheckError(__FILE__, __LINE__, #expr); } while (false)
#else
    #define glCheck(expr) (expr)
#endif

void glCheckError(const char* file,unsigned int line,const char* expression);

#endif 
