/*
 * characterTest.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: mwn
 */

#include "sysLibTest.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char* argv[])
{
  CPPUNIT_NS::TextUi::TestRunner runner;   //the runner
  // Get the top level suite from the registry
  CPPUNIT_NS::Test* suite =
      CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
  // Adds the test to the list of test to run
  runner.addTest(suite);
  // Run the test.
  bool wasSucessful = runner.run();
  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}
