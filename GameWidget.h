/***********************************************************************
 * Module:  GameWidget.h
 * Author:  Zhuang Hu
 * Purpose: Declaration of the class GameWidget
 ***********************************************************************/

#ifndef _GAMEWIDGET_H_
#define _GAMEWIDGET_H_

#include <QWidget>
#include "ShapeFactory.h"
#include "Shape.h"
#include "Ground.h"

class GameWidget : public QWidget
{
	Q_OBJECT

public:
	GameWidget();
	~GameWidget();

	/* 显示游戏窗口 */
	void drawMe(QPainter &p);

//public slots:
	/* 新游戏 */
	void newGame();
	/* 游戏结束 */
	void gameOver();
	/* 当图形移动之后会调用这个函数 */
	void whenShapeMoved();

protected:
	void paintEvent(QPaintEvent *);
	void keyPressEvent(QKeyEvent *);

private:
	QColor backgroundColor;
	QColor linesColor;
	ShapeFactory shapeFactory;
	Shape* shape;
	Ground ground;
};

#endif
