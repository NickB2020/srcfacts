/*
    XMLParser.cpp
 
    Implementation file for XML parsing class
 */

#include "XMLParser.hpp"
#include "refillBuffer.hpp"

#include <iostream>
#include <iterator>
#include <sstream>

const int XMLNS_SIZE = strlen("xmlns");

// constructor
XMLParser::XMLParser(std::function<void(const std::string&)>handleDeclarations,
                     std::function<void(const std::string&)>handleRequiredVersion,
                     std::function<void(const std::string&)>handleEncoding,
                     std::function<void(const std::string&)>handleStandalones,
                     std::function<void(const std::string&)>handleEndTags,
                     std::function<void(const std::string&)>handleStartTags,
                     std::function<void(const std::string&)>handleNameSpaces,
                     std::function<void(const std::string&)>handleAttributes,
                     std::function<void(const std::string&)>handleCDATA,
                     std::function<void(const std::string&)>handleComments,
                     std::function<void(const std::string&)>handleCharactersBeforeOrAfter,
                     std::function<void(const std::string&)>handleEntityReferences,
                     std::function<void(const std::string&)>handleCharacters)
   : handleDeclarations(handleDeclarations), handleRequiredVersion(handleRequiredVersion),
     handleEncoding(handleEncoding), handleStandalones(handleStandalones),
     handleEndTags(handleEndTags), handleStartTags(handleStartTags), handleNameSpaces(handleNameSpaces),
     handleAttributes(handleAttributes), handleCDATA(handleCDATA), handleComments(handleComments),
     handleCharactersBeforeOrAfter(handleCharactersBeforeOrAfter), handleEntityReferences(handleEntityReferences),
     handleCharacters(handleCharacters)
{
    pc = buffer.cbegin();
    //pc = refillBuffer(pc, buffer, total);
}

// is done parsing
bool XMLParser::isDone() {
    
    return pc == buffer.cend();
}

// is parsing at a XML declaration
bool XMLParser::isXMLDeclaration() {
  
    return *pc == '<' && *std::next(pc) == '?';

}

// is parsing at a XML end tag
bool XMLParser::isXMLEndTag() {
    
    return *pc == '<' && *std::next(pc) == '/';
}

// is parsing at a XML start tag
bool XMLParser::isXMLStartTag() {
    
    return *pc == '<' && *std::next(pc) != '/' && *std::next(pc) != '?';

}

// is parsing at a XML namespace
bool XMLParser::isXMLNamespace() {
    
    return intag && *pc != '>' && *pc != '/' && std::distance(pc, buffer.cend()) > (int) XMLNS_SIZE && std::string(pc, std::next(pc, XMLNS_SIZE)) == "xmlns"
    && (*std::next(pc, XMLNS_SIZE) == ':' || *std::next(pc, XMLNS_SIZE) == '=');
}

// is parsing at a XML attribute
bool XMLParser::isXMLAttribute() {
    
    return intag && *pc != '>' && *pc != '/';
}

// is parsing at a XML CDATA
bool XMLParser::isXMLCDATA() {
    
    return *pc == '<' && *std::next(pc) == '!' && *std::next(pc, 2) == '[';
}

// is parsing at a XML comment
bool XMLParser::isXMLComment() {
    
    return *pc == '<' && *std::next(pc) == '!' && *std::next(pc, 2) == '-' && *std::next(pc, 3) == '-';
}

// is parsing at characters before or after XML
bool XMLParser::isCharactersBeforeOrAfter() {
    
    return *pc != '<' && depth == 0;
}

// is parsing at a XML entity characters
bool XMLParser::isXMLEntityCharacters() {
    
    return *pc == '&';
}

// is parsing at a XML characters
bool XMLParser::isXMLCharacters() {
    
    return *pc != '<';
}

// parse declaration
void XMLParser::parseDeclaration() {
     
    if(handleDeclarations != nullptr){
        handleDeclarations(local_name);
    }
    //check for incomplete XML declaration
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
}

// parse required version
void XMLParser::parseRequiredVersion() {
    
    if(handleRequiredVersion != nullptr){
        handleRequiredVersion(local_name);
    }
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

}

// parse a XML encoding
void XMLParser::parseEncoding() {
    
    if(handleEncoding != nullptr){
        handleEncoding(local_name);
    }
    if (pc == endpc) {
        std::cerr << "parser error: Missing required encoding in XML declaration\n";
        exit(1);
    }
    std::string::const_iterator pnameend = std::find(pc, endpc, '=');
    if (pnameend == endpc) {
        std::cerr << "parser error: Incomple encoding in XML declaration\n";
        exit(1);
    }
    const std::string attr2(pc, pnameend);
    pc = pnameend;
    std::advance(pc, 1);
    char delim2 = *pc;
    if (delim2 != '"' && delim2 != '\'') {
        std::cerr << "parser error: Invalid end delimiter for encoding in XML declaration\n";
        exit(1);
    }
    std::advance(pc, 1);
    std::string::const_iterator pvalueend = std::find(pc, endpc, delim2);
    if (pvalueend == endpc) {
        std::cerr << "parser error: Incomple encoding in XML declaration\n";
        exit(1);
    }
    if (attr2 != "encoding") {
         std::cerr << "parser error: Missing required encoding in XML declaration\n";
        exit(1);
    }
    const std::string encoding(pc, pvalueend);
    pc = std::next(pvalueend);
    pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });
}

// parse a XML standalone
void XMLParser::parseStandalone() {
    
    if(handleStandalones != nullptr){
        handleStandalones(local_name);
    }
    if (pc == endpc) {
        std::cerr << "parser error: Missing required third attribute standalone in XML declaration\n";
        exit(1);
    }
    std::string::const_iterator pnameend = std::find(pc, endpc, '=');
    const std::string attr3(pc, pnameend);
    pc = pnameend;
    std::advance(pc, 1);
    char delim3 = *pc;
    if (delim3 != '"' && delim3 != '\'') {
        std::cerr << "parser error : Missing attribute standalone delimiter in XML declaration\n";
        exit(1);
    }
    std::advance(pc, 1);
    std::string::const_iterator pvalueend = std::find(pc, endpc, delim3);
    if (pvalueend == endpc) {
        std::cerr << "parser error : Missing attribute standalone in XML declaration\n";
        exit(1);
    }
    if (attr3 != "standalone") {
        std::cerr << "parser error : Missing attribute standalone in XML declaration\n";
        exit(1);
    }
    const std::string standalone(pc, pvalueend);
    pc = std::next(pvalueend);
    pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });
    std::advance(pc, strlen("?>"));
    pc = std::find_if_not(pc, buffer.cend(), [] (char c) { return isspace(c); });
}

// parse a XML end tag
void XMLParser::parseEndTag() {
    
    if(handleEndTags != nullptr){
        handleEndTags(local_name);
    }
    --depth;
    std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
    if (endpc == buffer.cend()) {
        pc = refillBuffer(pc, buffer, total);
        endpc = std::find(pc, buffer.cend(), '>');
        if (endpc == buffer.cend()) {
            std::cerr << "parser error: Incomplete element end tag\n";
            exit(1);
        }
    }
    std::advance(pc, 2);
    std::string::const_iterator pnameend = std::find_if(pc, std::next(endpc), [] (char c) { return isspace(c) || c == '>' || c == '/'; });
    if (pnameend == std::next(endpc)) {
          std::cerr << "parser error: Incomplete element end tag name\n";
          exit(1);
    }
    const std::string qname(pc, pnameend);
    const auto colonpos = qname.find(':');
    std::string prefixbase;
    if (colonpos != std::string::npos)
        prefixbase = qname.substr(0, colonpos);
    const std::string prefix = std::move(prefixbase);
    std::string local_namebase;
    if (colonpos != std::string::npos)
        local_namebase = qname.substr(colonpos + 1);
    else
        local_namebase = qname;
    const std::string local_name = std::move(local_namebase);
    pc = std::next(endpc);
}

// parse a XML start tag
void XMLParser::parseStartTag() {
    
    if(handleStartTags != nullptr){
        handleStartTags(local_name);
    }
    endpc = std::find(pc, buffer.cend(), '>');
    if (endpc == buffer.cend()) {
        pc = refillBuffer(pc, buffer, total);
        endpc = std::find(pc, buffer.cend(), '>');
        if (endpc == buffer.cend()) {
            std::cerr << "parser error: Incomplete element start tag\n";
            exit(1);
        }
    }
    std::advance(pc, 1);
    std::string::const_iterator pnameend = std::find_if(pc, std::next(endpc), [] (char c) { return isspace(c) || c == '>' || c == '/'; });
    if (pnameend == std::next(endpc)) {
        std::cerr << "parser error : Unterminated start tag '" << std::string(pc, pnameend) << "'\n";
        exit(1);
    }
    const std::string qname(pc, pnameend);
    const auto colonpos = qname.find(':');
    std::string prefixbase;
    if (colonpos != std::string::npos)
        prefixbase = qname.substr(0, colonpos);
    const std::string prefix = std::move(prefixbase);
    std::string local_namebase;
    if (colonpos != std::string::npos)
        local_namebase = qname.substr(colonpos + 1);
    else
        local_namebase = qname;
    const std::string local_name = std::move(local_namebase);
    pc = pnameend;
    pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
    ++depth;
    intag = true;
    if (intag && *pc == '>') {
        std::advance(pc, 1);
        intag = false;
    }
    if (intag && *pc == '/' && *std::next(pc) == '>') {
        std::advance(pc, 2);
        intag = false;
        --depth;
    }
}

// parse a XML namespace
void XMLParser::parseNameSpace() {
    
    if(handleNameSpaces != nullptr){
        handleNameSpaces(local_name);
    }
    std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
    std::string::const_iterator pnameend = std::find(pc, std::next(endpc), '=');
    if (pnameend == std::next(endpc)) {
        std::cerr << "parser error : incomplete namespace\n";
        exit(1);
        }
   // pc = pnameend;
    std::string prefix;
    if (*pc == ':') {
        std::advance(pc, 1);
        prefix.assign(pc, pnameend);
        }
    pc = std::next(pnameend);
    pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
    if (pc == std::next(endpc)) {
        std::cerr << "parser error : incomplete namespace\n";
        exit(1);
        }
    const char delim = *pc;
    if (delim != '"' && delim != '\'') {
        std::cerr << "parser error : incomplete namespace\n";
        exit(1);
        }
    std::advance(pc, 1);
    std::string::const_iterator pvalueend = std::find(pc, std::next(endpc), delim);
    if (pvalueend == std::next(endpc)) {
        std::cerr << "parser error : incomplete namespace\n";
        exit(1);
        }
    const std::string uri(pc, pvalueend);
    pc = std::next(pvalueend);
    pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
    if (intag && *pc == '>') {
        std::advance(pc, 1);
        intag = false;
        }
    if (intag && *pc == '/' && *std::next(pc) == '>') {
        std::advance(pc, 2);
        intag = false;
        }
}

// parse a XML attribute
void XMLParser::parseAttribute() {

    if(handleAttributes != nullptr){
        handleAttributes(local_name);
    }
    //std::string url;
    endpc = std::find(pc, buffer.cend(), '>');
    std::string::const_iterator pnameend = std::find(pc, std::next(endpc), '=');
    if (pnameend == std::next(endpc))
        exit(1);
    const std::string qname(pc, pnameend);
    const auto colonpos = qname.find(':');
    std::string prefixbase;
    if (colonpos != std::string::npos)
        prefixbase = qname.substr(0, colonpos);
    const std::string prefix = std::move(prefixbase);
    std::string local_namebase;
    if (colonpos != std::string::npos)
        local_namebase = qname.substr(colonpos + 1);
    else
    local_namebase = qname;
    const std::string local_name = std::move(local_namebase);
    pc = std::next(pnameend);
    pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
    if (pc == buffer.cend()) {
        std::cerr << "parser error : attribute " << qname << " incomplete attribute\n";
        exit(1);
    }
    char delim = *pc;
    if (delim != '"' && delim != '\'') {
        std::cerr << "parser error : attribute " << qname << " missing delimiter\n";
        exit(1);
    }
    std::advance(pc, 1);
    std::string::const_iterator pvalueend = std::find(pc, std::next(endpc), delim);
    if (pvalueend == std::next(endpc)) {
        std::cerr << "parser error : attribute " << qname << " missing delimiter\n";
        exit(1);
    }
    const std::string value(pc, pvalueend);
    if (local_name == "url")
        url = value;
    pc = std::next(pvalueend);
    pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
    if (intag && *pc == '>') {
        std::advance(pc, 1);
        intag = false;
    }
    if (intag && *pc == '/' && *std::next(pc) == '>') {
        std::advance(pc, 2);
        intag = false;
    }
}

// parse a XML CDATA
void XMLParser::parseCDATA() {
    
    if(handleCDATA != nullptr){
        handleCDATA(local_name);
    }
    const std::string endcdata = "]]>";
    std::advance(pc, strlen("<![CDATA["));
    endpc = std::search(pc, buffer.cend(), endcdata.begin(), endcdata.end());
    if (endpc == buffer.cend()) {
        pc = refillBuffer(pc, buffer, total);
        endpc = std::search(pc, buffer.cend(), endcdata.begin(), endcdata.end());
        if (endpc == buffer.cend())
           exit(1);
    }
    const std::string characters(pc, endpc);
    textsize += (int) characters.size();
    loc += (int) std::count(characters.begin(), characters.end(), '\n');
    pc = std::next(endpc, strlen("]]>"));
}

// parse a XML comment
void XMLParser::parseComment() {
    
    if(handleComments != nullptr){
        handleComments(local_name);
    }
    const std::string endcomment = "-->";
    endpc = std::search(pc, buffer.cend(), endcomment.begin(), endcomment.end());
    if (endpc == buffer.cend()) {
        pc = refillBuffer(pc, buffer, total);
        endpc = std::search(pc, buffer.cend(), endcomment.begin(), endcomment.end());
        if (endpc == buffer.cend()) {
            std::cerr << "parser error : Unterminated XML comment\n";
            exit(1);
        }
    }
    pc = std::next(endpc, strlen("-->"));
    pc = std::find_if_not(pc, buffer.cend(), [] (char c) { return isspace(c); });
}

// parse a XML character before or after XML
void XMLParser::parseCharactersBeforeOrAfter() {
    
    if(handleCharactersBeforeOrAfter != nullptr){
        handleCharactersBeforeOrAfter(local_name);
    }
    pc = std::find_if_not(pc, buffer.cend(), [] (char c) { return isspace(c); });
    if (pc == buffer.cend() || !isspace(*pc)) {
        std::cerr << "parser error : Start tag expected, '<' not found\n";
        exit(1);
    }
}

// parse a XML entity references
void XMLParser::parseEntityReference() {
    
    if(handleEntityReferences != nullptr){
        handleEntityReferences(local_name);
    }
    std::string characters;
    if (std::distance(pc, buffer.cend()) < 3) {
        pc = refillBuffer(pc, buffer, total);
        if (std::distance(pc, buffer.cend()) < 3) {
            std::cerr << "parser error : Incomplete entity reference, '" << std::string(pc, buffer.cend()) << "'\n";
            exit(1);
        }
    }
    if (*std::next(pc) == 'l' && *std::next(pc, 2) == 't' && *std::next(pc, 3) == ';') {
        characters += '<';
        std::advance(pc, strlen("&lt;"));
    } else if (*std::next(pc) == 'g' && *std::next(pc, 2) == 't' && *std::next(pc, 3) == ';') {
        characters += '>';
        std::advance(pc, strlen("&gt;"));
    } else if (*std::next(pc) == 'a' && *std::next(pc, 2) == 'm' && *std::next(pc, 3) == 'p') {
        if (std::distance(pc, buffer.cend()) < 4) {
            pc = refillBuffer(pc, buffer, total);
            if (std::distance(pc, buffer.cend()) < 4) {
                std::cerr << "parser error : Incomplete entity reference, '" << std::string(pc, buffer.cend()) << "'\n";
                exit(1);
            }
        }
        if (*std::next(pc, 4) != ';') {
            const std::string partialEntity(pc, std::next(pc, 4));
            std::cerr << "parser error : Incomplete entity reference, '" << partialEntity << "'\n";
            exit(1);
        }
        characters += '&';
        std::advance(pc, strlen("&amp;"));
    } else {
        characters += '&';
        std::advance(pc, 1);
    }
    textsize += (int) characters.size();
}

// parse a XML characters
void XMLParser::parseCharacters() {
    
    if(handleCharacters != nullptr){
        handleCharacters(local_name);
    }
    std::string::const_iterator endpc = std::find_if(pc, buffer.cend(), [] (char c) { return c == '<' || c == '&'; });
    const std::string characters(pc, endpc);
    loc += (int) std::count(characters.cbegin(), characters.cend(), '\n');
    textsize += (int) characters.size();
    pc = endpc;
}
