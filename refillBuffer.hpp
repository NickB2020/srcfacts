/*
    refillBuffer.hpp

    Declaration of refill buffer function
*/

#ifndef INCLUDE_REFILLBUFFER_HPP
#define INCLUDE_REFILLBUFFER_HPP

#include <iostream>
#include <iterator>
#include <string>

// refill buffer
std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& totalBytes);

#endif
