@echo off
git log -n 1 --pretty=format:"%%C(auto,red)%%H %%d %%s"
pause