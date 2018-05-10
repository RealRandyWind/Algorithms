mkdir %1
echo. 2>.\%1\%1.cpp
echo."%%VCINSTALLDIR%%Auxiliary\Build\vcvarsall" %%1>.\%1\init_cl.bat
echo.cl /I ..\Core %1.cpp /EHsc>.\%1\make.bat