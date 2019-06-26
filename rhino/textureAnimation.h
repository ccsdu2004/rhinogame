#ifndef RHINO_TEXTURE_ANIMATION_H
#define RHINO_TEXTURE_ANIMATION_H
#include <memory>
#include <QVector>
#include <QOpenGLTexture>
#include "drawable.h"

class RHINO_EXPORT TextureAnimation : public Drawable
{
public:
	TextureAnimation();
	~TextureAnimation();

#define TextureAnimation_State_Running 0
#define TextureAnimation_State_Pause   1
#define TextureAnimation_State_Stop    2
	void start();
	void pause();
	void resume();
	void stop();
	int  getState()const { return state; }

	void setFrameTime(int time);
	int  getFrameTime()const { return frameTime; }
	int  getDuration()const { return frameTime*textures.size(); }
	int  getCurrentTime()const { return currentTime; }

	void setLoop(bool lp) { loop = lp; }
	bool isLoop()const { return loop; }

	void addTexture(std::shared_ptr<QOpenGLTexture> texture);
	void insertTexture(int pos,std::shared_ptr<QOpenGLTexture> texture);
	int  getTextureCount();
public:
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
private:
	QVector<std::shared_ptr<QOpenGLTexture>> textures;
	int state;
	int currentTime;
	int frameTime;
	bool loop;

};

#endif
