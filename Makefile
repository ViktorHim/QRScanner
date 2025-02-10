.PHONY: all build clean run
EXE_NAME = QRScanner
DESTINATION = res

all: configure build

build:
	cmake --build build
configure:
	cmake -B build
run:
	@if exist bin\$(EXE_NAME).exe (bin\$(EXE_NAME).exe ${DESTINATION}) else (echo "Executable not found!")

clean:
	@if exist build (rmdir /s /q build)
	@if exist bin (rmdir /s /q bin)
	@if exist thresholds_new.pnm (del /f /q thresholds_new.pnm)
