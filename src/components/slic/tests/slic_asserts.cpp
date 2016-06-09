/*
 * Copyright (c) 2015, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and further
 * review from Lawrence Livermore National Laboratory.
 */


#include "gtest/gtest.h"

#include "slic/slic.hpp"
#include "slic/UnitTestLogger.hpp"
using asctoolkit::slic::UnitTestLogger;

/**
 * \file
 *
 * The tests in this file check that SLIC macros properly output their message and exit (when appropriate)
 * when run from constructors and destructors.
 * They also exercise the SLIC UnitTestLogger.
 */

namespace {
    /**
     * A simple struct with an assert in the constructor
     */
    struct AssertCtor
    {
        AssertCtor() { SLIC_ASSERT_MSG(false,"Testing assert in .ctor"); }
    };

    /** 
     *  A simple struct with an assert in a method (foo)
     */
    struct AssertMethod
    {
        void foo() { SLIC_ASSERT_MSG(false,"Testing assert in class method"); }
    };

    /** 
     *  A simple struct with an assert in the destructor
     */
    struct AssertDtor
    {
        ~AssertDtor() { SLIC_ASSERT_MSG(false,"Testing assert in .dtor"); }
    };
   
      
    /** 
     *  A simple testing fixture with a SLIC_WARNING in the constructor.
     *  Note: gtest ASSERT_DEATH has a return, so it cannot be used in a constructor.
     */
    class SetFixtureC : public ::testing::Test
    {
    public:
        SetFixtureC() { SLIC_WARNING("Testing warning in fixture .ctor -- this warning message should be logged"); }
    };

    /** 
     *  A simple testing fixture with an assert in the SetUp function.
     */
    class SetFixtureS : public ::testing::Test
    {
    public:
        void SetUp() {
          #ifdef ATK_DEBUG
             ASSERT_DEATH( SLIC_ASSERT_MSG(false,"Testing assert in fixture setup"), "");
          #else
             SLIC_WARNING("Testing warning in fixture setup");
          #endif
        }
    };
    
    /** 
     *  A simple testing fixture with an assert in the TearDown function.
     */
    class SetFixtureT : public ::testing::Test
    {
    public:
        void TearDown() {
          #ifdef ATK_DEBUG
            ASSERT_DEATH( SLIC_ASSERT_MSG(false,"Testing assert in fixture teardown"), "");
          #else
            SLIC_WARNING("Testing warning in fixture teardown");
          #endif
        }
    };
    
    /** 
     *  A simple testing fixture with a SLIC_WARNING in the destructor.
     *  Note: gtest ASSERT_DEATH has a return, so it cannot be used in a destructor.
     *
     */    
    class SetFixtureD : public::testing::Test
    {
    public:
        ~SetFixtureD() { SLIC_WARNING("Testing warning in fixture .dtor -- this warning message should be logged"); }
    };    
    
}

// ********  A series of tests exercising SLIC_ASSERT

TEST(gtest_slic_usage,in_test)
{
  SLIC_ASSERT_MSG(true, "Testing SLIC assert (true) in test body");
#ifdef ATK_DEBUG
  ASSERT_DEATH( SLIC_ASSERT_MSG(false, "Testing SLIC assert(false) in test body"), "" )
      << "SLIC assert (false) from a test";
#else
  ASSERT_DEATH( SLIC_ERROR_IF(true, "Testing SLIC error in test body for release mode"), "" )
      << "SLIC_ERROR_IF(false) from a test";

#endif
}

TEST(gtest_slic_usage,in_ctor)
{
#ifdef ATK_DEBUG
   ASSERT_DEATH( AssertCtor(), "" ) << " SLIC assert from class .ctor ";
#else
   AssertCtor();
#endif
}

TEST(gtest_slic_usage,in_method)
{
  AssertMethod am;
#ifdef ATK_DEBUG
  ASSERT_DEATH( am.foo(), "" ) << " SLIC assert from class method ";
#else
  am.foo();
#endif
 }

TEST(gtest_slic_usage,in_dtor)
{
#ifdef ATK_DEBUG
  ASSERT_DEATH( AssertDtor(), "" ) << " SLIC assert from class .ctor ";
#else
  AssertDtor();
#endif
}

// A test using a test fixture with an assert in the setup phase
TEST_F(SetFixtureS, in_fixture_setup){}

// A test using a test fixture with an assert in the teardown phase
TEST_F(SetFixtureT, in_fixture_teardown){}


///  Note (KW): the following two tests are warnings since ASSERT_DEATH does not work in a constructor or destructor
///  Specifically, the ASSERT_DEATH macro has a return statement which is not allowed in constructors or destructors

// A test using a test fixture with an assert in the constructor
TEST_F(SetFixtureC, in_fixture_ctor){}

// A test using a test fixture with an assert in the destructor
TEST_F(SetFixtureD, in_fixture_dtor){}



int main(int argc, char * argv[])
{
  int result = 0;

  ::testing::InitGoogleTest(&argc, argv);

  UnitTestLogger logger;  // create & initialize test logger,
                          // finalized when exiting main scope

  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  result = RUN_ALL_TESTS();

  return result;
}
