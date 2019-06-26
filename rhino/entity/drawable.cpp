#include "drawable.h"

Drawable::Drawable():
visible(true),
zOrder(0.0)
{
}

Drawable::~Drawable()
{
}

void Drawable::setVisible(bool show)
{
	visible = show;
}

void Drawable::show()
{
	visible = true;
}

void Drawable::hide()
{
	visible = false;
}

bool Drawable::isVisible()const
{
	return visible;
}

void Drawable::setZOrder(float order)
{
	zOrder = order;
}
