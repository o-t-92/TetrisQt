#ifndef NEXTFIGURE_H
#define NEXTFIGURE_H

#include <QWidget>
#include "figure.h"

class NextFigure : public QWidget
{
	Q_OBJECT

	Figure* next;

public:
	explicit NextFigure(QWidget *parent = 0);

signals:

public slots:
	void drawNextFigure(Figure* next);

protected:
	virtual void paintEvent(QPaintEvent* event);
};

#endif // NEXTFIGURE_H
