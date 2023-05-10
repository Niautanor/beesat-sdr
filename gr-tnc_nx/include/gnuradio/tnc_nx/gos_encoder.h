/* -*- c++ -*- */
/*
 * Copyright 2023 German Orbital Systems GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TNC_NX_GOS_ENCODER_H
#define INCLUDED_TNC_NX_GOS_ENCODER_H

#include <gnuradio/block.h>
#include <gnuradio/tnc_nx/api.h>

namespace gr {
namespace tnc_nx {

/*!
 * \brief Encoder for the GOS Mobitex Variant. Similar to nx_encoder but with fewer features
 * \ingroup tnc_nx
 *
 */
class TNC_NX_API gos_encoder : virtual public gr::block
{
public:
    typedef std::shared_ptr<gos_encoder> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of tnc_nx::gos_encoder.
     *
     * To avoid accidental use of raw pointers, tnc_nx::gos_encoder's
     * constructor is in a private implementation
     * class. tnc_nx::gos_encoder::make is the public interface for
     * creating new instances.
     */
    static sptr make(bool is_tnc, uint8_t sat_id);
};

} // namespace tnc_nx
} // namespace gr

#endif /* INCLUDED_TNC_NX_GOS_ENCODER_H */
