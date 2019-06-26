#include <qrandom.h>
#include "rhinoMath.h"
#include <iostream>

void saRandomSwap(int n,int& i,int& j)
{
	i = j = 0;
	while(true)
	{
		i = qrand() % n;
		j = qrand() % n;

		if(i != j)
			break;
	}
}

bool saAccpet(float current,float temp,float t)
{
	if (current > temp)
		return true;

	float delta = temp - current;
	return rand() <= std::exp(-delta/t) * RAND_MAX;
}

float saDistance2(const QList<QPointF>& from,const QList<QPointF>& to)
{
	float distance = 0.0f;
	for (int i = 0; i < from.size(); i++)
	{
		distance += rhino::distance2<float>(to[i].x(), to[i].y(), from[i].x(), from[i].y());
	}
	return distance;
}

float sa(const QList<QPointF>& to,QList<QPointF>& from,int n,float high,float low,float at)
{
	if(to.size() != from.size())
		return -1.0;

	if(to.isEmpty())
		return 0.0;

	if(to.size() == 1)
	{
		from = to;
		return rhino::distance2<float>(to[0].x(), to[0].y(), from[0].x(), from[0].y());
	}

	if(high < low)
		std::swap(high,low);

	float distance = saDistance2(from,to);

	const int l = n * to.size();
	float t = high;

	QList<QPointF> current(from);

	while (t >= low)
	{
		for (int i = 0; i < l; i++)
		{
			int x, y;
			saRandomSwap(to.size(),x,y);
			rhino::swap<QPointF>(current[x],current[y]);
			float d = saDistance2(to,current);
			bool accpet = saAccpet(distance,d,t);
			if(accpet)
			{
				distance = d;
			}
			else
				rhino::swap<QPointF>(current[x], current[y]);
		}
		t *= at;
	}

	from = current;
	return distance;
}