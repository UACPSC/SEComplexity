/*
    srcMLXPathCount.cpp

    Implementation file for srcMLXPathCount()
*/

#include "srcMLXPathCount.hpp"

#include "memory"

#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

// std::unique_ptr deleter functions for libxml2
// usage: std::unique<xmlDoc> p(xmlReadMemory);
// Call p.get() for original pointer
// Will deallocate automatically at end of std::unique_ptr lifetime
namespace std {
    template<>
    struct default_delete<xmlDoc> {
        void operator()(xmlDoc* doc) { xmlFreeDoc(doc); }
    };

    template<>
    struct default_delete<xmlXPathObject> {
        void operator()(xmlXPathObject* xpath) { xmlXPathFreeObject(xpath); }
    };

    template<>
    struct default_delete<xmlXPathContext> {
        void operator()(xmlXPathContext* context) { xmlXPathFreeContext(context); }
    };
}

/** Count of the result of applying the xpath to the srcML file
 * 
 * XPath expression must result in a numeric, integer result.
 * In general, this means it needs to use the XPath count() function
 *
 * @param srcMLfile filename of srcML file
 * @param xpath XPath expression as string
 * @retval Number of conditions in the srcMLfile
 * @retval -1 Error in apply XPath
 * @retval -2 Invalid argument
 */
int srcMLXPathCount(const char* srcMLfile, const char* xpath) {

    // precondition on parameters
    if (srcMLfile == nullptr || xpath == nullptr)
        return -2;

    xmlInitParser();

    // open the srcML file with no encoding change and no options
    std::unique_ptr<xmlDoc> srcMLdoc(xmlReadFile(srcMLfile, nullptr, 0));
    if (!srcMLdoc)
        return -1;

    // create xpath evaluation context
    std::unique_ptr<xmlXPathContext> xpathCtx(xmlXPathNewContext(srcMLdoc.get()));
    if (!xpathCtx)
        return -1;

    // register srcML namespaces
    if (xmlXPathRegisterNs(xpathCtx.get(), BAD_CAST "src", BAD_CAST "http://www.srcML.org/srcML/src"))
        return -1;
    if (xmlXPathRegisterNs(xpathCtx.get(), BAD_CAST "cpp", BAD_CAST "http://www.srcML.org/srcML/cpp"))
        return -1;

    // evaluate xpath expression
    std::unique_ptr<xmlXPathObject> xpathResults(xmlXPathEvalExpression(BAD_CAST xpath, xpathCtx.get()));
    if (!xpathResults)
        return -1;

    // extract the count
    int count = xmlXPathCastToNumber(xpathResults.get());
    if (count < 0)
        return -1;

    return count;
}
