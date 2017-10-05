#include "mainclass.h"
#include "data.h"
#include "install.h"
#include "log.h"
#include <QApplication>
#include <QErrorMessage>
#include <QString>

int mainclass::exec(int argc, char **argv) {
    options set;
    QString workDir;
#if OS == 0
    FILE *fp = popen("echo $(cd $(dirname $0) && pwd)", "r");
    char buf[256];
    fgets(buf, sizeof(buf) - 1, fp);
    pclose(fp);
    workDir = buf;
    workDir = workDir.left(workDir.indexOf('\n'));
#elif OS == 1
    workDir = getenv("%~dp0");
#endif
    log::message(0, __FILE__, __LINE__, QString("Work dir is ") + workDir);
    install ins(workDir);
    QApplication app(argc,argv);
    ins.read();
    (new Window(&ins, set.read_set(false), &set))->show();
    log::message(0, __FILE__, __LINE__, "Window exec");
    int res = app.exec();
    log::message(0, __FILE__, __LINE__, "Window closed");
    set.autowrite_set();
    ins.write();
    log::message(0, __FILE__, __LINE__, QString("Exiting... Returned ") + QString::number(res));
    return res;
}

















