#include "figure.h"
#include <QBrush>

Qt::GlobalColor Figure::cellColors[4] = { Qt::red, Qt::green, Qt::blue, Qt::yellow };

Figure::Figure(uint cellSize) : m_i(0), m_j(0), w(cellSize)
{
}

void Figure::setPos(int row, int col)
{
	m_i = row;
	m_j = col;
}

void Figure::rotateColors(bool up)
{
	int d = up ? 1 : -1;
	QColor tmp[3];
	memcpy(tmp, figureArray, sizeof(tmp));
	figureArray[0] = tmp[(d+3)%3];
	figureArray[1] = tmp[(d+4)%3];
    figureArray[2] = tmp[(d+5)%3];
}

void Figure::makeRandomColors()
{
	figureArray[0] = QColor(cellColors[rand()%4]);
	figureArray[1] = QColor(cellColors[rand()%4]);
	figureArray[2] = QColor(cellColors[rand()%4]);
}

void Figure::paintFigure(QPainter& painter)
{
	for (uint i = 0; i < 3; i++)
	{
		painter.setBrush(QBrush(figureArray[i]));
		painter.drawRect(m_j * w, (m_i + i) * w, w, w);
	}
}
