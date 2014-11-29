/***********************************************************************
 * Module:  Shape.cpp
 * Author:  Zhuang Hu
 * Modified: 2014年11月12日 14:44:34
 * Purpose: Implementation of the class Shape
 ***********************************************************************/

#include "Shape.h"
#include "global.h"
#include "Ground.h"
#include <QDebug>

Shape::Shape( int t /*= 0*/, int s /*= 0*/ )
	: type(t), status(s)
{
	color = Qt::blue;
	speed = DOWN_SPEED;
	running = true;
	paused = false;
	left = (GAME_WIDGET_WIDTH - shapeSize().width()) / 2;
	top = -shapeSize().height();
}

void Shape::moveLeft(void)
{
	left--;
	qDebug() << "Shape left, " << left << "," << top << "\n"; 
	emit shapeMoved();
}

void Shape::moveRighe(void)
{
	left++;
	qDebug() << "Shape right, (" << left << "," << top << ")\n"; 
	emit shapeMoved();
}

void Shape::moveDown(void)
{
	top++;
	qDebug() << "Shape down, (" << left << "," << top << ")\n"; 
	emit shapeMoved();
}

void Shape::rotate(void)
{
	status = (status + 1) % 4;
	qDebug() << "Shape rotate\n";
	emit shapeMoved();
}

void Shape::drawMe(QPainter &painter)
{
	painter.setBrush(QBrush(color));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(SHAPES[type][status][4 * i + j] == 1)
			{
				painter.drawRect((left + j) * CELL_WIDTH, (top + i) * CELL_WIDTH,
					CELL_WIDTH, CELL_WIDTH);
			}
		}
	}
}

void Shape::stop()
{
	running = false;
}

void Shape::pause()
{
	paused = true;
}

void Shape::restart()
{
	paused = false;
}

void Shape::run()
{
	while(running)
	{
		if (!paused)
		{
			moveDown();
		}
		QThread::msleep(speed);
	}
}


QSize Shape::shapeSize() const
{
	int w = 0;
	int h = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (SHAPES[type][status][4 * i + j] == 1)
			{
				h++;
				break;
			}
		}
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (SHAPES[type][status][4 * i + j] == 1)
			{
				w++;
				break;
			}
		}
	}

	return QSize(w, h);
}




// 获得图形的位置，横坐标
int Shape::getLeft(void) const
{
	return left;
}


// 获得图形的位置，y坐标
int Shape::getTop(void) const
{
	return top;
}


const int* Shape::getBody(void) const
{
	return SHAPES[type][status];
}


// 获得图形的颜色
QColor Shape::getColor(void) const
{
	return color;
}





// 判断图形是否能向左移动
bool Shape::canMoveLeft(const Ground& ground)
{
	////是否到达最左边
	//if (left <= 0)
	//{
	//	return false;
	//}

	//左边是否有Ground
	for (int i = 0; i < shapeSize().height(); i++)
	{
		int j = firstCellLocation(i);
		if (/*left + j >= 1 && */ground.isBarrier(top + i, left + j - 1))
		{
			return false;
		}
	}

	return true;
}


// 计算第row行的第一个格子的位置
int Shape::firstCellLocation(int row)
{
	for (int col = 0; col < 4; col++)
	{
		if (SHAPES[type][status][row * 4 + col] == 1)
		{
			return col;
		}
	}
	return -1;	//没有格子，返回-1
}


// 判断图形能否向右移动
bool Shape::canMoveRight(const Ground& ground)
{
	////是否到达最右边
	//if (left + shapeSize().width() >= GAME_WIDGET_WIDTH)
	//{
	//	return false;
	//}

	//右边是否有障碍物
	for (int i = 0; i < shapeSize().height(); i++)
	{
		int j = lastCellLocation(i);
		if (/*left + j + 1 <= GAME_WIDGET_WIDTH - 1 &&*/
			ground.isBarrier(top + i, left + j + 1))
		{
			return false;
		}
	}

	return true;
}

int Shape::lastCellLocation( int row )
{
	for (int col = shapeSize().width() - 1; col >= 0; col--)
	{
		if (SHAPES[type][status][4 * row + col] == 1)
		{
			return col;
		}
	}
	return -1;	////没有格子，返回-1
}


// 判断图形是否能向下移动
bool Shape::canMoveDown(const Ground& ground)
{
	////判断是否到达最底部
	//if (top + shapeSize().height() >= GAME_WIDGET_HEIGHT)
	//{
	//	return false;
	//}

	//判断下面是否有障碍物
	for (int j = 0; j < shapeSize().width(); j++)
	{
		int i = buttonCellLocation(j);
		if (/*top + i + 1 <= GAME_WIDGET_HEIGHT - 1 &&*/
			ground.isBarrier(top + i + 1, left + j))
		{
			return false;
		}
	}
	return true;
}


// 计算col列的最下面一个格子的位置
int Shape::buttonCellLocation(int col)
{
	for (int row = shapeSize().height() - 1; row >= 0; row--)
	{
		if (SHAPES[type][status][4 * row + col] == 1)
		{
			return row;
		}
	}
	return -1;	//没有格子，返回-1
}


// 判断图形时候能旋转
bool Shape::canRotate(const Ground& ground)
{
	Shape rotateShape(type, (status + 1) % 4);	//旋转之后的图形

	//旋转后的图形是否操作边界
	//if (left + rotateShape.shapeSize().width() > GAME_WIDGET_WIDTH ||
	//	top + rotateShape.shapeSize().height() > GAME_WIDGET_HEIGHT)
	//{
	//	return false;
	//}

	//旋转后的图形是否与ground有冲突
	const int *p = rotateShape.getBody();
	for (int i = 0; i < rotateShape.shapeSize().height(); i++)
		for(int j = 0; j < rotateShape.shapeSize().width(); j++)
			if (p[4 * i + j] == 1 && ground.isBarrier(top + i, left + j))
			{
				return false;
			}

			return true;
}


int Shape::getType(void)
{
	return type;
}


int Shape::getStatus(void)
{
	return status;
}


// 是否是暂停状态
bool Shape::isPaused(void)
{
	return paused;
}

void Shape::setColor( const QColor& c )
{
	color = c;
}

void Shape::gotoGroundDirectly( const Ground& ground )
{
	qDebug() << "Shape::gotoGroundDirectly()\n";
	int d = INT_MAX;
	for (int j = 0; j < shapeSize().width(); j++)
	{
		int x = 0;
		for (int i = buttonCellLocation(j) + top + 1; i < GAME_WIDGET_HEIGHT; i++)
		{
			if (!ground.isBarrier(i, left + j))
			{
				x++;
			}
			else
			{
				break;
			}
		}
		if (d > x)
		{
			d = x;
		}
	}
	top += d;

	emit shapeMoved();
}
