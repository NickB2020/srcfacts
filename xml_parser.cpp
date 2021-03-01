/*
    xml_parser.cpp
 
    Implementation file for XML parsing functions
 */

#include "xml_parser.hpp"
#include <iostream>
#include <iterator>
#include <string>

const int XMLNS_SIZE = strlen("xmlns");
const int BUFFER_SIZE = 16 * 16 * 4096;
std::string buffer(BUFFER_SIZE, ' ');

// XML parsing is at a XML declaration
bool isXMLDeclaration(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '?';
}

// XML parsing is at a XML end tag
bool isXMLEndTag(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '/';
}

// XML parsing is at a XML start tag
bool isXMLStartTag(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) != '/' && *std::next(pc) != '?';
}

// XML parsing is at a XML attribute
bool isXMLAttribute(bool intag, std::string::const_iterator pc){
    
    return intag && *pc != '>' && *pc != '/';
}

// XML parsing is at a XML CDATA
bool isXMLCDATA(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '!' && *std::next(pc, 2) == '[';
}

// XML parsing is at a XML comment
bool isXMLComment(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '!' && *std::next(pc, 2) == '-' && *std::next(pc, 3) == '-';
}

// XML parsing is at characters before or after XML
bool isCharactersBeforeOrAfter(int depth, std::string::const_iterator pc){
    
    return *pc != '<' && depth == 0;
}

// XML parsing is at entity characters
bool isXMLEntityCharacters(std::string::const_iterator pc){
    
    return *pc == '&';
}

// XML parsing is at characters
bool isXMLCharacters(std::string::const_iterator pc){
    
    return *pc != '<';
}

// XML parsing is at namespaces
bool isXMLNamespace(bool intag, std::string::const_iterator pc){
    
    std::advance(pc, XMLNS_SIZE);
    
    return intag && *pc != '>' && *pc != '/' && std::distance(pc, buffer.cend()) > (int) XMLNS_SIZE && std::string(pc, std::next(pc, XMLNS_SIZE)) == "xmlns"
    && (*std::next(pc, XMLNS_SIZE) == ':' || *std::next(pc, XMLNS_SIZE) == '=');
}
