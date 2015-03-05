REM bootstrap.bat - compile script modules and generate grammar_full.g for lc-compile
REM params:
REM    1: pSolutionDir
REM    2: pOutDir

SETLOCAL ENABLEDELAYEDEXPANSION
if errorlevel 1 echo unable to set delayed expansion

SET SCRIPT_SRC=%1libscript\src
SET SCRIPT_MODULES=foreign.mlc arithmetic.mlc array.mlc binary.mlc bitwise.mlc byte.mlc char.mlc codeunit.mlc date.mlc file.mlc list.mlc logic.mlc math-foundation.mlc math.mlc sort.mlc stream.mlc string.mlc system.mlc type.mlc type-convert.mlc unittest.mlc

SET ENGINE_SRC=%1engine\src
SET ENGINE_MODULES=engine.mlc canvas.mlc widget.mlc

SET LCBC=%2\lc-bootstrap-compile.exe

SET MODULE_PATH=%2\modules

IF NOT EXIST %MODULE_PATH%\ MKDIR %MODULE_PATH%

SET MODULE_FILES=
FOR %%m IN (%SCRIPT_MODULES%) DO SET MODULE_FILES=!MODULE_FILES! %SCRIPT_SRC%\%%m
FOR %%m IN (%ENGINE_MODULES%) DO SET MODULE_FILES=!MODULE_FILES! %ENGINE_SRC%\%%m

REM Compile script & engine modules
FOR %%m IN (%MODULE_FILES%) DO %LCBC% --modulepath %MODULE_PATH% %%m

REM Generate grammar_full.g
SET GRAMMAR_TEMPLATE=%1toolchain\lc-compile\src\grammar.g
SET GRAMMAR_OUTPUT=%toolchain\lc-compile\src\grammar_full.g
%LCBC% --bootstrap --modulepath %MODULE_PATH% --template %GRAMMAR_TEMPLATE% --output %GRAMMAR_OUTPUT% %MODULE_FILES%
