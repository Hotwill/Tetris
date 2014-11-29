/***********************************************************************
 * Module:  Shape.h
 * Author:  Zhuang Hu
 * Modified: 2014年11月12日 14:44:34
 * Purpose: Declaration of the class Shape
 ***********************************************************************/

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <QPainter>
#include <QThread>
#include <QColor>

class Ground;
class Shape : public QThread
{
	Q_OBJECT

public:
	Shape(int t = 0, int s = 0);
	int getType(void);
	int getStatus(void);
	/* 获得图形的位置，x坐标 */
	int getLeft(void) const;

	/* 获得图形的位置，y坐标 */
	int getTop(void) const;

	/* 获得表示图形的数组 */
	const int* getBody(void) const;

	/* 获得图形的颜色 */
	QColor getColor(void) const;

	/* 设置图形颜色 */
	void setColor(const QColor& c);

	/* 向左移动 */
	void moveLeft(void);

	/* 向右移动 */
	void moveRighe(void);

	/* 向下移动 */
	void moveDown(void);

	/* 顺时针旋转 */
	void rotate(void);

	/* 直接下落到地面 */
	void gotoGroundDirectly(const Ground& ground);

	/* 判断图形是否能向左移动 */
	bool canMoveLeft(const Ground& ground);

	/* 判断图形能否向右移动 */
	bool canMoveRight(const Ground& ground);

	/* 判断图形是否能向下移动 */
	bool canMoveDown(const Ground& ground);

	/* 判断图形时候能旋转 */
	bool canRotate(const Ground& ground);

	/* 是否是暂停状态 */
	bool isPaused(void);
	

	/* 游戏停止 */
	void stop();

	/* 游戏暂停 */
	void pause();

	/* 游戏重新开始 */
	void restart();

	/* 绘制图形，即将图形显示出来 */
	void drawMe(QPainter &painter);

	/* 获取图形的真实大小 */
	QSize shapeSize() const;

signals:
	/* 图形移动了信号 */
	void shapeMoved();

protected:
	/* 重载QThread的run()函数，实现多线程 */
	void run();

private:
	// 计算第row行的第一个格子的位置
	int firstCellLocation(int row);
	// 计算第row行的最后一个格子的位置
	int lastCellLocation(int row);
	// 计算col列的最下面一个格子的位置
	int buttonCellLocation(int col);

private:
	int type;
	int status;
	int left;
	int top;
	QColor color;	//图形的颜色
	int speed;		//多少毫秒下落一次
	bool running;	//游戏是否在运行中
	bool paused;	//游戏是否暂停
};

#endif