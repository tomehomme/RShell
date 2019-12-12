#include "gtest/gtest.h"


#include "constructor_test.hpp"
#include "Command_test.hpp"
#include "And_test.hpp"
#include "Or_test.hpp"
#include "execute_test.hpp"
#include "Paren_test.hpp"
#include "test_test.hpp"
#include "Write_test.hpp"
#include "Append_test.hpp"
#include "Read_test.hpp"

int main(int argc, char** argv){

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();


}
