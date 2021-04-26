
/////////////////////////////////////////////////////////////
//
// Source file for MenuBar1UI
//
//    This class implements the user interface created in 
//    the interface builder. Normally it is not used directly.
//    Instead the subclass, MenuBar1 is instantiated
//
//    To extend or alter the behavior of this class, you should
//    modify the MenuBar1 files
//
//    Restrict changes to those sections between
//    the "//--- Start/End editable code block" markers
//
//    This will allow the builder to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//
//
/////////////////////////////////////////////////////////////


#include "MenuBar1UI.h" // Generated header file for this class

#include <Vk/VkResource.h>
//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations


// These are default resources for widgets in objects of this class
// All resources will be prepended by *<name> at instantiation,
// where <name> is the name of the specific instance, as well as the
// name of the baseWidget. These are only defaults, and may be overriden
// in a resource file by providing a more specific resource name

String  MenuBar1UI::_defaultMenuBar1UIResources[] = {
        (char*)NULL
};

MenuBar1UI::MenuBar1UI(const char *name) : VkComponent(name) 
{ 
    // No widgets are created by this constructor.
    // If an application creates a component using this constructor,
    // It must explictly call create at a later time.
    // This is mostly useful when adding pre-widget creation
    // code to a derived class constructor.

    //---- Start editable code block: MenuBar1 constructor 2


    //---- End editable code block: MenuBar1 constructor 2


} // End Constructor




MenuBar1UI::MenuBar1UI(const char *name, Widget parent) : VkComponent(name) 
{ 
    // Call creation function to build the widget tree.

     create(parent);

    //---- Start editable code block: MenuBar1 constructor


    //---- End editable code block: MenuBar1 constructor


} // End Constructor


MenuBar1UI::~MenuBar1UI() 
{
    // Base class destroys widgets

    //---- Start editable code block: MenuBar1UI destructor


    //---- End editable code block: MenuBar1UI destructor
} // End destructor



void MenuBar1UI::create ( Widget parent )
{
    Arg      args[4];
    Cardinal count;
    count = 0;

    // Load any class-defaulted resources for this object

    setDefaultResources(parent, _defaultMenuBar1UIResources  );


    // Create an unmanaged widget as the top of the widget hierarchy


    count = 0;
    _baseWidget = _menuBar1 = XmCreateMenuBar(parent, 
                                        _name,
                                        args, count );

    // install a callback to guard against unexpected widget destruction

    installDestroyHandler();


    // Create widgets used in this component
    // All variables are data members of this class


    count = 0;
    _pane1PulldownMenu = XmCreatePulldownMenu( _baseWidget, 
                                                            "pane1PulldownMenu",
                                                            args, count );



    _action1 = XtVaCreateManagedWidget  ( "action1",
                                           xmPushButtonGadgetClass,
                                           _pane1PulldownMenu, 
                                           (XtPointer) NULL ); 


    _action2 = XtVaCreateManagedWidget  ( "action2",
                                           xmPushButtonGadgetClass,
                                           _pane1PulldownMenu, 
                                           (XtPointer) NULL ); 


    _action3 = XtVaCreateManagedWidget  ( "action3",
                                           xmPushButtonGadgetClass,
                                           _pane1PulldownMenu, 
                                           (XtPointer) NULL ); 


    XtVaSetValues ( _pane1PulldownMenu, 
                    XmNwidth, 81, 
                    XmNheight, 78, 
                    (XtPointer) NULL );
    _pane1 = XtVaCreateManagedWidget  ( "pane1",
                                         xmCascadeButtonWidgetClass,
                                         _baseWidget, 
                                         XmNwidth, 61, 
                                         XmNheight, 24, 
                                         XmNsubMenuId, _pane1PulldownMenu, 
                                         (XtPointer) NULL ); 


    XtVaSetValues ( _pane1PulldownMenu, 
                    XmNwidth, 81, 
                    XmNheight, 78, 
                    (XtPointer) NULL );

    count = 0;
    _pane2PulldownMenu = XmCreatePulldownMenu( _baseWidget, 
                                                            "pane2PulldownMenu",
                                                            args, count );



    _action4 = XtVaCreateManagedWidget  ( "action4",
                                           xmPushButtonGadgetClass,
                                           _pane2PulldownMenu, 
                                           (XtPointer) NULL ); 


    _action5 = XtVaCreateManagedWidget  ( "action5",
                                           xmPushButtonGadgetClass,
                                           _pane2PulldownMenu, 
                                           (XtPointer) NULL ); 


    _action6 = XtVaCreateManagedWidget  ( "action6",
                                           xmPushButtonGadgetClass,
                                           _pane2PulldownMenu, 
                                           (XtPointer) NULL ); 


    XtVaSetValues ( _pane2PulldownMenu, 
                    XmNwidth, 81, 
                    XmNheight, 78, 
                    (XtPointer) NULL );
    _pane2 = XtVaCreateManagedWidget  ( "pane2",
                                         xmCascadeButtonWidgetClass,
                                         _baseWidget, 
                                         XmNwidth, 62, 
                                         XmNheight, 24, 
                                         XmNsubMenuId, _pane2PulldownMenu, 
                                         (XtPointer) NULL ); 


    XtVaSetValues ( _pane2PulldownMenu, 
                    XmNwidth, 81, 
                    XmNheight, 78, 
                    (XtPointer) NULL );
    //---- Start editable code block: MenuBar1UI create


    //---- End editable code block: MenuBar1UI create
}

const char * MenuBar1UI::className()
{
    return ("MenuBar1UI");
} // End className()




/////////////////////////////////////////////////////////////// 
// The following functions are called from the menu items 
// in this window.
/////////////////////////////////// 



