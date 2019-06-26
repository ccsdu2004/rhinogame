#ifndef RHINO_MATH_H
#define RHINO_MATH_H
#include <QPoint>
#include <QLine>
#include <QVector2D>
#include <QList>
#include "rhino.h"

#define R3 1.73205

#ifndef PI
#define PI 3.1419265
#endif

namespace rhino
{

template <class T>
inline T distance2(T x1, T y1, T x2, T y2)
{
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

template<class T>
inline constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
	if (v < lo)
		return lo;
	else if (v > hi)
		return hi;
	return v;
}

template<class T>
inline void swap(T& left, T& right)
{
	T v = std::move(left);
	left = std::move(right);
	right = std::move(v);
}

inline bool isZero(float x) { return x > -0.00001 && x < 0.00001; }

void RHINO_EXPORT limitVector2D(QVector2D& vec,float value);

}

int RHINO_EXPORT floyd(const QList<QPoint>& vertices,const QList<QLine>& edges,const QPoint& from,const QPoint& to, QList<QPoint>& output);
float RHINO_EXPORT sa(const QList<QPointF>& to,QList<QPointF>& from,int n = 10,float high = 1000.0f,float low = 10.0f,float at = 0.999f);

#endif 