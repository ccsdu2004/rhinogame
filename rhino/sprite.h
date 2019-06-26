#ifndef RHINO_SPRITE_H
#define RHINO_SPRITE_H
#include <QString>
#include <QColor>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QImage>
#include "drawable.h"
#include "entity.h"

class RHINO_EXPORT Sprite : public Drawable, public Entity
{
public:
	Sprite();
	explicit Sprite(const QPointF& position,const QSizeF& size);
	explicit Sprite(const QPointF& position,const QSizeF& size,std::shared_ptr<QImage> image);
	explicit Sprite(std::shared_ptr<QImage> image);
	virtual ~Sprite();
public:
	void setSpriteID(int id);
	int getSpriteID()const { return spriteID; }

	void setSpriteName(const QString& name);
	QString getSpriteName()const;

	void setSpriteText(const QString& text);
	QString getSpriteText()const;

	void setSpriteTextColor(const QColor& color);
	QColor getSpriteTextColor()const;

	void setSpriteImage(std::shared_ptr<QImage> image);

	void showBorder(bool show);
	bool isShowBorder()const;

	void setBorderColor(const QColor& color);
	QColor getBorderColor()const;
public:
	virtual void glDraw();
	virtual void qtDraw(QWidget* widget);
	virtual void update(int time);
private:
	void drawTexture();
	void drawBorder();
private:
	int spriteID;
	QString spriteName;
	std::shared_ptr<QImage> spriteImage;
	QString spriteText;
	QColor  spriteTextColor;
	bool   visibleBorder;
	QColor borderColor;
};

#endif