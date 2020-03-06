#include "nextfigure.h"
#include <QPainter>

NextFigure::NextFigure(QWidget *parent) : QWidget(parent)
{
}

void NextFigure::drawNextFigure(Figure* next)
{
	this->next = next;
	repaint();
}

void NextFigure::paintEvent(QPaintEvent* event)
{
	if (next)
	{
		QPainter p(this);
		next->paintFigure(p);
	}
}
