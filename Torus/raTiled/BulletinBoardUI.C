
/////////////////////////////////////////////////////////////
//
// Source file for BulletinBoardUI
//
//    This class implements the user interface created in 
//    the interface builder. Normally it is not used directly.
//    Instead the subclass, BulletinBoard is instantiated
//
//    To extend or alter the behavior of this class, you should
//    modify the BulletinBoard files
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


#include "BulletinBoardUI.h" // Generated header file for this class

#include <Xm/BulletinB.h> 
#include <Xm/Label.h> 
#include <Xm/Separator.h> 
#include <Xm/TextF.h> 
#include <Vk/VkResource.h>
#include <Vk/VkOptionMenu.h>
#include <Vk/VkMenuItem.h>
//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations



// These are default resources for widgets in objects of this class
// All resources will be prepended by *<name> at instantiation,
// where <name> is the name of the specific instance, as well as the
// name of the baseWidget. These are only defaults, and may be overriden
// in a resource file by providing a more specific resource name

String  BulletinBoardUI::_defaultBulletinBoardUIResources[] = {
        "*numTorusTilesOptMenu1.labelString:  Number of Samples",
        "*optionA2.labelString:  1",
        "*optionB16.labelString:  2",
        "*optionB17.labelString:  4",
        "*optionB18.labelString:  8",
        "*optionB19.labelString:  16",
        "*optionB20.labelString:  32",
        "*optionB21.labelString:  64",
        "*optionB22.labelString:  128",
        "*optionB23.labelString:  256",
        "*torusSizeLabel.labelString:  ----",
        "*label8.labelString:  Torus size = window size / number torus tiles = ",
        "*winSizeLabel.labelString:  ----",
        "*label6.labelString:  Window Size = # samples / sample tile size =",
        "*estWorkLabel.labelString:  ----",
        "*label4.labelString:  Work ~ ( # samples x sample tile size",
        "*sampSizeOptMenu.labelString:  Sample Tile Size",
        "*optionA1.labelString:  1",
        "*optionB8.labelString:  2",
        "*optionB9.labelString:  4",
        "*optionB10.labelString:  8",
        "*optionB11.labelString:  16",
        "*optionB12.labelString:  32",
        "*optionB13.labelString:  64",
        "*optionB14.labelString:  128",
        "*optionB15.labelString:  256",
        "*numTorusTilesOptMenu.labelString:  Number of Torus Tiles",
        "*optionA.labelString:  1",
        "*optionB.labelString:  2",
        "*optionB1.labelString:  4",
        "*optionB6.labelString:  8",
        "*optionB2.labelString:  16",
        "*optionB3.labelString:  32",
        "*optionB4.labelString:  64",
        "*optionB5.labelString:  128",
        "*optionB7.labelString:  256",
        "*label3.labelString:  Display",
        "*label2.labelString:  Size",
        "*label1.labelString:  Origin",
        "*omegaXPos.value:  ",
        "*label.labelString:  Sampling Area in Omega Space",
        (char*)NULL
};

BulletinBoardUI::BulletinBoardUI(const char *name) : VkComponent(name) 
{ 
    // No widgets are created by this constructor.
    // If an application creates a component using this constructor,
    // It must explictly call create at a later time.
    // This is mostly useful when adding pre-widget creation
    // code to a derived class constructor.

    //---- Start editable code block: BulletinBoard constructor 2


    //---- End editable code block: BulletinBoard constructor 2


} // End Constructor




BulletinBoardUI::BulletinBoardUI(const char *name, Widget parent) : VkComponent(name) 
{ 
    // Call creation function to build the widget tree.

     create(parent);

    //---- Start editable code block: BulletinBoard constructor


    //---- End editable code block: BulletinBoard constructor


} // End Constructor


BulletinBoardUI::~BulletinBoardUI() 
{
    // Base class destroys widgets

    //---- Start editable code block: BulletinBoardUI destructor


    //---- End editable code block: BulletinBoardUI destructor
} // End destructor



void BulletinBoardUI::create ( Widget parent )
{
    Arg      args[8];
    Cardinal count;
    count = 0;

    // Load any class-defaulted resources for this object

    setDefaultResources(parent, _defaultBulletinBoardUIResources  );


    // Create an unmanaged widget as the top of the widget hierarchy

    _baseWidget = _bulletinBoard = XtVaCreateWidget ( _name,
                                                      xmBulletinBoardWidgetClass,
                                                      parent, 
                                                      XmNresizePolicy, XmRESIZE_GROW, 
                                                      (XtPointer) NULL ); 

    // install a callback to guard against unexpected widget destruction

    installDestroyHandler();


    // Create widgets used in this component
    // All variables are data members of this class

    _numTorusTilesOptMenu1 = new VkOptionMenu ( _baseWidget);
    _optionA2 =  _numTorusTilesOptMenu1->addAction ( "optionA2", 
                                        &BulletinBoardUI::setNumSamples1Callback, 
                                        (XtPointer) this );

    _optionB16 =  _numTorusTilesOptMenu1->addAction ( "optionB16", 
                                        &BulletinBoardUI::setNumSamples2Callback, 
                                        (XtPointer) this );

    _optionB17 =  _numTorusTilesOptMenu1->addAction ( "optionB17", 
                                        &BulletinBoardUI::setNumSamples4Callback, 
                                        (XtPointer) this );

    _optionB18 =  _numTorusTilesOptMenu1->addAction ( "optionB18", 
                                        &BulletinBoardUI::setNumSamples8Callback, 
                                        (XtPointer) this );

    _optionB19 =  _numTorusTilesOptMenu1->addAction ( "optionB19", 
                                        &BulletinBoardUI::setNumSamples16Callback, 
                                        (XtPointer) this );

    _optionB20 =  _numTorusTilesOptMenu1->addAction ( "optionB20", 
                                        &BulletinBoardUI::setNumSamples32Callback, 
                                        (XtPointer) this );

    _optionB21 =  _numTorusTilesOptMenu1->addAction ( "optionB21", 
                                        &BulletinBoardUI::setNumSamples64Callback, 
                                        (XtPointer) this );

    _optionB22 =  _numTorusTilesOptMenu1->addAction ( "optionB22", 
                                        &BulletinBoardUI::setNumSamples128Callback, 
                                        (XtPointer) this );

    _optionB23 =  _numTorusTilesOptMenu1->addAction ( "optionB23", 
                                        &BulletinBoardUI::setNumSamples256Callback, 
                                        (XtPointer) this );

    _torusSizeLabel = XtVaCreateManagedWidget  ( "torusSizeLabel",
                                                  xmLabelWidgetClass,
                                                  _baseWidget, 
                                                  XmNlabelType, XmSTRING, 
                                                  XmNx, 360, 
                                                  XmNy, 370, 
                                                  XmNwidth, 40, 
                                                  XmNheight, 20, 
                                                  (XtPointer) NULL ); 


    _label8 = XtVaCreateManagedWidget  ( "label8",
                                          xmLabelWidgetClass,
                                          _baseWidget, 
                                          XmNlabelType, XmSTRING, 
                                          XmNx, 20, 
                                          XmNy, 380, 
                                          XmNwidth, 328, 
                                          XmNheight, 20, 
                                          (XtPointer) NULL ); 


    _winSizeLabel = XtVaCreateManagedWidget  ( "winSizeLabel",
                                                xmLabelWidgetClass,
                                                _baseWidget, 
                                                XmNlabelType, XmSTRING, 
                                                XmNx, 340, 
                                                XmNy, 350, 
                                                XmNwidth, 40, 
                                                XmNheight, 20, 
                                                (XtPointer) NULL ); 


    _label6 = XtVaCreateManagedWidget  ( "label6",
                                          xmLabelWidgetClass,
                                          _baseWidget, 
                                          XmNlabelType, XmSTRING, 
                                          XmNx, 20, 
                                          XmNy, 350, 
                                          XmNwidth, 307, 
                                          XmNheight, 20, 
                                          (XtPointer) NULL ); 


    _estWorkLabel = XtVaCreateManagedWidget  ( "estWorkLabel",
                                                xmLabelWidgetClass,
                                                _baseWidget, 
                                                XmNlabelType, XmSTRING, 
                                                XmNx, 330, 
                                                XmNy, 310, 
                                                XmNwidth, 40, 
                                                XmNheight, 20, 
                                                (XtPointer) NULL ); 


    _label4 = XtVaCreateManagedWidget  ( "label4",
                                          xmLabelWidgetClass,
                                          _baseWidget, 
                                          XmNlabelType, XmSTRING, 
                                          XmNx, 20, 
                                          XmNy, 310, 
                                          XmNwidth, 294, 
                                          XmNheight, 20, 
                                          (XtPointer) NULL ); 


    _separator3 = XtVaCreateManagedWidget  ( "separator3",
                                              xmSeparatorWidgetClass,
                                              _baseWidget, 
                                              XmNx, 10, 
                                              XmNy, 270, 
                                              XmNwidth, 477, 
                                              XmNheight, 20, 
                                              (XtPointer) NULL ); 


    _sampSizeOptMenu = new VkOptionMenu ( _baseWidget);
    _optionA1 =  _sampSizeOptMenu->addAction ( "optionA1", 
                                        &BulletinBoardUI::setNumTorus1Callback, 
                                        (XtPointer) this );

    _optionB8 =  _sampSizeOptMenu->addAction ( "optionB8", 
                                        &BulletinBoardUI::setNumTorus2Callback, 
                                        (XtPointer) this );

    _optionB9 =  _sampSizeOptMenu->addAction ( "optionB9", 
                                        &BulletinBoardUI::setNumTorus4Callback, 
                                        (XtPointer) this );

    _optionB10 =  _sampSizeOptMenu->addAction ( "optionB10", 
                                        &BulletinBoardUI::setNumTorus8Callback, 
                                        (XtPointer) this );

    _optionB11 =  _sampSizeOptMenu->addAction ( "optionB11", 
                                        &BulletinBoardUI::setNumTorus16Callback, 
                                        (XtPointer) this );

    _optionB12 =  _sampSizeOptMenu->addAction ( "optionB12", 
                                        &BulletinBoardUI::setNumTorus32Callback, 
                                        (XtPointer) this );

    _optionB13 =  _sampSizeOptMenu->addAction ( "optionB13", 
                                        &BulletinBoardUI::setNumTorus64Callback, 
                                        (XtPointer) this );

    _optionB14 =  _sampSizeOptMenu->addAction ( "optionB14", 
                                        &BulletinBoardUI::setNumTorus128Callback, 
                                        (XtPointer) this );

    _optionB15 =  _sampSizeOptMenu->addAction ( "optionB15", 
                                        &BulletinBoardUI::setNumTorus256Callback, 
                                        (XtPointer) this );

    _numTorusTilesOptMenu = new VkOptionMenu ( _baseWidget);
    _optionA =  _numTorusTilesOptMenu->addAction ( "optionA", 
                                        &BulletinBoardUI::setSampleSize1Callback, 
                                        (XtPointer) this );

    _optionB =  _numTorusTilesOptMenu->addAction ( "optionB", 
                                        &BulletinBoardUI::setSampleSize2Callback, 
                                        (XtPointer) this );

    _optionB1 =  _numTorusTilesOptMenu->addAction ( "optionB1", 
                                        &BulletinBoardUI::setSampleSize4Callback, 
                                        (XtPointer) this );

    _optionB6 =  _numTorusTilesOptMenu->addAction ( "optionB6", 
                                        &BulletinBoardUI::setSampleSize8Callback, 
                                        (XtPointer) this );

    _optionB2 =  _numTorusTilesOptMenu->addAction ( "optionB2", 
                                        &BulletinBoardUI::setSampleSize16Callback, 
                                        (XtPointer) this );

    _optionB3 =  _numTorusTilesOptMenu->addAction ( "optionB3", 
                                        &BulletinBoardUI::setSampleSize32Callback, 
                                        (XtPointer) this );

    _optionB4 =  _numTorusTilesOptMenu->addAction ( "optionB4", 
                                        &BulletinBoardUI::setSampleSize64Callback, 
                                        (XtPointer) this );

    _optionB5 =  _numTorusTilesOptMenu->addAction ( "optionB5", 
                                        &BulletinBoardUI::setSampleSize128Callback, 
                                        (XtPointer) this );

    _optionB7 =  _numTorusTilesOptMenu->addAction ( "optionB7", 
                                        &BulletinBoardUI::setSampleSize256Callback, 
                                        (XtPointer) this );

    _label3 = XtVaCreateManagedWidget  ( "label3",
                                          xmLabelWidgetClass,
                                          _baseWidget, 
                                          XmNlabelType, XmSTRING, 
                                          XmNx, 20, 
                                          XmNy, 160, 
                                          XmNwidth, 56, 
                                          XmNheight, 20, 
                                          (XtPointer) NULL ); 


    _separator2 = XtVaCreateManagedWidget  ( "separator2",
                                              xmSeparatorWidgetClass,
                                              _baseWidget, 
                                              XmNx, 10, 
                                              XmNy, 140, 
                                              XmNwidth, 480, 
                                              XmNheight, 20, 
                                              (XtPointer) NULL ); 


    _omegaSize = XtVaCreateManagedWidget  ( "omegaSize",
                                             xmTextFieldWidgetClass,
                                             _baseWidget, 
                                             XmNx, 100, 
                                             XmNy, 90, 
                                             XmNwidth, 120, 
                                             XmNheight, 30, 
                                             (XtPointer) NULL ); 

    XtAddCallback ( _omegaSize,
                    XmNactivateCallback,
                    &BulletinBoardUI::setOmegaWindowSizeCallback,
                    (XtPointer) this ); 


    _label2 = XtVaCreateManagedWidget  ( "label2",
                                          xmLabelWidgetClass,
                                          _baseWidget, 
                                          XmNlabelType, XmSTRING, 
                                          XmNx, 20, 
                                          XmNy, 90, 
                                          XmNwidth, 32, 
                                          XmNheight, 20, 
                                          (XtPointer) NULL ); 


    _omegaYPos = XtVaCreateManagedWidget  ( "omegaYPos",
                                             xmTextFieldWidgetClass,
                                             _baseWidget, 
                                             XmNx, 230, 
                                             XmNy, 50, 
                                             XmNwidth, 120, 
                                             XmNheight, 30, 
                                             (XtPointer) NULL ); 

    XtAddCallback ( _omegaYPos,
                    XmNactivateCallback,
                    &BulletinBoardUI::setOmegaYPosCallback,
                    (XtPointer) this ); 


    _label1 = XtVaCreateManagedWidget  ( "label1",
                                          xmLabelWidgetClass,
                                          _baseWidget, 
                                          XmNlabelType, XmSTRING, 
                                          XmNx, 20, 
                                          XmNy, 50, 
                                          XmNwidth, 48, 
                                          XmNheight, 20, 
                                          (XtPointer) NULL ); 


    _omegaXPos = XtVaCreateManagedWidget  ( "omegaXPos",
                                             xmTextFieldWidgetClass,
                                             _baseWidget, 
                                             XmNx, 100, 
                                             XmNy, 50, 
                                             XmNwidth, 120, 
                                             XmNheight, 30, 
                                             (XtPointer) NULL ); 

    XtAddCallback ( _omegaXPos,
                    XmNactivateCallback,
                    &BulletinBoardUI::setOmegaXPosCallback,
                    (XtPointer) this ); 


    _label = XtVaCreateManagedWidget  ( "label",
                                         xmLabelWidgetClass,
                                         _baseWidget, 
                                         XmNlabelType, XmSTRING, 
                                         XmNx, 20, 
                                         XmNy, 20, 
                                         XmNwidth, 222, 
                                         XmNheight, 20, 
                                         (XtPointer) NULL ); 


    XtVaSetValues ( _numTorusTilesOptMenu1->baseWidget(),
                    XmNx, 10, 
                    XmNy, 130, 
                    XmNwidth, 232, 
                    XmNheight, 32, 
                    (XtPointer) NULL );
    XtVaSetValues ( _sampSizeOptMenu->baseWidget(),
                    XmNx, 20, 
                    XmNy, 230, 
                    (XtPointer) NULL );
    XtVaSetValues ( _numTorusTilesOptMenu->baseWidget(),
                    XmNx, 20, 
                    XmNy, 200, 
                    XmNwidth, 250, 
                    XmNheight, 30, 
                    (XtPointer) NULL );
    //---- Start editable code block: BulletinBoardUI create


    //---- End editable code block: BulletinBoardUI create
}

const char * BulletinBoardUI::className()
{
    return ("BulletinBoardUI");
} // End className()




/////////////////////////////////////////////////////////////// 
// The following functions are static member functions used to 
// interface with Motif.
/////////////////////////////////// 

void BulletinBoardUI::setNumSamples1Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples1 ( w, callData );
}

void BulletinBoardUI::setNumSamples128Callback ( Widget    w,
                                                 XtPointer clientData,
                                                 XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples128 ( w, callData );
}

void BulletinBoardUI::setNumSamples16Callback ( Widget    w,
                                                XtPointer clientData,
                                                XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples16 ( w, callData );
}

void BulletinBoardUI::setNumSamples2Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples2 ( w, callData );
}

void BulletinBoardUI::setNumSamples256Callback ( Widget    w,
                                                 XtPointer clientData,
                                                 XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples256 ( w, callData );
}

void BulletinBoardUI::setNumSamples32Callback ( Widget    w,
                                                XtPointer clientData,
                                                XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples32 ( w, callData );
}

void BulletinBoardUI::setNumSamples4Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples4 ( w, callData );
}

void BulletinBoardUI::setNumSamples64Callback ( Widget    w,
                                                XtPointer clientData,
                                                XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples64 ( w, callData );
}

void BulletinBoardUI::setNumSamples8Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumSamples8 ( w, callData );
}

void BulletinBoardUI::setNumTorus1Callback ( Widget    w,
                                             XtPointer clientData,
                                             XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus1 ( w, callData );
}

void BulletinBoardUI::setNumTorus128Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus128 ( w, callData );
}

void BulletinBoardUI::setNumTorus16Callback ( Widget    w,
                                              XtPointer clientData,
                                              XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus16 ( w, callData );
}

void BulletinBoardUI::setNumTorus2Callback ( Widget    w,
                                             XtPointer clientData,
                                             XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus2 ( w, callData );
}

void BulletinBoardUI::setNumTorus256Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus256 ( w, callData );
}

void BulletinBoardUI::setNumTorus32Callback ( Widget    w,
                                              XtPointer clientData,
                                              XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus32 ( w, callData );
}

void BulletinBoardUI::setNumTorus4Callback ( Widget    w,
                                             XtPointer clientData,
                                             XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus4 ( w, callData );
}

void BulletinBoardUI::setNumTorus64Callback ( Widget    w,
                                              XtPointer clientData,
                                              XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus64 ( w, callData );
}

void BulletinBoardUI::setNumTorus8Callback ( Widget    w,
                                             XtPointer clientData,
                                             XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setNumTorus8 ( w, callData );
}

void BulletinBoardUI::setOmegaWindowSizeCallback ( Widget    w,
                                                   XtPointer clientData,
                                                   XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setOmegaWindowSize ( w, callData );
}

void BulletinBoardUI::setOmegaXPosCallback ( Widget    w,
                                             XtPointer clientData,
                                             XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setOmegaXPos ( w, callData );
}

void BulletinBoardUI::setOmegaYPosCallback ( Widget    w,
                                             XtPointer clientData,
                                             XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setOmegaYPos ( w, callData );
}

void BulletinBoardUI::setSampleSize1Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize1 ( w, callData );
}

void BulletinBoardUI::setSampleSize128Callback ( Widget    w,
                                                 XtPointer clientData,
                                                 XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize128 ( w, callData );
}

void BulletinBoardUI::setSampleSize16Callback ( Widget    w,
                                                XtPointer clientData,
                                                XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize16 ( w, callData );
}

void BulletinBoardUI::setSampleSize2Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize2 ( w, callData );
}

void BulletinBoardUI::setSampleSize256Callback ( Widget    w,
                                                 XtPointer clientData,
                                                 XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize256 ( w, callData );
}

void BulletinBoardUI::setSampleSize32Callback ( Widget    w,
                                                XtPointer clientData,
                                                XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize32 ( w, callData );
}

void BulletinBoardUI::setSampleSize4Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize4 ( w, callData );
}

void BulletinBoardUI::setSampleSize64Callback ( Widget    w,
                                                XtPointer clientData,
                                                XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize64 ( w, callData );
}

void BulletinBoardUI::setSampleSize8Callback ( Widget    w,
                                               XtPointer clientData,
                                               XtPointer callData ) 
{ 
    BulletinBoardUI* obj = ( BulletinBoardUI * ) clientData;
    obj->setSampleSize8 ( w, callData );
}



/////////////////////////////////////////////////////////////// 
// The following functions are called from the menu items 
// in this window.
/////////////////////////////////// 

void BulletinBoardUI::setNumSamples1 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples1Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumSamples128 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples128Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumSamples16 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples16Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumSamples2 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples2Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumSamples256 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples256Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumSamples32 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples32Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumSamples4 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples4Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumSamples64 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples64Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumSamples8 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumSamples8Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus1 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus1Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus128 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus128Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus16 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus16Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus2 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus2Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus256 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus256Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus32 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus32Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus4 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus4Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus64 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus64Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setNumTorus8 ( Widget, XtPointer ) 
{
    // This virtual function is called from setNumTorus8Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setOmegaWindowSize ( Widget, XtPointer ) 
{
    // This virtual function is called from setOmegaWindowSizeCallback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setOmegaXPos ( Widget, XtPointer ) 
{
    // This virtual function is called from setOmegaXPosCallback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setOmegaYPos ( Widget, XtPointer ) 
{
    // This virtual function is called from setOmegaYPosCallback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize1 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize1Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize128 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize128Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize16 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize16Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize2 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize2Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize256 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize256Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize32 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize32Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize4 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize4Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize64 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize64Callback.
    // This function is normally overriden by a derived class.

}

void BulletinBoardUI::setSampleSize8 ( Widget, XtPointer ) 
{
    // This virtual function is called from setSampleSize8Callback.
    // This function is normally overriden by a derived class.

}



