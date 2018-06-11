#include "Vector.h"
#include <shogun/base/init.h>
// #include "op.h"

using namespace shogun;

int main()
{
	init_shogun_with_defaults();
	sg_io->set_loglevel(MSG_GCDEBUG);

	Vector a(3); // creates a vector with all zero
	SGVector<float64_t> b_({1, 2, 3});
	Vector b(b_);

	a.display_vector("a");
	b.display_vector("b");
	//  auto c = plus(a, b);
	exit_shogun();
	return 0;
}
