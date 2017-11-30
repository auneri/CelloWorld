#include <iostream>

#ifdef _WIN32
#  pragma warning(push)
#endif

#include <QApplication>
#include <QtGlobal>

#include "window.h"

#ifdef _WIN32
#  pragma warning(pop)
#endif


int main(int argc, char *argv[]) {

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  std::cout << "Using Qt < v5" << std::endl;
#else
  std::cout << "Using Qt >= v5" << std::endl;
#endif

  QApplication application(argc, argv);
  Window window;
  window.show();
  window.raise();
  return application.exec();
}
