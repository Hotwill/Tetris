#include "GameWidget.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	GameWidget *widget = new GameWidget;
	widget->setWindowIcon(QIcon("俄罗斯方块.ico"));
    widget->setWindowTitle(QObject::tr("俄罗斯方块"));
	widget->show();

	return app.exec();
}
