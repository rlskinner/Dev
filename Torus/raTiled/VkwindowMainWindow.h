
//////////////////////////////////////////////////////////////
//
// Header file for VkwindowMainWindow
//
//    This class is a ViewKit VkWindow subclass
//
// Normally, very little in this file should need to be changed.
// Create/add/modify menus using the builder.
//
// Restrict changes to those sections between
// the "//--- Start/End editable code block" markers
// Doing so will allow you to make chnages using the builder
// without losing any changes you may have made manually
//
//////////////////////////////////////////////////////////////
#ifndef VKWINDOWMAINWINDOW_H
#define VKWINDOWMAINWINDOW_H
#include <Vk/VkWindow.h>

class VkMenuItem;
class VkMenuToggle;
class VkMenuConfirmFirstAction;
class VkSubMenu;
class VkRadioSubMenu;

//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations


//---- VkwindowMainWindow class declaration

class VkwindowMainWindow: public VkWindow { 

  public:

    VkwindowMainWindow( const char * name, 
                        ArgList args = NULL,
                        Cardinal argCount = 0 );
    ~VkwindowMainWindow();
    const char *className();
    virtual Boolean okToQuit();

    //---- Start editable code block: VkwindowMainWindow public


    //---- End editable code block: VkwindowMainWindow public


  protected:



    // Classes created by this class

    class BulletinBoard *_bulletinBoard;

    // Menu items created by this class

    //---- Start editable code block: VkwindowMainWindow protected


    //---- End editable code block: VkwindowMainWindow protected


  private:


    static String      _defaultVkwindowMainWindowResources[];

    //---- Start editable code block: VkwindowMainWindow private


    //---- End editable code block: VkwindowMainWindow private


};
#endif
