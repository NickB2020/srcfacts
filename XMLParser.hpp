/*
    XMLParser.hpp
 
    Declaration file for XML parsing class
 */

#ifndef INCLUDED_XMLPARSER_HPP
#define INCLUDED_XMLPARSER_HPP

#include <string>
#include <functional>

class XMLParser {
public:
    
    // constructor
    XMLParser();
    
    // is done parsing
    bool isDone();
    
    // is parsing at a XML declaration
    bool isXMLDeclaration();
    
    // is parsing at a XML end tag
    bool isXMLEndTag();
    
    // is parsing at a XML start tag
    bool isXMLStartTag();
    
    // is parsing at a XML Namespace
    bool isXMLNamespace();
    
    // is parsing at a XML attribute
    bool isXMLAttribute();
    
    // is parsing at a XML CDATA
    bool isXMLCDATA();
    
    // is parsing at a XML comment
    bool isXMLComment();

    // is parsing at characters before or after XML
    bool isCharactersBeforeOrAfter();

    // is parsing at a XML entity characters
    bool isXMLEntityCharacters();

    // is parsing at a XML characters
    bool isXMLCharacters();

    // parse declaration
    void parseDeclaration();

    // parse required version
    void parseRequiredVersion();

    // parse a XML encoding
    void parseEncoding();

    // parse a XML standalone
    void parseStandalone();

    // parse a XML end tag
    void parseEndTag();

    // parse a XML start tag
    void parseStartTag();

    // parse a XML namespace
    void parseNameSpace();

    // parse a XML attribute
    void parseAttribute();

    // parse a XML CDATA
    void parseCDATA();

    // parse a XML comment
    void parseComment();
    
    // parse a XML character before or after XML
    void parseCharactersBeforeOrAfter();
 
    // parse a XML entity references
    void parseEntityReference();
    
    // parse a XML characters
    void parseCharacters();

private:
    std::function<void(const std::string&)>handleDeclarations;
    std::function<void(const std::string&)>handleRequiredVersion;
    std::function<void(const std::string&)>handleEncoding;
    std::function<void(const std::string&)>handleStandalones;
    std::function<void(const std::string&)>handleEndTags;
    std::function<void(const std::string&)>handleStartTags;
    std::function<void(const std::string&)>handleNameSpaces;
    std::function<void(const std::string&)>handleAttributes;
    std::function<void(const std::string&)>handleCDATA;
    std::function<void(const std::string&)>handleComments;
    std::function<void(const std::string&)>handleCharactersBeforeOrAfter;
    std::function<void(const std::string&)>handleEntityReferences;
    std::function<void(const std::string&)>handleCharacters;
    
    
    std::string::const_iterator pc;
    std::string::const_iterator endpc;
    std::string buffer;
    long total = 0;
    bool intag = false;
    int depth = 0;
    int textsize = 0;
    int loc = 0;
};

#endif
