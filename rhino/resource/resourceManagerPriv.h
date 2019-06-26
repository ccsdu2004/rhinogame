#ifndef RHINO_RESOURCE_MANAGER_PRIV_H
#define RHINO_RESOURCE_MANAGER_PRIV_H
#include <QMap>
#include "resourceManager.h"

class ResourceManagerPriv : public ResourceManager
{
public:
	ResourceManagerPriv() = default;
public:
	std::shared_ptr<QImage> loadImage(const QString& file);
	std::shared_ptr<QOpenGLTexture> buildTexture(std::shared_ptr<QImage> image);

	void clearResources();

	void setSpriteFont(const QFont& font) { spriteFont = font; }
	QFont getSpriteFont()const { return spriteFont; }
private:
	QMap<QString,std::shared_ptr<QImage>> images;
	QMap<std::shared_ptr<QImage>,std::shared_ptr<QOpenGLTexture>> textures;
	QFont spriteFont;
};

#endif