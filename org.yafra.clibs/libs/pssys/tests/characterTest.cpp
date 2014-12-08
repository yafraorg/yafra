/*
 * characterTest.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: mwn
 */

#include "sysLibTest.h"

class characterTest : public CppUnit::TestCase {
public:
  displayCharacters( std::string name ) : CppUnit::TestCase( name ) {}

  void runTest() {
    CPPUNIT_ASSERT( Complex (10, 1) == Complex (10, 1) );
    CPPUNIT_ASSERT( !(Complex (1, 1) == Complex (2, 2)) );
  }
};
