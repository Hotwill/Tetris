/***********************************************************************
 * Module:  Ground.h
 * Author:  Zhuang Hu
 * Modified: 2014年11月12日 14:48:59
 * Purpose: Declaration of the class Ground
 * Comment: 表示已经落下的图形
 ***********************************************************************/

#ifndef _GROUND_H_
#define _GROUND_H_

#include "global.h"
#include <QPainter>

class Shape;
class Ground
{
public:
	Ground();

	/* 显示自己 */
	void drawMe(QPainter &painter);

	// 接收落下的图形，并返回消去的满行的数目
	int accept(const Shape& shape);

	// 判断在点(row, col)处是否是障碍物
	bool isBarrier(int row, int col) const
	{
		if (col < 0 || col >= COLS || row >= ROWS)
		{
			return true;
		}
		if (row < 0)
		{
			return false;
		}
		return isGround[row][col];
	}
	//判断是否所有的行都有障碍物了，事实上，只需要判断第0行
	bool isFull() const;

	void clean();

private:
	// 判断row行是否已满
	bool isRowFull(int row) const;
	// 删除第row行
	void deleteRow(int row);

private:
	static const int ROWS = GAME_WIDGET_HEIGHT;
	static const int COLS = GAME_WIDGET_WIDTH;
	//记录每一个格子是否是障碍物
	bool isGround[ROWS][COLS];
	//记录每块障碍物的颜色
	QColor colors[ROWS][COLS];
};

#endif