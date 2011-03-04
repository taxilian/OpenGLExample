
#include "OpenGLExampleX11.h"
#include <gtk/gtkgl.h>
#include <GL/gl.h>

void OpenGLExampleX11::StaticInitialize()
{
    int c = 0;
    gdk_gl_init_check(&c, NULL);
}

void OpenGLExampleX11::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

OpenGLExampleX11::OpenGLExampleX11()
{
}

OpenGLExampleX11::~OpenGLExampleX11()
{
}

bool OpenGLExampleX11::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowX11 *win)
{
}

bool OpenGLExampleX11::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowX11 *win)
{
}

void OpenGLExampleX11::renderThread(FB::PluginWindowX11* win)
{
    GdkGLConfigMode glconf = static_cast<GdkGLConfigMode>(
            GDK_GL_MODE_RGB |
            GDK_GL_MODE_DOUBLE |
            GDK_GL_MODE_ACCUM |
            GDK_GL_MODE_ACCUM
            );
    glConfig = gdk_gl_config_new_by_mode(glconf);

    gtk_widget_set_gl_capability(win->getWidget(), glConfig, NULL, TRUE, GDK_GL_RGBA_TYPE);

    GdkGLContext *glcontext = gtk_widget_get_gl_context (win->getWidget());
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (win->getWidget());

    // Attach our OpenGL context to the widget
    gdk_gl_drawable_make_current(gldrawable, glcontext);
    try {
        while (!boost::this_thread::interruption_requested()) {
            render();
            GdkGLDrawable *gld = gtk_widget_get_gl_drawable (win->getWidget());
            if (gdk_gl_drawable_is_double_buffered (gld)) {
                gdk_gl_drawable_swap_buffers (gld);
            } else {
                glFlush();
            }
            boost::this_thread::sleep(boost::posix_time::milliseconds(20));
        }
    } catch (const boost::thread_interrupted&) {
    }
    // Shut down the opengl config and context objects
    if (glConfig) {
        g_object_unref(G_OBJECT(glConfig));
        glConfig = NULL;
    }
    GdkGLContext *glContext = gtk_widget_get_gl_context(win->getWidget());
    if (glContext) {
        g_object_unref(G_OBJECT(glContext));
        glContext = NULL;
    }
}
