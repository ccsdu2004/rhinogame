#include "textureAnimation.h"

TextureAnimation::TextureAnimation():
state(TextureAnimation_State_Stop),
currentTime(-1),
frameTime(20),
loop(true)
{
}

TextureAnimation::~TextureAnimation()
{
}

void TextureAnimation::start()
{
	state = TextureAnimation_State_Running;
}

void TextureAnimation::pause()
{
	state = TextureAnimation_State_Pause;
}

void TextureAnimation::resume()
{
	state = TextureAnimation_State_Running;
}

void TextureAnimation::stop()
{
	state = TextureAnimation_State_Stop;
	currentTime = 0;
}

void TextureAnimation::setFrameTime(int time)
{
	if(time < 0)
		time = 1;

	frameTime = time;
}

void TextureAnimation::addTexture(std::shared_ptr<QOpenGLTexture> texture)
{
	if(!texture)
		return;

	textures.push_back(texture);
	if(currentTime == -1)
		currentTime = 0;
}

void TextureAnimation::insertTexture(int pos,std::shared_ptr<QOpenGLTexture> texture)
{
	textures.insert(pos,texture);
	if(currentTime == -1)
		currentTime = 0;
}

int TextureAnimation::getTextureCount()
{
	return textures.size();
}

void TextureAnimation::glDraw()
{
	if(!isVisible())
		return;

	if(currentTime == -1)
		return;

	int current = currentTime / frameTime;
	textures.at(current)->bind();
}

void TextureAnimation::qtDraw(QWidget* widget)
{
	Q_UNUSED(widget)
}

void TextureAnimation::update(int time)
{
	if (state == TextureAnimation_State_Pause ||
		state == TextureAnimation_State_Stop)
		return;

	currentTime += time/frameTime;
	if (currentTime > getDuration())
		currentTime = 0;
}