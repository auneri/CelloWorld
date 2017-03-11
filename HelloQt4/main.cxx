#ifdef _WIN32
#  pragma warning(push)
#endif

#include <QApplication>

#include "window.h"

#ifdef _WIN32
#  pragma warning(pop)
#endif


int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  Window window;
  window.show();
  window.raise();
  return application.exec();
}
