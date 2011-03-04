
/**********************************************************\

  OpenGLExampleX11 - X11 specific code for OpenGLExample
                     plugin
\**********************************************************/
#ifndef H_OpenGLExampleX11PLUGIN
#define H_OpenGLExampleX11PLUGIN

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkgl.h>

#include "X11/PluginWindowX11.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"

#include <boost/thread.hpp>

#include "OpenGLExample.h"

FB_FORWARD_PTR(OpenGLExampleX11)
class OpenGLExampleX11 : public OpenGLExample
{
public:
    static void StaticInitialize();
    static void StaticDeinitialize();
public:
    OpenGLExampleX11();
    virtual ~OpenGLExampleX11();

public:
    //virtual bool isWindowless() { return false; }

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowX11)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowX11)
        PLUGIN_EVENT_MAP_CASCADE(OpenGLExample)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowX11 *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowX11 *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

private:
    void renderThread(FB::PluginWindowX11* win);
    boost::thread rThread;
    GdkGLConfig *glConfig;
};


#endif

