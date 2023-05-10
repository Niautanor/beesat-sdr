# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT tnc_nx_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT tnc_nx_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND tnc_nx_python_files
    tnc_python.cc
    nx_encoder_python.cc
    nx_decoder_python.cc
    tnc_b1_python.cc
    local_extrema_detect_python.cc
    gos_encoder_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(tnc_nx
   ../../..
   gr::tnc_nx
   "${tnc_nx_python_files}")

# copy in bindings .so file for use in QA test module
add_custom_target(
  copy_bindings_for_tests ALL
  COMMAND
    ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/*.so"
    ${CMAKE_BINARY_DIR}/test_modules/gnuradio/tnc_nx/
  DEPENDS tnc_nx_python)

install(TARGETS tnc_nx_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/tnc_nx COMPONENT pythonapi)
