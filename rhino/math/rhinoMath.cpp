#include "rhinoMath.h"

namespace rhino
{

void limitVector2D(QVector2D& vec,float value)
{
	auto dist = distance2<float>(vec.x(),vec.y(),0,0);
	if (dist <= value * value)
		return;

	bool zero = isZero(vec.x());
	if (zero)
	{
		vec.setY(value);
		return;
	}

	float r = vec.y() / vec.x();
	float x = std::sqrtf(value*value/(1+r*r));
	if(vec.x() < 0.0)
		x = -x;

	float y = x * r;
	vec.setX(x);
	vec.setY(y);
}

}