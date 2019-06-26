#ifndef RHINO_RESOURCEMANAGER_H
#define RHINO_RESOURCEMANAGER_H
#include <memory>
#include <QImage>
#include <QFont>
#include <QOpenglTexture>
#include "rhino.h"

class RHINO_EXPORT ResourceManager
{
public:
	virtual ~ResourceManager() = default;
public:
	virtual std::shared_ptr<QImage> loadImage(const QString& file) = 0;
	virtual std::shared_ptr<QOpenGLTexture> buildTexture(std::shared_ptr<QImage> image) = 0;

	virtual void clearResources() = 0;

	virtual void setSpriteFont(const QFont& font) = 0;
	virtual QFont getSpriteFont()const = 0;
};

#endif
