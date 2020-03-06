#ifndef GLASS_H
#define GLASS_H

#include <QVector>
#include <QWidget>
#include "figure.h"

class Glass : public QWidget
{
	Q_OBJECT
    Q_PROPERTY(int rows READ rows WRITE setRows)
    Q_PROPERTY(int columns READ columns WRITE setColumns)
	Q_PROPERTY(uint timerInterval READ timerInterval WRITE setTimerInterval)

private:
    int m_rows, m_columns;
	bool gameOn;
	uint score;
	QVector<QVector<QColor>> glassArray;
	Figure* cur;
	Figure* next;
	int timerId;
	uint m_timerInterval;
	void dropCell(int row, int col);

public:
	static const uint W = 20;
	static QColor emptyCell;
	explicit Glass(QWidget *parent = 0);
	~Glass();
    int rows() const { return m_rows; }
    int columns() const { return m_columns; }
	uint timerInterval() const { return m_timerInterval; }
	void clear();
	void acceptCurFigure();
	int checkGlass();

signals:
	void signalInit();
	void drawPattern(Figure* next);
	void displayScore(int);

public slots:
    void setRows(int rows)
    {
        if(rows > 0)
            m_rows = rows;
    }
    void setColumns(int columns)
    {
        if(columns > 0)
            m_columns = columns;
    }
	void setTimerInterval(uint msecs) { m_timerInterval = msecs; }
	void slotInit();
	void slotNewGame();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void timerEvent(QTimerEvent* event);
};

#endif // GLASS_H
