/***********************************************************************
 * Module:  ShapeFactory.cpp
 * Author:  Zhuang Hu
 * Modified: 2014年11月12日 14:35:25
 * Purpose: Implementation of the class ShapeFactory
 ***********************************************************************/

#include <QDebug>
#include <cstdlib>
#include <ctime>
#include "ShapeFactory.h"
#include "Shape.h"
#include "global.h"

////////////////////////////////////////////////////////////////////////
// Name:       ShapeFactory::getShape()
// Purpose:    Implementation of ShapeFactory::getShape()
// Comment:    生产各种各样的图形
// Return:     Shape
////////////////////////////////////////////////////////////////////////

Shape* ShapeFactory::getShape(void)
{
	srand(time(NULL));

	int type = rand() % SHAPE_TYPES;
	int status = rand() % SHAPE_STATUS;
	const QColor color = COLOR_SET[rand() % MAX_COLORS];

	Shape *shape = new Shape(type, status);
	shape->setColor(color);
	qDebug() << "Produce a shape, type=" << type << "status=" << status << "\n";
	return shape;
}