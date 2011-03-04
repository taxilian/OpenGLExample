/**********************************************************\

  Auto-generated OpenGLExampleAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "OpenGLExample.h"

#ifndef H_OpenGLExampleAPI
#define H_OpenGLExampleAPI

class OpenGLExampleAPI : public FB::JSAPIAuto
{
public:
    OpenGLExampleAPI(const OpenGLExamplePtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~OpenGLExampleAPI();

    OpenGLExamplePtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Method test-event
    void testEvent(const FB::variant& s);

private:
    OpenGLExampleWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_OpenGLExampleAPI

