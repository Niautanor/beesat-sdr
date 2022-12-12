/*
 * Copyright 2022 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(local_extrema_detect.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(1c6cdedc2f9c64ecaf7e5db93aed0e58)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/tnc_nx/local_extrema_detect.h>
// pydoc.h is automatically generated in the build directory
#include <local_extrema_detect_pydoc.h>

void bind_local_extrema_detect(py::module& m)
{

    using local_extrema_detect    = ::gr::tnc_nx::local_extrema_detect;


    py::class_<local_extrema_detect, gr::block, gr::basic_block,
        std::shared_ptr<local_extrema_detect>>(m, "local_extrema_detect", D(local_extrema_detect))

        .def(py::init(&local_extrema_detect::make),
           py::arg("hist"),
           py::arg("threshold"),
           py::arg("gain"),
           D(local_extrema_detect,make)
        )
        




        
        .def("hist",&local_extrema_detect::hist,       
            D(local_extrema_detect,hist)
        )


        
        .def("threshold",&local_extrema_detect::threshold,       
            D(local_extrema_detect,threshold)
        )


        
        .def("gain",&local_extrema_detect::gain,       
            D(local_extrema_detect,gain)
        )

        ;




}








