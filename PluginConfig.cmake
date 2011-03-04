#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for OpenGL Example
#
#\**********************************************************/

set(PLUGIN_NAME "OpenGLExample")
set(PLUGIN_PREFIX "OGL")
set(COMPANY_NAME "FireBreathDevTeam")

# ActiveX constants:
set(FBTYPELIB_NAME OpenGLExampleLib)
set(FBTYPELIB_DESC "OpenGLExample 1.0 Type Library")
set(IFBControl_DESC "OpenGLExample Control Interface")
set(FBControl_DESC "OpenGLExample Control Class")
set(IFBComJavascriptObject_DESC "OpenGLExample IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "OpenGLExample ComJavascriptObject Class")
set(IFBComEventSource_DESC "OpenGLExample IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 0b82c1b9-3a9f-544c-81df-06dad2256bfa)
set(IFBControl_GUID 9e0fa492-c491-5639-91c9-af8b710eb71f)
set(FBControl_GUID ed52c558-1f10-5c95-92a1-d93e9ca38eb0)
set(IFBComJavascriptObject_GUID b6feedeb-2fd2-5962-a903-e8aeb922eb79)
set(FBComJavascriptObject_GUID e87c2762-1413-58dc-ad6b-ec396435e6dc)
set(IFBComEventSource_GUID 6fed6ea3-f1d9-5309-8354-ade1d693f935)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "FireBreathDevTeam.OpenGLExample")
set(MOZILLA_PLUGINID "firebreathdevteam.com/OpenGLExample")

# strings
set(FBSTRING_CompanyName "FireBreath Dev Team")
set(FBSTRING_FileDescription "Example plugin using opengl")
set(FBSTRING_PLUGIN_VERSION "1.0.0")
set(FBSTRING_LegalCopyright "Copyright 2011 FireBreath Dev Team")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "OpenGL Example")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "OpenGL Example")
set(FBSTRING_MIMEType "application/x-openglexample")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

# set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
