/*
    xml_parser.cpp
 
    Implementation file for XML parsing functions
 */

#include "xml_parser.hpp"
#include "refillBuffer.hpp"
#include <iostream>
#include <iterator>
#include <cstring>
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

// Parse a XML declaration
std::string::const_iterator parseDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, long& total){

    //check for incomplete XML declaration
    //endpc = std::find(pc, buffer.cend(), '>');
    if (endpc == buffer.cend()) {
        //refill the buffer
        pc = refillBuffer(pc, buffer, total);
        endpc = std::find(pc, buffer.cend(), '>');
        if (endpc == buffer.cend()) {
            std::cerr << "parser error: Incomplete XML declaration\n";
            exit(1);
        }
    }
    std::advance(pc, strlen("<?xml"));
    pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });
    
    return pc;
}
// Parse a XML required version
std::string::const_iterator parseRequiredVersion(std::string::const_iterator pc, std::string::const_iterator endpc){

        if (pc == endpc) {
            std::cerr << "parser error: Missing space after before version in XML declaration\n";
            exit(1);
            }
        std::string::const_iterator pnameend = std::find(pc, endpc, '=');
        const std::string attr(pc, pnameend);
        pc = pnameend;
        std::advance(pc, 1);
        char delim = *pc;
        if (delim != '"' && delim != '\'') {
            std::cerr << "parser error: Invalid start delimiter for version in XML declaration\n";
            exit(1);
            }
            std::advance(pc, 1);
        std::string::const_iterator pvalueend = std::find(pc, endpc, delim);
        if (pvalueend == endpc) {
            std::cerr << "parser error: Invalid end delimiter for version in XML declaration\n";
            exit(1);
            }
        if (attr != "version") {
            std::cerr << "parser error: Missing required first attribute version in XML declaration\n";
            exit(1);
            }
        const std::string version(pc, pvalueend);
        pc = std::next(pvalueend);
        pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });

        return pc;
    }
