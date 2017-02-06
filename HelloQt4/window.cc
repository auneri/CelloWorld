#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "window.h"


Window::Window() {
  QWidget *widget = new QWidget(this);
  QPushButton *button = new QPushButton(tr("Quit"), widget);

  QObject::connect(button, SIGNAL(clicked()), this, SLOT(close()));

  QVBoxLayout *v_layout = new QVBoxLayout(widget);
  v_layout->addWidget(button);

  this->setCentralWidget(widget);
  this->setWindowTitle(tr("HelloQt"));
}
