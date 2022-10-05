#
# itk
#

#
# use shorted path if you want to use Visual Studio!
# vs 2013 requires a very short path (< 14 chars)!
# nmake requires total path (including drive letter) to be less than 50 chars!

REPLACEME_SV_SPECIAL_COMPILER_SCRIPT

export CC=REPLACEME_CC
export CXX=REPLACEME_CXX

rm -Rf REPLACEME_SV_TOP_BIN_DIR_ITK
mkdir -p REPLACEME_SV_TOP_BIN_DIR_ITK
chmod u+w,a+rx REPLACEME_SV_TOP_BIN_DIR_ITK

#
# copy files needed from build dir to bin dir for SV linking!
#

mkdir -p REPLACEME_SV_TOP_BIN_DIR_ITK/REPLACEME_SV_ITK_INCLUDE_DIR
chmod a+rwx REPLACEME_SV_TOP_BIN_DIR_ITK/REPLACEME_SV_ITK_INCLUDE_DIR
cp ITKHelpers/*.h REPLACEME_SV_TOP_BIN_DIR_ITK/REPLACEME_SV_ITK_INCLUDE_DIR

rm -Rf REPLACEME_SV_TOP_BLD_DIR_ITK
mkdir -p REPLACEME_SV_TOP_BLD_DIR_ITK
cd REPLACEME_SV_TOP_BLD_DIR_ITK

REPLACEME_SV_CMAKE_CMD -G REPLACEME_SV_CMAKE_GENERATOR \
   -DSV_EXTERNALS_TOPLEVEL_BIN_DIR:PATH=REPLACEME_SV_FULLPATH_BINDIR \
   -DCMAKE_INSTALL_PREFIX=REPLACEME_SV_TOP_BIN_DIR_ITK \
   -DCMAKE_BUILD_TYPE=REPLACEME_SV_CMAKE_BUILD_TYPE \
   -DBUILD_EXAMPLES=0 \
   -DBUILD_TESTING=0 \
   -DBUILD_SHARED_LIBS=1 \
   -DITK_USE_SYSTEM_GDCM=1 \
   -DITK_USE_SYSTEM_HDF5=1 \
   -DModule_ITKReview=1 \
   -DModule_ITKVtkGlue=1 \
   -DGDCM_DIR=REPLACEME_SV_TOP_BIN_DIR_GDCM/REPLACEME_SV_GDCM_CMAKE_LIB_DIR \
   -DHDF5_DIR=REPLACEME_SV_TOP_BIN_DIR_HDF5/REPLACEME_SV_HDF5_CMAKE_LIB_DIR \
   -DVTK_DIR=REPLACEME_SV_TOP_BIN_DIR_VTK/REPLACEME_SV_VTK_CMAKE_LIB_DIR \
   -DPython3_ROOT_DIR=/usr/local/sv/ext/2022.09/release/gl2/bin/gnu/7.5/x64/python-3.9.10/ \
REPLACEME_SV_TOP_SRC_DIR_ITK

REPLACEME_SV_MAKE_CMD REPLACEME_SV_ITK_MAKE_FILENAME REPLACEME_SV_MAKE_BUILD_PARAMETERS

REPLACEME_SV_MAKE_CMD REPLACEME_SV_ITK_MAKE_FILENAME REPLACEME_SV_MAKE_INSTALL_PARAMETERS

REPLACEME_SV_SPECIAL_COMPILER_END_SCRIPT



