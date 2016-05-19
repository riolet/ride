#ifndef RIXPARSER_HANDLER_H
#define RIXPARSER_HANDLER_H
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(struct error_object** err, int* err_num, char* doc);
    ~Worker();
public slots:
    void process();
signals:
    void finished();
private:
    struct error_object **_err;
    int *_err_num;
    char *_doc;
};
#endif // RIXPARSER_HANDLER_H
