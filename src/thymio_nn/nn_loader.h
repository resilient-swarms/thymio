//
// Created by matthew on 02/08/19.
//

#ifndef THYMIO_NN_LOADER_H
#define THYMIO_NN_LOADER_H

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include "params.h"

using namespace boost::archive;
using namespace robots_nn;

namespace nn_loader {

    const char savefile[] = "BOOST_SERIALIZATION_NVP";

    /// load data (neural network) from binary archive file
    nn_t Load() {

        gen_t loaded_ind;

        std::ifstream ifs(savefile);
        text_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(loaded_ind);

        // develop the parameters
        BGL_FORALL_VERTICES_T(v, loaded_ind.get_graph(),
                              typename nn_t::graph_t)
            {
                loaded_ind.get_graph()[v].get_afparams().develop();
                loaded_ind.get_graph()[v].get_pfparams().develop();
                loaded_ind.get_graph()[v].set_afparams(loaded_ind.get_graph()[v].get_afparams());
                loaded_ind.get_graph()[v].set_pfparams(loaded_ind.get_graph()[v].get_pfparams());
            }
        BGL_FORALL_EDGES_T(e, loaded_ind.get_graph(),
                           typename nn_t::graph_t)
            {
                loaded_ind.get_graph()[e].get_weight().develop();
            }
        // init everything
        loaded_ind.init();

        /*{
            std::ofstream aofs("nn_after.dot");
            loaded_ind.write(aofs);
        }*/
        return loaded_ind;
    }
}
#endif //THYMIO_NN_LOADER_H
