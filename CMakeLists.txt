cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(QRScanner)

set(CMAKE_CXX_STANDARD 17)
find_package(ZXing CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/QRReader.cpp src/QRReportGenerator.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ZXing::Core ZXing::ZXing)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .exe)