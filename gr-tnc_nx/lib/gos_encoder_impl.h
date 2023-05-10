/* -*- c++ -*- */
/*
 * Copyright 2023 German Orbital Systems GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TNC_NX_GOS_ENCODER_IMPL_H
#define INCLUDED_TNC_NX_GOS_ENCODER_IMPL_H

#include <gnuradio/tnc_nx/gos_encoder.h>
#include <gnuradio/tnc_nx/mobitex_coding.h>
#include <gnuradio/tnc_nx/frame_composer.h>
#include <gnuradio/tnc_nx/nx_protocol.h>

namespace gr {
namespace tnc_nx {

class gos_encoder_impl : public gos_encoder
{
private:
    size_t	d_off;
    bool is_tnc;
    uint8_t sat_id;

    mobitex_coding tx;
    frame_composer fr;

    // compose and transmit a message
    void transmit_msg(pmt::pmt_t meta);

public:
    gos_encoder_impl(bool is_tnc, uint8_t sat_id);
    ~gos_encoder_impl();

		// handle incoming messages
		void handle_msg(pmt::pmt_t msg);
};

} // namespace tnc_nx
} // namespace gr

#endif /* INCLUDED_TNC_NX_GOS_ENCODER_IMPL_H */
