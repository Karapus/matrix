#include <gtest/gtest.h>
#include "matrix.hpp"

namespace {
TEST(Matrix, DefaultCtor) {
	Matrix<int, 2, 2> ma{};
}
TEST(Matrix, InitListCtor) {
	Matrix<int, 2, 2> ma{{{1, 0}, {0, 1}}};
}
TEST(Matrix, Access) {
	Matrix<int, 2, 2> ma{{{1, 0}, {0, 1}}};
	EXPECT_EQ(ma[0][0], ma[1][1]);
	EXPECT_EQ(ma[1][0], ma[0][1]);
	ma[1][0] = 1;
	EXPECT_EQ(ma[1][0], ma[1][1]);
}
TEST(Matrix, CopyCtor) {
	Matrix<int, 2, 2> ma{{{1, 0}, {0, 1}}};
	Matrix<int, 2, 2> mb{ma};
	EXPECT_EQ(ma[0][0], mb[0][0]);
	EXPECT_NE(&ma[0][0], &mb[0][0]);
}
}
