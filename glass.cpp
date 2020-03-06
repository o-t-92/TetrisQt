#include <QPainter>
#include <QBrush>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPoint>
#include <QThread>
#include <QTime>
#include "glass.h"

QColor Glass::emptyCell = QColor(150, 150, 150);

void Glass::dropCell(int row, int col)
{
	for (int i = row; i > 0; i--)
		glassArray[i][col] = glassArray[i-1][col];
	glassArray[0][col] = emptyCell;
}

Glass::Glass(QWidget *parent) : QWidget(parent)
{
	gameOn = false;
	connect(this, Glass::signalInit, this, Glass::slotInit, Qt::QueuedConnection);
	emit(this->signalInit());
	cur = new Figure(W);
	next = new Figure(W);

}

Glass::~Glass()
{
	delete cur;
	delete next;
}

void Glass::clear()
{
	for (int i = 0; i < glassArray.length(); i++)
		glassArray[i].fill(emptyCell);
}

void Glass::acceptCurFigure()
{
	killTimer(timerId);
    for (int i = 0; i < 3; i++)
		glassArray[cur->top() + i][cur->column()] = cur->colorAt(i);
	gameOn = false;
	int points;
	do {
		QThread::msleep(250);
		points = checkGlass();
		repaint();
		score += points;
		emit(displayScore(score));
	} while (points > 0);
	gameOn = true;
	Figure* tmp = cur;
	cur = next;
	next = tmp;
	next->setPos(0, 0);
	cur->setPos(0, m_columns / 2);
	next->makeRandomColors();
    emit(drawPattern(next));
	timerId = startTimer(m_timerInterval);
}

int Glass::checkGlass()
{
	QVector<QPoint> toDrop;
	int i, j;
	for (i = m_rows-1; i >= 0; i--)
		for (j = 2; j < m_columns; j++)
			if (glassArray[i][j] != emptyCell &&
				glassArray[i][j] == glassArray[i][j-1] &&
				glassArray[i][j] == glassArray[i][j-2])
			{
				QPoint p1(i, j), p2(i, j-1), p3(i, j-2);
				if (!toDrop.contains(p1)) toDrop.append(p1);
				if (!toDrop.contains(p2)) toDrop.append(p2);
				if (!toDrop.contains(p3)) toDrop.append(p3);
			}
	for (j = 0; j < m_columns; j++)
		for (i = m_rows-3; i >= 0; i--)
			if (glassArray[i][j] != emptyCell &&
				glassArray[i][j] == glassArray[i+1][j] &&
				glassArray[i][j] == glassArray[i+2][j])
			{
				QPoint p1(i, j), p2(i+1, j), p3(i+2, j);
				if (!toDrop.contains(p1)) toDrop.append(p1);
				if (!toDrop.contains(p2)) toDrop.append(p2);
				if (!toDrop.contains(p3)) toDrop.append(p3);
			}
	for (i = 0; i < m_rows; i++)
		for (j = 0; j < m_columns; j++)
			if (toDrop.contains(QPoint(i, j)))
				dropCell(i, j);
	return toDrop.count();
}

void Glass::slotInit()
{
	glassArray.resize(m_rows);
    for (int i = 0; i < m_rows; i++)
		glassArray[i].resize(m_columns);
	clear();
	setFixedSize(m_columns * W + 1 , m_rows * W + 1);
}

void Glass::slotNewGame()
{
	gameOn = true;
	score = 0;
	clear();
	cur->setPos(0, m_columns / 2);
	next->setPos(0, 0);
	srand(QTime::currentTime().msec());
	cur->makeRandomColors();
	next->makeRandomColors();
	emit(drawPattern(next));
	timerId = startTimer(m_timerInterval);
	setFocus();
	repaint();
}


void Glass::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_columns; j++)
		{
			p.setBrush(QBrush(glassArray[i][j]));
			p.drawRect(j * W, i * W, W, W);
		}
	if (gameOn)
	{
		cur->paintFigure(p);
	}
}

void Glass::keyPressEvent(QKeyEvent* event)
{
	if (gameOn)
	{
		switch(event->key())
		{
		case Qt::Key_Left:
			if ((cur->column() > 0) &&
				(glassArray[cur->bottom()][cur->column()-1] == emptyCell))
				{
					cur->moveLeft();
				}
			break;
		case Qt::Key_Right:
			if ((cur->column() < m_columns-1) &&
				(glassArray[cur->bottom()][cur->column()+1] == emptyCell))
				{
					cur->moveRight();
				}
			break;
		case Qt::Key_Down:
			cur->rotateColors(false);
			break;
		case Qt::Key_Up:
			cur->rotateColors(true);
			break;
		case Qt::Key_Space:
			killTimer(timerId);
			timerId = startTimer(10);
			break;
		default:
			QWidget::keyPressEvent(event);
		}
		repaint();
	}
	else QWidget::keyPressEvent(event);
}

void Glass::timerEvent(QTimerEvent* event)
{
	if (cur->bottom() < m_rows-1 && glassArray[cur->bottom()+1][cur->column()] == emptyCell)
	{
		cur->moveDown();
	}
	else if (cur->top() > 0)
	{
		acceptCurFigure();
	}
	else
	{
		killTimer(timerId);
		QMessageBox::information(this, "Всё", "Вы проиграли!");
	}
	repaint();
}

