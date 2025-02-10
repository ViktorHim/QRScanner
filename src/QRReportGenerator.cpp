#include "QRReportGenerator.h"

QRReportGenerator::QRReportGenerator()
{
}

QRReportGenerator::~QRReportGenerator()
{
}

void QRReportGenerator::generate(QRDataList list)
{
    std::ofstream file("report.html");

    if(!file.is_open())
    {
        std::cerr << "cannot open file" << std::endl;
        return;
    }

    file << "<!DOCTYPE html>"
    "<html lang=\"en\">"
    "<head>"
    "<meta charset=\"UTF-8\" />"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />"
    "<title>QR-коды</title>"
    "</head>"
    "<body>"
    "<style>"
    ".image {"
    "height: 300px;"
    "width: 500px;"
    "object-fit: contain;"
    "}"
    ".container {"
    "display: flex;"
    "flex-direction: column;"
    "align-items: center;"
    "}"
    ".card {"
    "background-color: #8bdaff;"
    "padding: 10px;"
    "border-radius: 5px;"
    "margin-bottom: 10px;"
    "color: white;"
    "}"
    ".card.error"
    "{"
      "background-color: #ff7878;"
    "}"
    "button {"
    "color: white;"
    "cursor: pointer;"
    "background-color: #12d01f;"
    "padding: 10px;"
    "border: none;"
    "border-radius: 3px;"
    "}"
    "</style>"
    "<script>"
    "document.addEventListener(\"DOMContentLoaded\", () => {"
    "const items = document.querySelectorAll(\"button\");"
    "const texts = document.querySelectorAll(\"p\");"
    "items.forEach((el) => {"
    "el.addEventListener(\"click\", (e) => {"
    "const id = e.target.dataset.btn;"
    "texts.forEach(async (text) => {"
    "const textId = text.dataset.text;"
    "if (textId == id) {"
    "try {"
    "await navigator.clipboard.writeText(text.dataset.value);"
    "} catch (err) {"
    "alert('Ошибка копирования:' + err);"
    "}}});});});});"
    "</script>"
    "<div class='container'>";


    for(auto& qrData : list)
    {
        bool isEmpty = qrData.second.empty();
        std::string data =isEmpty  ? "not found" : qrData.second;
        std::string path = qrData.first;

        if(isEmpty)
        {
            file << "<div class=\"card error\">";
            file << "<img class=\"image\" src=\"" << path << "\">";
            file << "<p>QRcode is not defined</p>";
        }
        else
        {
            file << "<div class=\"card\">";
            file << "<img class=\"image\" src=\"" << path << "\">";
            file << "<p data-text=\"" << path <<"\" data-value=\"" << data <<"\">QRcode in " << path <<" : " << data << "</p>";
            file << "<button data-btn=\"" << path <<"\">Copy</button>";
        }

        file << "</div>";
    }

    file << "</div></body></html>";

    file.close();
}