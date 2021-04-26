
//////////////////////////////////////////////////////////////
//
// Header file for BulletinBoardUI
//
//    This file is generated by RapidApp 1.1
//
//    This class implements the user interface portion of a class
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
//////////////////////////////////////////////////////////////
#ifndef BULLETINBOARDUI_H
#define BULLETINBOARDUI_H
#include <Vk/VkComponent.h>


//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations


class VkOptionMenu;
class VkMenuAction;
class VkMenuToggle;
class VkMenuItem;
class BulletinBoardUI : public VkComponent
{ 

  public:

    BulletinBoardUI(const char *, Widget);
    BulletinBoardUI(const char *);
    ~BulletinBoardUI();
    void create ( Widget );
    const char *  className();

    //---- Start editable code block: BulletinBoard public


    //---- End editable code block: BulletinBoard public


  protected:


    // Widgets created by this class

    Widget  _bulletinBoard;
    Widget  _estWorkLabel;
    Widget  _label;
    Widget  _label1;
    Widget  _label2;
    Widget  _label3;
    Widget  _label4;
    Widget  _label6;
    Widget  _label8;
    Widget  _omegaSize;
    Widget  _omegaXPos;
    Widget  _omegaYPos;
    Widget  _separator2;
    Widget  _separator3;
    Widget  _torusSizeLabel;
    Widget  _winSizeLabel;

    VkOptionMenu  *_numTorusTilesOptMenu;
    VkOptionMenu  *_numTorusTilesOptMenu1;
    VkOptionMenu  *_sampSizeOptMenu;

    VkMenuItem *_optionA;
    VkMenuItem *_optionA1;
    VkMenuItem *_optionA2;
    VkMenuItem *_optionB;
    VkMenuItem *_optionB1;
    VkMenuItem *_optionB10;
    VkMenuItem *_optionB11;
    VkMenuItem *_optionB12;
    VkMenuItem *_optionB13;
    VkMenuItem *_optionB14;
    VkMenuItem *_optionB15;
    VkMenuItem *_optionB16;
    VkMenuItem *_optionB17;
    VkMenuItem *_optionB18;
    VkMenuItem *_optionB19;
    VkMenuItem *_optionB2;
    VkMenuItem *_optionB20;
    VkMenuItem *_optionB21;
    VkMenuItem *_optionB22;
    VkMenuItem *_optionB23;
    VkMenuItem *_optionB3;
    VkMenuItem *_optionB4;
    VkMenuItem *_optionB5;
    VkMenuItem *_optionB6;
    VkMenuItem *_optionB7;
    VkMenuItem *_optionB8;
    VkMenuItem *_optionB9;


    // These virtual functions are called from the private callbacks (above)
    // Intended to be overriden in derived classes to define actions

    virtual void setNumSamples1 ( Widget, XtPointer );
    virtual void setNumSamples128 ( Widget, XtPointer );
    virtual void setNumSamples16 ( Widget, XtPointer );
    virtual void setNumSamples2 ( Widget, XtPointer );
    virtual void setNumSamples256 ( Widget, XtPointer );
    virtual void setNumSamples32 ( Widget, XtPointer );
    virtual void setNumSamples4 ( Widget, XtPointer );
    virtual void setNumSamples64 ( Widget, XtPointer );
    virtual void setNumSamples8 ( Widget, XtPointer );
    virtual void setNumTorus1 ( Widget, XtPointer );
    virtual void setNumTorus128 ( Widget, XtPointer );
    virtual void setNumTorus16 ( Widget, XtPointer );
    virtual void setNumTorus2 ( Widget, XtPointer );
    virtual void setNumTorus256 ( Widget, XtPointer );
    virtual void setNumTorus32 ( Widget, XtPointer );
    virtual void setNumTorus4 ( Widget, XtPointer );
    virtual void setNumTorus64 ( Widget, XtPointer );
    virtual void setNumTorus8 ( Widget, XtPointer );
    virtual void setOmegaWindowSize ( Widget, XtPointer );
    virtual void setOmegaXPos ( Widget, XtPointer );
    virtual void setOmegaYPos ( Widget, XtPointer );
    virtual void setSampleSize1 ( Widget, XtPointer );
    virtual void setSampleSize128 ( Widget, XtPointer );
    virtual void setSampleSize16 ( Widget, XtPointer );
    virtual void setSampleSize2 ( Widget, XtPointer );
    virtual void setSampleSize256 ( Widget, XtPointer );
    virtual void setSampleSize32 ( Widget, XtPointer );
    virtual void setSampleSize4 ( Widget, XtPointer );
    virtual void setSampleSize64 ( Widget, XtPointer );
    virtual void setSampleSize8 ( Widget, XtPointer );

    //---- Start editable code block: BulletinBoard protected


    //---- End editable code block: BulletinBoard protected


  private: 
    // Array of default resources

    static String      _defaultBulletinBoardUIResources[];

    // Callbacks to interface with Motif

    static void setNumSamples1Callback ( Widget, XtPointer, XtPointer );
    static void setNumSamples128Callback ( Widget, XtPointer, XtPointer );
    static void setNumSamples16Callback ( Widget, XtPointer, XtPointer );
    static void setNumSamples2Callback ( Widget, XtPointer, XtPointer );
    static void setNumSamples256Callback ( Widget, XtPointer, XtPointer );
    static void setNumSamples32Callback ( Widget, XtPointer, XtPointer );
    static void setNumSamples4Callback ( Widget, XtPointer, XtPointer );
    static void setNumSamples64Callback ( Widget, XtPointer, XtPointer );
    static void setNumSamples8Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus1Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus128Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus16Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus2Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus256Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus32Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus4Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus64Callback ( Widget, XtPointer, XtPointer );
    static void setNumTorus8Callback ( Widget, XtPointer, XtPointer );
    static void setOmegaWindowSizeCallback ( Widget, XtPointer, XtPointer );
    static void setOmegaXPosCallback ( Widget, XtPointer, XtPointer );
    static void setOmegaYPosCallback ( Widget, XtPointer, XtPointer );
    static void setSampleSize1Callback ( Widget, XtPointer, XtPointer );
    static void setSampleSize128Callback ( Widget, XtPointer, XtPointer );
    static void setSampleSize16Callback ( Widget, XtPointer, XtPointer );
    static void setSampleSize2Callback ( Widget, XtPointer, XtPointer );
    static void setSampleSize256Callback ( Widget, XtPointer, XtPointer );
    static void setSampleSize32Callback ( Widget, XtPointer, XtPointer );
    static void setSampleSize4Callback ( Widget, XtPointer, XtPointer );
    static void setSampleSize64Callback ( Widget, XtPointer, XtPointer );
    static void setSampleSize8Callback ( Widget, XtPointer, XtPointer );

    //---- Start editable code block: BulletinBoard private


    //---- End editable code block: BulletinBoard private
};
#endif

