#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QtGlobal>

#include "window.h"


int main(int argc, char *argv[]) {

  Q_ASSERT(QT_VERSION >= QT_VERSION_CHECK(5, 0, 0));

  QApplication application(argc, argv);

  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addOption(QCommandLineOption("no-gui"));
  parser.process(application);

  if (!parser.isSet("no-gui")) {
    Window window;
    window.show();
    window.raise();
    return application.exec();
  }
}
