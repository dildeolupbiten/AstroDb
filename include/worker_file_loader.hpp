#ifndef WORKER_FILE_LOADER_HPP
#define WORKER_FILE_LOADER_HPP

#include "consts.hpp"

class WorkerFileLoader : public QThread {
    Q_OBJECT
public:
    WorkerFileLoader(str filename);

signals:
    void finished(const Adb& adb);

protected:
    void run() override;

private:
    str filename;
};

#endif // WORKER_FILE_LOADER_HPP
