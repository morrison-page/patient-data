// Test Includes
#include "pch.h"
#include "CppUnitTest.h"

// Project Includes
#include "accessLevel.hpp"
#include "database.hpp"
#include "hashing.hpp"
#include "patient.hpp"
#include "user.hpp"
#include "utils.hpp"
#include "database.cpp"
#include "hashing.cpp"
#include "main.cpp"
#include "patient.cpp"
#include "user.cpp"
#include "utils.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(tests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}
		
		TEST_METHOD(createPatientAccount)
		{
			// TODO: Create Patient Account

			Assert::IsTrue(true);
		}

		TEST_METHOD(deletePatientAccount)
		{
			// TODO: Delete Patient Account
			Assert::IsTrue(true);
		}

		TEST_METHOD(createStaffAccount)
		{
			// TODO: Create Staff Account
			Assert::IsTrue(true);
		}

		TEST_METHOD(deleteStaffAccount)
		{
			// TODO: Delete Staff Account
			Assert::IsTrue(true);
		}
	};
}
