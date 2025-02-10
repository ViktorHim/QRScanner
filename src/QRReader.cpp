#include "QRReader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

QRReader::QRReader(/* args */)
{
}

QRReader::~QRReader()
{
}

QRDataList QRReader::decodeQRFromDir(std::string path)
{
    std::vector<std::string> imagePaths;
    QRDataList list;

    if(fs::is_regular_file(path))
    {
        imagePaths.push_back(path);
    }
    else
    {
        for(auto& entry: fs::directory_iterator(path))
        {
            if(entry.is_regular_file())
            {
                std::string extension = entry.path().extension().string();
                if(extension == ".jpeg" 
                    || extension == ".jpg" 
                    || extension == ".png" 
                    || extension == ".bmp"
                    || extension == ".JPEG" 
                    || extension == ".JPG" 
                    || extension == ".PNG" 
                    || extension == ".BMP"
                )
                {
                    imagePaths.push_back(entry.path().string());
                }
            }
        }
    }

    for(auto& imagePath: imagePaths)
    {
        std::cout << "Processing " << imagePath << std::endl;
        int width, height, channels;

        Pixel * img_data = stbi_load(imagePath.c_str(), &width, &height, &channels, 1);

        if(!img_data)
        {
            std::cerr << "Failed to load image" <<std::endl;
            exit(-1);
        }

        std::string qr = readQr(img_data, width, height);

        list.push_back(QRData(imagePath , qr));

        stbi_image_free(img_data);
    }


    return list;
}

void QRReader::generateReport(QRDataList list)
{
}

std::string QRReader::readQr(Pixel * data, int width, int height)
{
    ZXing::ImageView view = ZXing::ImageView(data, width, height, ZXing::ImageFormat::Lum);
    auto options = ZXing::ReaderOptions()
    .setFormats(ZXing::BarcodeFormat::QRCode)
    .setTryHarder(true)
    .setTryRotate(true)
    .setTryDownscale(true);
    ZXing::Result result = ZXing::ReadBarcode(view, options);

    if(result.isValid())
    {
        return result.text();
    }
    
    return "";
}