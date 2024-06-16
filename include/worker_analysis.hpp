#ifndef WORKER_ANALYSIS_HPP
#define WORKER_ANALYSIS_HPP

#include "consts.hpp"

class WorkerAnalysis : public QThread {
    Q_OBJECT
public:
    WorkerAnalysis(
        str type,
        QProgressBar* progress_bar,
        Selections& selections,
        Sheets& selected_sheets,
        list<AdbEntry> records,
        Results& results,
        QObject* parent = nullptr
    );
    int n;
    void run() override;
    void analyze();
    void select();

signals:
    void progress(int value);
    void finished(int value, list<AdbEntry> records);

private:
    QProgressBar* progress_bar = nullptr;
    str type = "";
    list<AdbEntry> records;
    Results& results;
    Selections& selections;
    Sheets& selected_sheets;
};
#endif // WORKER_ANALYSIS_HPP
