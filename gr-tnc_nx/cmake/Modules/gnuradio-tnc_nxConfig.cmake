find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_TNC_NX gnuradio-tnc_nx)

FIND_PATH(
    GR_TNC_NX_INCLUDE_DIRS
    NAMES gnuradio/tnc_nx/api.h
    HINTS $ENV{TNC_NX_DIR}/include
        ${PC_TNC_NX_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_TNC_NX_LIBRARIES
    NAMES gnuradio-tnc_nx
    HINTS $ENV{TNC_NX_DIR}/lib
        ${PC_TNC_NX_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-tnc_nxTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_TNC_NX DEFAULT_MSG GR_TNC_NX_LIBRARIES GR_TNC_NX_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_TNC_NX_LIBRARIES GR_TNC_NX_INCLUDE_DIRS)
