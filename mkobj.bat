@echo off
set FormatDirectory=%2
if not defined FormatDirectory set FormatDirectory=.\
echo.#include ^<%1^>> %FormatDirectory%%1.cpp
echo.#pragma once> %FormatDirectory%%1.hpp
echo.#include "%1.hpp"> %FormatDirectory%%1