#ifndef WORKER_CALCULATIONS_HPP
#define WORKER_CALCULATIONS_HPP

#include "consts.hpp"

class WorkerCalculations : public QThread {
    Q_OBJECT
public:
    WorkerCalculations(
        QProgressBar* progress_bar,
        list<DataMap>& data1,
        list<DataMap>& data2,
        str calc_type_val,
        std::function<double(double x1, double x2, double n1, double n2)> func,
        QObject* parent = nullptr
    );
    void run() override;

signals:
    void progress(int value);
    void finished(int value);

private:
    QProgressBar* progress_bar = nullptr;
    list<DataMap>& data1;
    list<DataMap>& data2;
    str calc_type_val;
    std::function<double(double x1, double x2, double n1, double n2)> func;
    str getFilename();

};
#endif // WORKER_CALCULATIONS_HPP
