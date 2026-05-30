#include "type_set.hpp"
#include <concepts>

using S = type_set<int, double>;

static_assert(S::size == 2);
static_assert(S::contains<int>);
static_assert(!S::contains<char>);

using S2 = S::insert<char>;

static_assert(S2::size == 3);
static_assert(S2::contains<char>);

using S3 = S2::remove<double>;

static_assert(S3::size == 2);
static_assert(!S3::contains<double>);

int main() {}