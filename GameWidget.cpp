/***********************************************************************
 * Module:  GameWidget.cpp
 * Author:  Zhuang Hu
 * Modified: 2014年11月12日 13:46:51
 * Purpose: Implementation of the class GameWidget
 ***********************************************************************/

#include "GameWidget.h"
#include "global.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>

GameWidget::GameWidget()
{
	setFixedSize(GAME_WIDGET_WIDTH * CELL_WIDTH, GAME_WIDGET_HEIGHT * CELL_WIDTH);
	backgroundColor.setRgb(30, 40, 50);
	linesColor = Qt::black;
	shape = NULL;

	newGame();
}

GameWidget::~GameWidget()
{
	delete shape;
}

////////////////////////////////////////////////////////////////////////
// Name:       GameWidget::display()
// Purpose:    Implementation of GameWidget::display()
// Comment:    显示游戏窗口
// Return:     void
////////////////////////////////////////////////////////////////////////

void GameWidget::drawMe(QPainter &painter)
{
	//画背景
	painter.fillRect(0, 0, this->width(), this->height(), backgroundColor);

	painter.setPen(QPen(linesColor));
	//画横线
	for (int i = 0; i <= GAME_WIDGET_HEIGHT; i++)
	{
		painter.drawLine(0, i * CELL_WIDTH, this->width(), i * CELL_WIDTH);
	}
	//画竖线
	for (int i = 0; i <= GAME_WIDGET_WIDTH; i++)
	{
		painter.drawLine(i * CELL_WIDTH, 0, i * CELL_WIDTH, this->height());
	}
}

void GameWidget::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	
	this->drawMe(painter);
	if (shape != NULL)
	{
		shape->drawMe(painter);
	}
	ground.drawMe(painter);
}

void GameWidget::keyPressEvent(QKeyEvent *e)
{
	if (shape->isRunning())
	{
		switch (e->key())
		{
		case Qt::Key_Left:
			if (!shape->isPaused() && shape->canMoveLeft(ground))
			{
				shape->moveLeft();
			}
			break;
		case Qt::Key_Right:
			if (!shape->isPaused() && shape->canMoveRight(ground))
			{
				shape->moveRighe();
			}
			break;
		case Qt::Key_Up:
			if (!shape->isPaused() && shape->canRotate(ground))
			{
				shape->rotate();
			}
			break;
		case Qt::Key_Down:
			if (!shape->isPaused() && shape->canMoveDown(ground))
			{
				shape->moveDown();
			}
			break;
		case Qt::Key_Space:
			if (shape->isPaused())
			{
				shape->restart();
			}
			else
			{
				shape->pause();
			}
			break;
		case Qt::Key_Return:
			if (!shape->isPaused())
			{
				shape->gotoGroundDirectly(ground);
			}
			break;
		}
	}
	else
	{
		newGame();
	}
}


void GameWidget::whenShapeMoved()
{
	update();

	if (!shape->canMoveDown(ground))
	{	//如果已经落到了地面
		ground.accept(*shape);
		update();

		if (ground.isFull())
		{
			gameOver();
			return;
		}

		//重新生产一个图形
		shape->terminate();
		shape->wait();
		delete shape;
		shape = shapeFactory.getShape();
		connect(shape, &Shape::shapeMoved, this, &GameWidget::whenShapeMoved);
		shape->start();
	}
}

void GameWidget::newGame()
{
	if (shape != NULL)
	{
		shape->terminate();
		shape->wait();
		delete shape;
		shape = NULL;
	}
	shape = shapeFactory.getShape();
	connect(shape, &Shape::shapeMoved, this, &GameWidget::whenShapeMoved);
	ground.clean();
	shape->start();
}

void GameWidget::gameOver()
{
	shape->stop();
	QMessageBox::information(this, tr("俄罗斯方块"), tr("Geme Over!"));
}
