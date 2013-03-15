/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include "test2_impl.h"
#include <stdio.h>

namespace gr {
  namespace dvbt {

    test2::sptr
    test2::make(int itemsize, int ninput, int noutput)
    {
      return gnuradio::get_initial_sptr (new test2_impl(itemsize, ninput, noutput));
    }

    /*
     * The private constructor
     */
    test2_impl::test2_impl(int itemsize, int ninput, int noutput)
      : gr_sync_interpolator("test2",
		      gr_make_io_signature(1, 1, itemsize * ninput),
		      gr_make_io_signature(1, 1, itemsize),
          ninput)
    {}

    /*
     * Our virtual destructor.
     */
    test2_impl::~test2_impl()
    {
    }

    int
    test2_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

        int obsize = output_signature()->sizeof_stream_item (0);

        memcpy(out, in, noutput_items * obsize); 

        printf("noutput_items: %i\n", noutput_items);

        // Do <+signal processing+>

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace dvbt */
} /* namespace gr */
