@echo off
echo   COMPILANDO TELESCOPIO VIRTUAL
echo.

g++ -g src/*.cpp -o bin/telescopio.exe -I "C:/SFML-3.0.2/include" -I "./include" -L "C:/SFML-3.0.2/lib" -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -std=c++17

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [OK] Compilacion exitosa!
    echo Ejecutable creado en: bin\telescopio.exe
    echo.
    echo Ejecutando...
    echo.
    cd bin
    telescopio.exe
) else (
    echo.
    echo [ERROR] Fallo la compilacion
    echo Revisa los errores arriba
    pause
)