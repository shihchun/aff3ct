#ifndef DECODER_POLAR_SCF_NAIVE_
#define DECODER_POLAR_SCF_NAIVE_

#include <vector>

#include "Tools/Algo/Tree/Binary_tree.hpp"
#include "Tools/Code/Polar/decoder_polar_functions.h"

#include "../SC/Decoder_polar_SC_naive.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int, typename R = float, tools::proto_f<  R> F = tools::f_LLR,
                                                tools::proto_g<B,R> G = tools::g_LLR,
                                                tools::proto_h<B,R> H = tools::h_LLR>
class Decoder_polar_SCF_naive : public Decoder_polar_SC_naive<B,R,F,G,H>
{
public:
	Decoder_polar_SCF_naive(const int& K, const int& N, const std::vector<bool>& frozen_bits,
	                           const int n_frames = 1);
	virtual ~Decoder_polar_SCF_naive() = default;
};
}
}

#include "Decoder_polar_SCF_naive.hxx"

#endif /* DECODER_POLAR_SCF_NAIVE_ */
