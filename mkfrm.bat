@echo off
set FormatDirectory=.\Core\Formats\
mkdir %FormatDirectory%%1_Driver
echo.pragma once> %FormatDirectory%%1.hpp
echo.#include "%1.hpp"> %FormatDirectory%%1