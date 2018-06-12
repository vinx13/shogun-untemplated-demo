#include "Vector.h"
#include "exp.h"
#include "op.h"
#include <shogun/base/init.h>

using namespace shogun;

int main()
{
	init_shogun_with_defaults();

	Vector a(3);
	SGVector<float64_t> b_({4, 5, 6});
	Vector b(b_);
	Vector c(SGVector<float64_t>{1000, 1001, 1002});

	a.display_vector("a");
	b.display_vector("b");
	c.display_vector("c");

	// BinaryVectorExp<VectorAdd, VectorRefExp, VectorRefExp>
	// auto ab = add(a,b);
	auto ab = add(VectorRefExp(a), VectorRefExp(b));

	// BinaryVectorExp<VectorAdd, BinaryVectorExp<VectorAdd, VectorRefExp,
	// VectorRefExp>, VectorRefExp>
	Vector abc = add(ab, VectorRefExp(c));
	abc.display_vector("a+b+c");

	exit_shogun();
	return 0;
}
