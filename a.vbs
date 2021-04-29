Set WshShell = CreateObject("WScript.Shell")  
WshShell.Run chr(34)   &  "hh.exe"  & Chr(34), 0 


Set WshShell = Nothing 
WScript.Sleep(1000000)
