#ifndef SPREADSHEET_HPP
#define SPREADSHEET_HPP

#include "consts.hpp"

class Spreadsheet {

public:
    Spreadsheet(
        Results& results, 
        Selections& selections, 
        Sheets& sheets, 
        list<str>& links
    );
    void save(str filename);

private:
    Results& results;
    Selections& selections;
    Sheets& sheets;
    list<str>& links;
    void writeInfo(str path, str datetime);
    void write2d(
        str sheetname,
        dict2d data,
        list<list<str>> columns,
        list<str> labels
    );
    void write3d(
        str sheetname,
        dict3d data,
        list<list<str>> columns,
        list<str> labels,
        int expr
    );
    void writeSumOfAspects(str sheetname);
    void writeAspects(str sheetname);
    void writeMidpoints(str sheetname);
    void writeStaircase3d(str sheetname, dict3d& result);
    void writeStaircase4d(str sheetname, dict4d& result);

};

#endif // SPREADSHEET_HPP

