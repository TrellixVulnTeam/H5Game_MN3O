@ECHO OFF

rem --------------------update svn

cd %~dp0
svn cleanup .
svn up .

rem ---------------------build msg
cd ..\..\client\tool
rem SET PLUGINS=..\src\Assets\plugins
SET msgHandlerFact=..\src\Assets\game\fact\MsgHandlerFact.cs
SET msgHandler=..\src\Assets\game\msg
SET msgHelper=..\src\Assets\game\MsgHelper
SET msgexp=..\src\Assets\exp\msg

rem svn cleanup %PLUGINS%
rem svn up --accept tf --force %PLUGINS%
svn up --accept tf --force %msgHandlerFact%

svn cleanup %msgexp%
svn up --accept tf --force %msgexp%

svn cleanup %msgHandler%
svn up --accept tf --force %msgHandler%

svn cleanup %msgHelper%
svn up --accept tf --force %msgHelper%

rem set a=%CD%
rem echo %a% >aUTOSVN.log
call build_msg.bat


rem ---------------------svn ci

rem svn ci %PLUGINS%\msg.* -m "auto build msg.dll"

svn ci %msgHandlerFact% -m "auto build msg.dll"

svn ci %msgexp%\*.cs -m "auto build msg"

svn add --force %msgHandler%\*.cs >nul
svn ci %msgHandler%\*.cs -m "auto build msg handler"

svn add --force %msgHelper%\*.cs >nul
svn ci %msgHelper%\*.cs -m "auto build msg helper"
