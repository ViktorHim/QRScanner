#include "QRReader.h"
#include "QRReportGenerator.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path>\n";
        return 1;
    }

    QRReader reader = QRReader();
    QRReportGenerator generator = QRReportGenerator();

    QRDataList list = reader.decodeQRFromDir(std::string(argv[1]));

    for(auto& qrData: list)
    {
        std::string data = qrData.second.empty() ? "not found" : qrData.second;
        std::cout << qrData.first << ":" << data << std::endl;
    }

    generator.generate(list);

    return 0;
}