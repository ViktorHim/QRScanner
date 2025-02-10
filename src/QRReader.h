#ifndef QRREADER_H
#define QRREADER_H
#include <ZXing/ReadBarcode.h>
#include <ZXing/BarcodeFormat.h>
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

typedef std::vector<std::pair<std::string, std::string>> QRDataList;
typedef std::pair<std::string, std::string> QRData;
typedef uint8_t Pixel;

class QRReader
{
private:
    std::string readQr(Pixel * data, int width, int height);
public:

    QRReader(/* args */);
    ~QRReader();

    QRDataList decodeQRFromDir(std::string path);
    void generateReport(QRDataList list);
};
#endif