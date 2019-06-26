#include "rhinoWidget.h"
#include <QBoxLayout>
#include "glwidget.h"

rhino::rhino(QWidget *parent)
	: QWidget(parent)
{
	auto box = new QVBoxLayout(this);
	box->addWidget(new GLWidget(this));
	setFixedSize(662,502);
}
