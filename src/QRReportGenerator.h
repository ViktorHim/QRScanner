#ifndef QR_REPORT_GENERATOR_H
#define QR_REPORT_GENERATOR_H
#include "QRReader.h"
#include <fstream>
#include <iostream>
#include <string>
class QRReportGenerator
{
private:
public:
    QRReportGenerator();
    ~QRReportGenerator();

    void generate(QRDataList list);
};
#endif