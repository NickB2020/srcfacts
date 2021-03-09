/*
    XMLParser.cpp
 
    Implementation file for XML parsing class
 */

#include "XMLParser.hpp"
#include "xml_parser.hpp"

// constructor
XMLParser::XMLParser() {
    
    pc = buffer.cbegin();
    
}

// is done parsing
bool XMLParser::isDone( std::string::const_iterator end) {
    
    return pc == end;
}

// is parsing at a XML declaration
bool XMLParser::isXMLDeclaration() {
  
    return ::isXMLDeclaration(pc);
}

// is parsing at a XML end tag
bool XMLParser::isXMLEndTag() {
    
    return ::isXMLEndTag(pc);
}

// is parsing at a XML start tag
bool XMLParser::isXMLStartTag() {
    
    return ::isXMLStartTag(pc);
}

// is parsing at a XML namespace
bool XMLParser::isXMLNamespace(bool intag) {
    
    return ::isXMLNamespace(intag, pc);
}

// is parsing at a XML attribute
bool XMLParser::isXMLAttribute(bool intag) {
    
    return ::isXMLAttribute(intag, pc);
}

// is parsing at a XML CDATA
bool XMLParser::isXMLCDATA() {
    
    return ::isXMLCDATA(pc);
}

// is parsing at a XML comment
bool XMLParser::isXMLComment() {
    
    return ::isXMLComment(pc);
}

// is parsing at characters before or after XML
bool XMLParser::isCharactersBeforeOrAfter(int depth) {
    
    return ::isCharactersBeforeOrAfter(depth, pc);
}

// is parsing at a XML entity characters
bool XMLParser::isXMLEntityCharacters() {
    
    return ::isXMLEntityCharacters(pc);
}

// is parsing at a XML characters
bool XMLParser::isXMLCharacters() {
    
    return ::isXMLCharacters(pc);
}

// parse declaration
void XMLParser::parseDeclaration( std::string::const_iterator endpc, long& total) {
     
    pc = ::parseDeclaration(pc, endpc, total);
}

// parse required version
void XMLParser::parseRequiredVersion( std::string::const_iterator endpc) {
    
    pc = ::parseRequiredVersion(pc, endpc);
}

// parse a XML encoding
void XMLParser::parseEncoding( std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend) {
    
   pc = ::parseEncoding(pc, endpc, pnameend, pvalueend);
}

// parse a XML standalone
void XMLParser::parseStandalone( std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend) {
    
    pc = ::parseStandalone(pc, endpc, pnameend, pvalueend);
}

// parse a XML end tag
void XMLParser::parseEndTag( std::string::const_iterator pvalueend, int depth, long& total) {
    
    pc = ::parseEndTag(pc, pvalueend, depth, total);
}

// parse a XML start tag
void XMLParser::parseStartTag(int depth, long& total, bool intag, std::string::const_iterator endpc, std::string::const_iterator pnameend,std::string::const_iterator pvalueend, const std::string local_name) {
    
    pc = ::parseStartTag(depth, total, intag, pc, endpc, pnameend, pvalueend, local_name);
}

// parse a XML namespace
void XMLParser::parseNameSpace(bool intag,  std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend) {
    
    pc = ::parseNameSpace(intag, pc, endpc, pnameend, pvalueend);
}

// parse a XML attribute
void XMLParser::parseAttribute(std::string url, bool intag,   std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend) {

   pc = ::parseAttribute(url, intag, pc, endpc, pnameend, pvalueend);
}

// parse a XML CDATA
void XMLParser::parseCDATA(  std::string::const_iterator endpc, int loc, int textsize, long& total) {
    
    pc = ::parseCDATA(pc, endpc, loc, textsize, total);
}

// parse a XML comment
void XMLParser::parseComment(  std::string::const_iterator endpc, long& total) {
    
    pc = ::parseComment(pc, endpc, total);
}

// parse a XML character before or after XML
void XMLParser::parseCharactersBeforeOrAfter(std::string::const_iterator pc) {
    
   pc = ::parseCharactersBeforeOrAfter(pc);
}

// parse a XML entity references
void XMLParser::parseEntityReference( int textsize, long& total) {
    
   pc = ::parseEntityReference(pc, textsize, total);
}

// parse a XML characters
void XMLParser::parseCharacters( int loc, int textsize) {
    
    pc = ::parseCharacters(pc, loc, textsize);
}






