@echo off

echo. > out.txt

for /r %%i in (*.hpp *.cpp) do (
   echo. >> out.txt
   echo //  >> out.txt
   echo // %%~ni%%~xi >> out.txt
   echo //  >> out.txt
   type "%%~fi" >> out.txt
   echo. >> out.txt
)

pause