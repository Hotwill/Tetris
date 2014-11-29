/***********************************************************************
 * Module:  Ground.cpp
 * Author:  Zhuang Hu
 * Modified: 2014年11月12日 14:48:59
 * Purpose: Implementation of the class Ground
 * Comment: 表示已经落下的图形
 ***********************************************************************/

#include "Ground.h"
#include "Shape.h"
#include <QDebug>


Ground::Ground()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
		{
			isGround[i][j] = false;
			colors[i][j] = Qt::black;
		}


}


////////////////////////////////////////////////////////////////////////
// Name:       Ground::drawMe()
// Purpose:    Implementation of Ground::drawMe()
// Comment:    显示自己
// Return:     void
////////////////////////////////////////////////////////////////////////
void Ground::drawMe(QPainter &painter)
{
	painter.setPen(QPen(Qt::black));
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
		{
			if (isGround[i][j])
			{
				/*painter.fillRect(j * CELL_WIDTH, i * CELL_WIDTH, CELL_WIDTH,
								 CELL_WIDTH, colors[i][j]);*/
				painter.setBrush(QBrush(colors[i][j]));
				painter.drawRect(j * CELL_WIDTH, i * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH);
				
			}
		}
}

// 接收落下的图形，并返回消去的满行的数目
int Ground::accept(const Shape& shape)
{
	qDebug() << "Ground::accept()" << "\n";
	const int *p = shape.getBody();
	int left = shape.getLeft();
	int top = shape.getTop();
	QColor color = shape.getColor();

	//把shape所在的格子加入ground中
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (top + i >= 0 && p[4 * i + j] == 1)
			{
				isGround[top + i][left + j] = true;
				colors[top + i][left + j] = color;
			}
		}
	}

	int n = 0;	//记录满行的数目
	//删除满行
	for (int i = 0; i < shape.shapeSize().height(); i++)
	{
		if (isRowFull(top + i))
		{
			n++;
			deleteRow(top + i);
		}
	}

	return n;
}


// 判断row行是否已满
bool Ground::isRowFull(int row) const
{
	for (int col = 0; col < COLS; col++)
	{
		if (!isGround[row][col])
		{
			return false;
		}
	}
	return true;
}


// 删除第row行
void Ground::deleteRow(int row)
{
	//row之上的行全部向下移动一行
	for (int i = row; i >= 1; i--)
	{
		for (int j = 0; j < COLS; j++)
		{
			isGround[i][j] = isGround[i - 1][j];
			colors[i][j] = colors[i - 1][j];
		}
	}

	//第一行全部置为false
	for (int j = 0; j < COLS; j++)
	{
		isGround[0][j] = false;
		colors[0][j] = Qt::black;
	}
}

bool Ground::isFull() const
{
	for (int j = 0; j < COLS; j++)
	{
		if (isGround[0][j])
		{
			return true;
		}
	}
	return false;
}

void Ground::clean()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			isGround[i][j] = false;
		}
	}
}
