#include	<Xm/Xm.h>
#include	<Xm/Form.h>
#include	<X11/StringDefs.h>
#include	"GL/GLwMDrawA.h"

#include	<GL/gl.h>
#include	<GL/glu.h>
#include	<stdio.h>
#include	<stdlib.h>

#include	<oglGraphicsApp.h>

GLXContext	glxContext;
Widget		glxWidget;
const	char*		widgetName = "glwidget";
XtWorkProcId workprocid = NULL;
static	XtAppContext	appContext;


void
swapbuffers()
{
    glFlush();
    glXSwapBuffers( XtDisplay(glxWidget), XtWindow(glxWidget) );
    glXWaitX();
}

void
inputCB( Widget, XtPointer, XtPointer )
{
}

//
//  animation callback
Boolean
drawSceneCB( XtPointer clientData )
{
    GLwDrawingAreaMakeCurrent( glxWidget, glxContext );
    oglGraphicsApp	*app = (oglGraphicsApp*)clientData;
    app->doFrame();
    return FALSE;
}


void
exposeCB( Widget, XtPointer clientData, XtPointer /* callData */ )
{
    oglGraphicsApp	*app = (oglGraphicsApp*)clientData;
    app->redraw();
    workprocid = XtAppAddWorkProc( appContext, drawSceneCB, clientData );
}

void
resizeCB( Widget w, XtPointer clientData, XtPointer callData )
{
    GLwDrawingAreaCallbackStruct	*call;
    call = (GLwDrawingAreaCallbackStruct*)callData;

    GLwDrawingAreaMakeCurrent( w, glxContext );
    oglGraphicsApp	*app = (oglGraphicsApp*)clientData;
    app->resize( call->width, call->height );
}

void
initCB( Widget w, XtPointer clientData, XtPointer /* callData */ )
{
    // 
    //  do window initialization
    //
    Arg	args[1];
    XVisualInfo *vi;

    XtSetArg( args[0], GLwNvisualInfo, &vi );
    XtGetValues( w, args, 1 );
    glxContext = glXCreateContext( XtDisplay(w), vi, 0, GL_TRUE );
    glxWidget = w;

    GLwDrawingAreaMakeCurrent( w, glxContext );
    oglGraphicsApp	*app = (oglGraphicsApp*)clientData;
    app->graphicsInit( swapbuffers );
}



static	String fallback_resources[] = {
    "*%s*width: 1280",
    "*%s*height: 1024",
    // "*glwidget*doublebuffer: TRUE",
    // "*glwidget*allocateBackground: TRUE",
    NULL,
};

String	*combineResources( oglGraphicsApp *app ) 
{
    String	*appRes = app->getResources();

    int	numAppRes = 0;
    while( NULL != appRes[numAppRes] ) numAppRes++;

    int numMainRes = 0;
    while( NULL != fallback_resources[numMainRes] ) numMainRes++;

    String	*resources = new String[numAppRes+numMainRes+1];
    resources[numAppRes+numMainRes] = NULL;
    int	i;
    for( i=0; i<numAppRes; i++ ) {
	resources[i] = new char[128];
	sprintf( resources[i], appRes[i], widgetName );
    }

    for( i=0; i<numMainRes; i++ ) {
	resources[i+numAppRes] = new char[128];
	sprintf( resources[i+numAppRes], fallback_resources[i], widgetName );
    }

    return resources;
}

int
main( int argc, char **argv )
{
    oglGraphicsApp	*app = (oglGraphicsApp*)makeDefaultApplication();

    if( app->parseArgs( argc, argv ) ) {
	return 1;
    }

    String	*fallback_resources = combineResources( app );
    Widget	topLevel = XtAppInitialize( &appContext, "Mixed", NULL,
				0, &argc, argv,
				fallback_resources, NULL, 0 );

    Arg	args[20];
    int	n = 0;
    Widget form = XmCreateForm( topLevel, "form", args, n );
    XtManageChild( form );

    n = 0;
    XtSetArg( args[n], XmNbottomAttachment, XmATTACH_FORM );
    n++;
    XtSetArg( args[n], XmNtopAttachment, XmATTACH_FORM );
    n++;
    XtSetArg( args[n], XmNleftAttachment, XmATTACH_FORM );
    n++;
    XtSetArg( args[n], XmNrightAttachment, XmATTACH_FORM );
    n++;
    Widget	glw = GLwCreateMDrawingArea( form, "glwidget", args, n );
    XtManageChild( glw );

    XtAddCallback( glw, GLwNexposeCallback, exposeCB, (XtPointer)app );
    XtAddCallback( glw, GLwNresizeCallback, resizeCB, (XtPointer)app );
    XtAddCallback( glw, GLwNginitCallback, initCB, (XtPointer)app );
    XtAddCallback( glw, GLwNinputCallback, inputCB, (XtPointer)app );

    XtRealizeWidget( topLevel );
    XtAppMainLoop( appContext );
    return 0;
}
