/* -*- c++ -*- */
/*
 * Copyright 2023 German Orbital Systems GmbH.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "gos_encoder_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace tnc_nx {

gos_encoder::sptr gos_encoder::make(bool is_tnc, uint8_t sat_id)
{
    return gnuradio::make_block_sptr<gos_encoder_impl>(is_tnc, sat_id);
}


/*
 * The private constructor
 */
gos_encoder_impl::gos_encoder_impl(bool is_tnc, uint8_t sat_id)
    : gr::block("gos_encoder",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
      d_off(0),
      is_tnc(is_tnc),
      sat_id(sat_id),
      tx(),
      fr(&tx)
{
    /********************************
     * SET UP I/O PORTS AND HANDLER *
     ********************************/
    // INPUT
    message_port_register_in(pmt::mp("in"));
    set_msg_handler(pmt::mp("in"), [this](auto&& arg) { return handle_msg(arg); });
    // OUTPUT (single baudrate only)
    message_port_register_out(pmt::mp("out"));
}

/*
 * Our virtual destructor.
 */
gos_encoder_impl::~gos_encoder_impl() {}

/*
 * MESSAGE HANDLER
 * 	- assemble data to mobitex-blocks, encode and transmit them
 * 	- set/unset relays-mode if neccessary
 */
void gos_encoder_impl::handle_msg(pmt::pmt_t msg)
{
    pmt::pmt_t meta = pmt::car(msg);
    pmt::pmt_t vector = pmt::cdr(msg);

    // identify parts of the message
    const uint8_t* m = pmt::u8vector_elements(vector, d_off);

    /*
    uint8_t satid = [&meta]() -> uint8_t {
        pmt::pmt_t key = pmt::mp("satid");
        pmt::pmt_t ref = pmt::dict_ref(meta, key, pmt::PMT_NIL);
        meta = pmt::dict_delete(meta, key);
        // TODO: log incorrect types but permit nil
        if (pmt::is_integer(ref))
            return pmt::to_long(ref);
        else
            // TODO: make configurable
            return 0x11;
    }();
    */

    // TODO: handle cases where the input vector is longer than 256 * 18 bytes
    // and report errors properly
    tx.cur.blocks = (d_off + 17) / 18;
    if (tx.cur.blocks == 0 || tx.cur.blocks > 32)
      return;

    if (is_tnc) {
      tx.cur.control[0] = tx.cur.blocks;
      tx.cur.control[1] = sat_id;
    } else {
      tx.cur.control[0] = sat_id;
      tx.cur.control[1] = tx.cur.blocks;
    }
    tx.encode_control(&tx.cur);

    for (int i = 0; i < tx.cur.blocks; i++) {
      for (int j = 0; j < 18; j++)
        tx.mob_data[i][j] = *m++;
      tx.encode_datablock(i);
    }

    transmit_msg(meta);
}

/********************
 * OUTPUT FUNCTIONS *
 ********************/
void gos_encoder_impl::transmit_msg(pmt::pmt_t meta)
{
    int count = NUM_OF_PAD_BYTES * 8;

    int len_4k8 = ((NUM_OF_PAD_BYTES + NUM_OF_SYNC_BYTES + 5 + (tx.cur.blocks * 30) +
                    NUM_OF_HANG_BYTES) *
                   8);

    // **** PMT FOR 4k8 MODULATOR INPUT **** //
    pmt::pmt_t out_vector = pmt::make_s8vector(len_4k8, 0);
    int8_t* out_1 = pmt::s8vector_writable_elements(out_vector, d_off);

    // **** ASSEMBLE MESSAGE 4k8 **** //
    count += fr.write_sync(&out_1[count]);
    count += fr.write_header(&out_1[count], 0x5765);
    count += fr.write_data(&out_1[count]);
    count += fr.write_hangbytes(&out_1[count]);

    //  **** PUBLISH MESSAGES **** //
    // message_port_pub(pmt::mp("out"), pmt::cons(meta, out_vector));
    message_port_pub(pmt::mp("out"), pmt::cons(meta, pmt::make_blob(&out_1[0], len_4k8)));
}

} /* namespace tnc_nx */
} /* namespace gr */
