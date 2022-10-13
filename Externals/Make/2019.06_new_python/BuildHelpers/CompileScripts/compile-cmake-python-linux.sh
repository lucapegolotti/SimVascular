#
# python
#

REPLACEME_SV_SPECIAL_COMPILER_SCRIPT

export CC=REPLACEME_CC
export CXX=REPLACEME_CXX

rm -Rf REPLACEME_SV_TOP_BIN_DIR_PYTHON
mkdir -p REPLACEME_SV_TOP_BIN_DIR_PYTHON
chmod u+w,a+rx REPLACEME_SV_TOP_BIN_DIR_PYTHON

rm -Rf REPLACEME_SV_TOP_BLD_DIR_PYTHON
mkdir -p REPLACEME_SV_TOP_BLD_DIR_PYTHON
pushd REPLACEME_SV_TOP_BLD_DIR_PYTHON

/usr/local/bin/cmake -G REPLACEME_SV_CMAKE_GENERATOR \
   -DSV_EXTERNALS_TOPLEVEL_BIN_DIR:PATH=REPLACEME_SV_FULLPATH_BINDIR \
   -DBUILD_TESTING:BOOL=OFF \
   -DBUILD_LIBPYTHON_SHARED:BOOL=ON \
   -DENABLE_SSL:BOOL=ON \
   -DBUILTIN_SSL:BOOL=ON \
   -DBUILTIN_HASHLIB:BOOL=ON \
   -DUSE_SYSTEM_OpenSSL:BOOL=OFF \
   -DOPENSSL_INCLUDE_DIR:PATH=REPLACEME_SV_OPENSSL_INC_DIR \
   -DOPENSSL_LIBRARIES:FILEPATH=REPLACEME_SV_OPENSSL_LIBRARIES \
   -DENABLE_CTYPES:BOOL=ON \
   -DBUILTIN_CTYPES:BOOL=ON \
   -DCMAKE_INSTALL_PREFIX:PATH=REPLACEME_SV_TOP_BIN_DIR_PYTHON \
   -DCMAKE_BUILD_TYPE:STRING=REPLACEME_SV_CMAKE_BUILD_TYPE \
   -DPYTHON_VERSION=REPLACEME_SV_PYTHON_FULL_VERSION \
   -DENABLE_SQLITE3:BOOL=ON \
   -DSQLITE3_INCLUDE_PATH:PATH=REPLACEME_SV_SQLITE3_INC_DIR \
   -DSQLITE3_LIBRARY:FILEPATH=REPLACEME_SV_SQLITE3_LIBRARY \
   -DENABLE_TKINTER:BOOL=ON \
   -DUSE_SYSTEM_TCL:BOOL=OFF \
   -DTCL_INCLUDE_PATH:PATH=REPLACEME_SV_TOP_BIN_DIR_TCL/include \
   -DTCL_LIBRARY:FILEPATH=REPLACEME_SV_TOP_BIN_DIR_TCL/lib/REPLACEME_SV_TCL_LIB_NAME \
   -DTCL_TCLSH:FILEPATH=REPLACEME_SV_TOP_BIN_DIR_TCL/bin/REPLACEME_SV_TCLSH_EXECUTABLE \
   -DTK_INCLUDE_PATH:PATH=REPLACEME_SV_TOP_BIN_DIR_TK/include \
   -DTK_LIBRARY:FILEPATH=REPLACEME_SV_TOP_BIN_DIR_TK/lib/REPLACEME_SV_TK_LIB_NAME \
   -DTK_WISH:FILEPATH=REPLACEME_SV_TOP_BIN_DIR_TK/bin/REPLACEME_SV_WISH_EXECUTABLE \
   -DCMAKE_INSTALL_RPATH:PATH=REPLACEME_SV_TOP_BIN_DIR_PYTHON/lib:REPLACEME_SV_TOP_BIN_DIR_PYTHON/lib/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION/lib-dynload \
REPLACEME_SV_TOP_SRC_DIR_PYTHON

REPLACEME_SV_MAKE_CMD REPLACEME_SV_PYTHON_MAKE_FILENAME REPLACEME_SV_MAKE_BUILD_PARAMETERS

REPLACEME_SV_MAKE_CMD REPLACEME_SV_PYTHON_MAKE_FILENAME REPLACEME_SV_MAKE_INSTALL_PARAMETERS

# create a wrapper script for python executable

echo "#!/bin/bash -f" > REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "if [ -z \${PYTHONPATH+x} ]; then" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython 
echo "  OLDPYTHONPATH=\"\"" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython 
echo "else" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "  OLDPYTHONPATH=\$PYTHONPATH" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "  OLDPYTHONPATH=\${PYTHONPATH//;/:/}" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "fi" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "export PYTHONHOME=REPLACEME_SV_TOP_BIN_DIR_PYTHON" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "export LD_LIBRARY_PATH=\$PYTHONHOME/lib:\$LD_LIBRARY_PATH" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "export PYTHONPATH=REPLACEME_SV_TOP_BIN_DIR_PYTHON/lib/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION/lib-dynload:REPLACEME_SV_TOP_BIN_DIR_PYTHON/lib:REPLACEME_SV_TOP_BIN_DIR_PYTHON/lib/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION:REPLACEME_SV_TOP_BIN_DIR_PYTHON/lib/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION/site-packages:\$OLDPYTHONPATH" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "if [ \"\$#\" -eq 0 ]; then" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "  REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION " >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "elif [ \"\$#\" -eq 1 ]; then" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "  REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION \"\$1\" " >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "elif [ \"\$#\" -eq 2 ]; then" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "  REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION \"\$1\" \"\$2\" " >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "elif [ \"\$#\" -eq 3 ]; then" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "  REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION \"\$1\" \"\$2\" \"\$3\" " >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "else" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "  REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/pythonREPLACEME_SV_PYTHON_MAJOR_VERSION.REPLACEME_SV_PYTHON_MINOR_VERSION \"\$1\" \"\$2\" \"\$3\" \"\${@:4}\" " >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
echo "fi" >> REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython
chmod u+w,a+rx REPLACEME_SV_TOP_BIN_DIR_PYTHON/bin/svpython

REPLACEME_SV_SPECIAL_COMPILER_END_SCRIPT

popd
