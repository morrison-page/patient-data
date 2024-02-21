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
			Database Database;
			Patient Patient("test", Hashing::hashPassword("test"), "test", "test",
				0, false, NULL,
				false, NULL,
				false, NULL,
				false, false);
			Assert::IsTrue(Database.createPatient(Patient));
		}
		
		TEST_METHOD(createDoctorAccount)
		{
			Database Database;
			User User("test", Hashing::hashPassword("test"), AccessLevel::DOCTOR);
			Assert::IsTrue(Database.createStaff(User));
		}

		TEST_METHOD(createPharmacistAccount)
		{
			Database Database;
			User User("test", Hashing::hashPassword("test"), AccessLevel::PHARMACIST);
			Assert::IsTrue(Database.createStaff(User));
		}
	};
}
