#ifndef THYMIO_ARGOS_SFERES_PARAMS_H
#define THYMIO_ARGOS_SFERES_PARAMS_H

#include <sferes/phen/parameters.hpp>
#include <sferes/gen/evo_float.hpp>
#include <modules/nn2/gen_dnn.hpp>
#include <sferes/fit/fitness.hpp>

using namespace sferes;
using namespace sferes::gen::evo_float;
using namespace sferes::gen::dnn;
using namespace nn;

struct ParamsDnn
{
    /* use only the proximity sensors */
    struct dnn
    {
        static constexpr size_t nb_inputs = 10; // ! 7 ir sensors + 2 ground sensor + bias input at +1
        static constexpr size_t nb_outputs = 2; // 2 motors: left and right wheel

        static constexpr int io_param_evolving = true;
        static constexpr float m_rate_add_conn = 0.15f;
        static constexpr float m_rate_del_conn = 0.15f;
        static constexpr float m_rate_change_conn = 0.15f;
        static constexpr float m_rate_add_neuron = 0.10f;
        static constexpr float m_rate_del_neuron = 0.10f;

        static constexpr init_t init = random_topology; //random_topology or ff (feed-forward)
        //these only count w/ random init, instead of feed forward
        static constexpr size_t min_nb_neurons = 0;  // does not include input and output neurons
        static constexpr size_t max_nb_neurons = 20; // does not include input and output neurons
        static constexpr size_t min_nb_conns = 0;
        static constexpr size_t max_nb_conns = 40;
    };

    struct parameters
    {
        //Min and max weights of MLP?
        static constexpr float min = -2.0f;
        static constexpr float max = 2.0f;
    };

    struct evo_float
    {
        static constexpr mutation_t mutation_type = polynomial;
        //static const cross_over_t cross_over_type = sbx;
        static constexpr cross_over_t cross_over_type = no_cross_over;
        static constexpr float cross_rate = 0.0f;
        static constexpr float mutation_rate = 0.05f;
        static constexpr float eta_m = 15.0f;
        static constexpr float eta_c = 10.0f;
    };
};

namespace robots_nn
{
typedef phen::Parameters<gen::EvoFloat<1, ParamsDnn>, fit::FitDummy<>, ParamsDnn> weight_t;
typedef phen::Parameters<gen::EvoFloat<1, ParamsDnn>, fit::FitDummy<>, ParamsDnn> bias_t;

typedef PfWSum<weight_t> pf_t;
typedef AfTanh<bias_t> af_t;
typedef Neuron<pf_t, af_t> neuron_t;
typedef Connection<weight_t> connection_t;
typedef sferes::gen::Dnn<neuron_t, connection_t, ParamsDnn> gen_t;
typedef typename gen_t::nn_t nn_t; // not sure if typename should be here?
} // namespace robots_nn

#endif //THYMIO_ARGOS_SFERES_PARAMS_H
