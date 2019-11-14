#include "gtest/gtest.h"


#include "constructor_test.hpp"
#include "Command_test.hpp"
#include "And_test.hpp"
#include "Or_test.hpp"


int main(int argc, char** argv){

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();


}
