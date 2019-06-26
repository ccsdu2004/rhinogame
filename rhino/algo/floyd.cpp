#include <boost/shared_array.hpp>
#include <QMap>
#include <QVector>
#include "../rhinoMath.h"

int findPairIDByPair(const QMap<int,QPoint>& ref, const QPoint& p)
{
	auto itr = ref.begin();
	while (itr != ref.end())
	{
		if (itr.value() == p)
			return itr.key();
		itr++;
	}
	return -1;
}

int floyd(const QList<QPoint>& vertices, const QList<QLine>& edges, const QPoint& from, const QPoint& to, QList<QPoint>& output)
{
	if (!(vertices.contains(from) && vertices.contains(to)))
		return -1;

	QList<QPoint> points(vertices);
	points.removeAll(from);
	points.removeAll(to);
	points.push_front(from);
	points.push_back(to);

	foreach(auto line,edges)
	{
		if (!points.contains(line.p1()))
			return -1;
		if (!points.contains(line.p2()))
			return -1;
	}

	const int MAX_VALUE = std::numeric_limits<short>::max();
	const int size = points.size();

	QVector<boost::shared_array<QPair<int, int>>> ptr(size);
	for (int i = 0; i < size; i++)
		ptr[i].reset(new QPair<int, int>[size]);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ptr[i][j].first = MAX_VALUE;
			ptr[j][i].first = MAX_VALUE;
		}
		ptr[i][i].first = 0;
	}

	QMap<int, QPoint> ref;
	for (int i = 0; i < size; i++)
		ref[i] = points[i];

	foreach(auto line, edges)
	{
		auto id1 = findPairIDByPair(ref, line.p1());
		auto id2 = findPairIDByPair(ref, line.p2());
		ptr[id1][id2].first = 1;
		ptr[id2][id1].first = 1;
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
			{
				if (ptr[i][j].first > ptr[i][k].first + ptr[k][j].first)
				{
					ptr[i][j].second = k;
					ptr[i][j].first = ptr[i][k].first + ptr[k][j].first;
				}
			}

	if (ptr[0][size - 1].first >= MAX_VALUE)
		return -1;

	output.clear();

	int i = size - 1;
	output.append(ref[i]);

	while (i != 0)
	{
		i = ptr[0][i].second;
		output.append(ref[i]);
	}

	std::reverse(output.begin(), output.end());
	return output.size() - 1;
}