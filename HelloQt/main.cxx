#include <cassert>
#include <iostream>

#include <QApplication>
#include <QtGlobal>

#include "window.h"


int main(int argc, char *argv[]) {

  assert(QT_VERSION >= QT_VERSION_CHECK(5, 0, 0));

  QApplication application(argc, argv);
  Window window;
  window.show();
  window.raise();
  return application.exec();
}
