@echo off
REM Script to install Arduino libraries using arduino-cli

REM Initialize Arduino CLI
arduino-cli config init

REM Update the bookstore index
arduino-cli lib update-index

REM Install the ArduinoJson library
arduino-cli lib install "ArduinoJson"

REM Install the DHT sensor library
arduino-cli lib install "DHT sensor library"

REM Install the BH1750 sensor library
arduino-cli lib install "BH1750"

echo Libraries installed correctly.
pause
