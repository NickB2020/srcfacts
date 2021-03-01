/*
    srcFacts.cpp
    Produces a report with various counts of the number of
    statements, declarations, etc. of a source code project
    in C++, C, Java, and C#.
    Input is an XML file in the srcML format.
    Code includes an almost-complete XML parser. Limitations:
    * DTD declarations are not handled
    * Well-formedness is not checked
*/

#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <cstring>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>

#if !defined(_MSC_VER)
#include <sys/uio.h>
#include <unistd.h>
#define READ read
#else
#include <BaseTsd.h>
#include <io.h>
typedef SSIZE_T ssize_t;
#define READ _read
#endif

const int BUFFER_SIZE = 16 * 16 * 4096;

// call to refill buffer
std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& totalBytes);

int main() {
    const int XMLNS_SIZE = strlen("xmlns");
    std::string url;
    int textsize = 0;
    int loc = 0;
    int expr_count = 0;
    int function_count = 0;
    int class_count = 0;
    int file_count = 0;
    int decl_count = 0;
    int comment_count = 0;
    int return_count = 0;
    int literal_string_count = 0;
    int depth = 0;
    long total = 0;
    bool intag = false;
    std::string buffer(BUFFER_SIZE, ' ');
    auto pc = buffer.cend();
    while (true) {
        if (std::distance(pc, buffer.cend()) < 5) {
            // refill buffer and adjust iterator
            pc = refillBuffer(pc, buffer, total);
            if (pc == buffer.cend())
                break;
        } else if (*pc == '<' && *std::next(pc) == '?') {
            // parse XML declaration
            std::string::const_iterator isXMLDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, std::string buffer, long total, std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& totalBytes));
            
            // parse required version
            std::string::const_iterator isRequiredVersion(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

            // parse encoding
            std::string::const_iterator isEncoding(std::string::const_iterator pc, std::string::const_iterator endpc);
            
            // parse standalone
            std::string::const_iterator isStandalone(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pvalueend, std::string::const_iterator pnameend);
            
        } else if (*pc == '<' && *std::next(pc) == '/') {
            // parse end tag
            --depth;
            std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
            if (endpc == buffer.cend()) {
                pc = refillBuffer(pc, buffer, total);
                endpc = std::find(pc, buffer.cend(), '>');
                if (endpc == buffer.cend()) {
                    std::cerr << "parser error: Incomplete element end tag\n";
                    return 1;
                }
            }
            std::advance(pc, 2);
            std::string::const_iterator pnameend = std::find_if(pc, std::next(endpc), [] (char c) { return isspace(c) || c == '>' || c == '/'; });
            if (pnameend == std::next(endpc)) {
                  std::cerr << "parser error: Incomplete element end tag name\n";
                  return 1;
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

        } else if (*pc == '<' && *std::next(pc) != '/' && *std::next(pc) != '?') {
            // parse start tag
            std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
            if (endpc == buffer.cend()) {
                pc = refillBuffer(pc, buffer, total);
                endpc = std::find(pc, buffer.cend(), '>');
                if (endpc == buffer.cend()) {
                    std::cerr << "parser error: Incomplete element start tag\n";
                    return 1;
                }
            }
            std::advance(pc, 1);
            std::string::const_iterator pnameend = std::find_if(pc, std::next(endpc), [] (char c) { return isspace(c) || c == '>' || c == '/'; });
            if (pnameend == std::next(endpc)) {
                std::cerr << "parser error : Unterminated start tag '" << std::string(pc, pnameend) << "'\n";
                return 1;
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
            if (local_name == "expr")
                ++expr_count;
            else if (local_name == "function")
                ++function_count;
            else if (local_name == "decl")
                ++decl_count;
            else if (local_name == "class")
                ++class_count;
            else if (local_name == "unit" && depth > 0)
                ++file_count;
            else if (local_name == "comment")
                ++comment_count;
            else if (local_name == "return")
                ++return_count;
            else if (local_name == "literal")
                ++literal_string_count;
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
        } else if (intag && *pc != '>' && *pc != '/' && std::distance(pc, buffer.cend()) > (int) XMLNS_SIZE && std::string(pc, std::next(pc, XMLNS_SIZE)) == "xmlns"
            && (*std::next(pc, XMLNS_SIZE) == ':' || *std::next(pc, XMLNS_SIZE) == '=')) {
            // parse namespace
            std::advance(pc, XMLNS_SIZE);
            const std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
            std::string::const_iterator pnameend = std::find(pc, std::next(endpc), '=');
            if (pnameend == std::next(endpc)) {
                std::cerr << "parser error : incomplete namespace\n";
                return 1;
            }
            pc = pnameend;
            std::string prefix;
            if (*pc == ':') {
                std::advance(pc, 1);
                prefix.assign(pc, pnameend);
            }
            pc = std::next(pnameend);
            pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
            if (pc == std::next(endpc)) {
                std::cerr << "parser error : incomplete namespace\n";
                return 1;
            }
            const char delim = *pc;
            if (delim != '"' && delim != '\'') {
                std::cerr << "parser error : incomplete namespace\n";
                return 1;
            }
            std::advance(pc, 1);
            std::string::const_iterator pvalueend = std::find(pc, std::next(endpc), delim);
            if (pvalueend == std::next(endpc)) {
                std::cerr << "parser error : incomplete namespace\n";
                return 1;
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
        } else if (intag && *pc != '>' && *pc != '/') {
            // parse attribute
            const std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
            std::string::const_iterator pnameend = std::find(pc, std::next(endpc), '=');
            if (pnameend == std::next(endpc))
                return 1;
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
            std::string local_name = std::move(local_namebase);
            pc = std::next(pnameend);
            pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
            if (pc == buffer.cend()) {
                std::cerr << "parser error : attribute " << qname << " incomplete attribute\n";
                return 1;
            }
            char delim = *pc;
            if (delim != '"' && delim != '\'') {
                std::cerr << "parser error : attribute " << qname << " missing delimiter\n";
                return 1;
            }
            std::advance(pc, 1);
            std::string::const_iterator pvalueend = std::find(pc, std::next(endpc), delim);
            if (pvalueend == std::next(endpc)) {
                std::cerr << "parser error : attribute " << qname << " missing delimiter\n";
                return 1;
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
        } else if (*pc == '<' && *std::next(pc) == '!' && *std::next(pc, 2) == '[') {
            // parse CDATA
            const std::string endcdata = "]]>";
            std::advance(pc, strlen("<![CDATA["));
            std::string::const_iterator endpc = std::search(pc, buffer.cend(), endcdata.begin(), endcdata.end());
            if (endpc == buffer.cend()) {
                pc = refillBuffer(pc, buffer, total);
                endpc = std::search(pc, buffer.cend(), endcdata.begin(), endcdata.end());
                if (endpc == buffer.cend())
                    return 1;
            }
            const std::string characters(pc, endpc);
            textsize += (int) characters.size();
            loc += (int) std::count(characters.begin(), characters.end(), '\n');
            pc = std::next(endpc, strlen("]]>"));
        } else if (*pc == '<' && *std::next(pc) == '!' && *std::next(pc, 2) == '-' && *std::next(pc, 3) == '-') {
            // parse XML comment
            const std::string endcomment = "-->";
            std::string::const_iterator endpc = std::search(pc, buffer.cend(), endcomment.begin(), endcomment.end());
            if (endpc == buffer.cend()) {
                pc = refillBuffer(pc, buffer, total);
                endpc = std::search(pc, buffer.cend(), endcomment.begin(), endcomment.end());
                if (endpc == buffer.cend()) {
                    std::cerr << "parser error : Unterminated XML comment\n";
                    return 1;
                }
            }
            pc = std::next(endpc, strlen("-->"));
            pc = std::find_if_not(pc, buffer.cend(), [] (char c) { return isspace(c); });
        } else if (*pc != '<' && depth == 0) {
            // parse characters before or after XML
            pc = std::find_if_not(pc, buffer.cend(), [] (char c) { return isspace(c); });
            if (pc == buffer.cend() || !isspace(*pc)) {
                std::cerr << "parser error : Start tag expected, '<' not found\n";
                return 1;
            }
        } else if (*pc == '&') {
            // parse entity references
            std::string characters;
            if (std::distance(pc, buffer.cend()) < 3) {
                pc = refillBuffer(pc, buffer, total);
                if (std::distance(pc, buffer.cend()) < 3) {
                    std::cerr << "parser error : Incomplete entity reference, '" << std::string(pc, buffer.cend()) << "'\n";
                    return 1;
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
                        return 1;
                    }
                }
                if (*std::next(pc, 4) != ';') {
                    const std::string partialEntity(pc, std::next(pc, 4));
                    std::cerr << "parser error : Incomplete entity reference, '" << partialEntity << "'\n";
                    return 1;
                }
                characters += '&';
                std::advance(pc, strlen("&amp;"));
            } else {
                characters += '&';
                std::advance(pc, 1);
            }
            textsize += (int) characters.size();
        } else if (*pc != '<') {
            // parse characters
            const std::string::const_iterator endpc = std::find_if(pc, buffer.cend(), [] (char c) { return c == '<' || c == '&'; });
            const std::string characters(pc, endpc);
            loc += (int) std::count(characters.cbegin(), characters.cend(), '\n');
            textsize += (int) characters.size();
            pc = endpc;
        }
    }
    std::cout << "# srcFacts: " << url << '\n';
    std::cout << "| Item | Count |\n";
    std::cout << "|:-----|-----:|\n";
    std::cout << "| srcML | " << total << " |\n";
    std::cout << "| files | " << file_count << " |\n";
    std::cout << "| LOC | " << loc << " |\n";
    std::cout << "| characters | " << textsize << " |\n";
    std::cout << "| classes | " << class_count << " |\n";
    std::cout << "| functions | " << function_count << " |\n";
    std::cout << "| declarations | " << decl_count << " |\n";
    std::cout << "| expressions | " << expr_count << " |\n";
    std::cout << "| comments | " << comment_count << " |\n";
    std::cout << "| returns | " << return_count << " |\n";
    std::cout << "| literal strings | " << literal_string_count << " |\n";

    return 0;
}
