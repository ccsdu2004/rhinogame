#ifndef RHINO_UTIL_H
#define RHINO_UTIL_H
#include <string>
#include <vector>
#include <QString>
#include "rhino.h"

bool RHINO_EXPORT decompress(const char* source,std::vector<unsigned char>& dest,std::size_t in,std::size_t expected);
std::string RHINO_EXPORT decodeBase64(const std::string& encode);

QString RHINO_EXPORT readAllBufferFromFile(const QString& filename);
void RHINO_EXPORT saveToFile(const QString& filename, const QString& content);

#endif