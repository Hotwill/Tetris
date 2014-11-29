/***********************************************************************
 * Module:  ShapeFactory.h
 * Author:  Zhuang Hu
 * Modified: 2014年11月12日 14:35:25
 * Purpose: Declaration of the class ShapeFactory
 ***********************************************************************/

#ifndef _SHAPEFACTORY_H_
#define _SHAPEFACTORY_H_

#include "Shape.h"
#include <QColor>

int const MAX_COLORS = 14;
const QColor COLOR_SET[MAX_COLORS] = {
	Qt::red,
	Qt::darkRed,
	Qt::green,
	Qt::darkGreen,
	Qt::blue,
	Qt::darkBlue,
	Qt::cyan,
	Qt::darkCyan,
	Qt::magenta,
	Qt::darkMagenta,
	Qt::yellow,
	Qt::darkYellow,
	Qt::gray,
	Qt::darkGray,
};

class ShapeFactory
{
public:
   /* 生产各种各样的图形 */
   Shape* getShape(void);
};

#endif