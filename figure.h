#ifndef FIGURE_H
#define FIGURE_H
#include <QColor>
#include <QPainter>

class Figure
{
private:
	QColor figureArray[3];
    int m_i, m_j;
    uint w;

public:
	Figure(uint cellSize);
	void setPos(int row, int col);
    void moveLeft() { m_j--; }
	void moveRight() { m_j++; }
	void moveDown() { m_i++; }
	uint size() { return w; }
    int column() { return m_j; }
    int top() { return m_i; }
    int bottom() { return m_i + 2; }
	QColor colorAt(uint i) { return figureArray[i]; }
	void rotateColors(bool up);
	void makeRandomColors();
	void paintFigure(QPainter& painter);
	static Qt::GlobalColor cellColors[4];
};
#endif // FIGURE_H
