#include "../include/worker_file_loader.hpp"
#include "../include/utils.hpp"

WorkerFileLoader::WorkerFileLoader(str filename) : filename(filename) {}

void WorkerFileLoader::run() {
    Adb adb = getAdb(filename);
    emit finished(adb);
}

