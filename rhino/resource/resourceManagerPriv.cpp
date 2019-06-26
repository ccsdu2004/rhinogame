#include <QImage>
#include <QDebug>
#include "resourceManagerPriv.h"

std::shared_ptr<QImage> ResourceManagerPriv::loadImage(const QString& file)
{
	auto image = images[file];
	if (image)
		return image;

	image = std::make_shared<QImage>();
	if (!image->load(file))
		return image;

	images[file] = image;
	return image;
}

std::shared_ptr<QOpenGLTexture> ResourceManagerPriv::buildTexture(std::shared_ptr<QImage> image)
{
	if(!image)
		return nullptr;

	auto texture = textures[image];
	if (texture)
		return texture;

	texture = std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target2D);
	texture->setData(image->mirrored());
	texture->setMinificationFilter(QOpenGLTexture::Nearest);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture->setWrapMode(QOpenGLTexture::Repeat);
	texture->bind();
	textures[image] = texture;
	return texture;
}
 
void ResourceManagerPriv::clearResources()
{
	foreach(auto item,textures)
		item->release();
	
	textures.clear();
	images.clear();
}