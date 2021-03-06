#ifndef	_glutApp_h_
#define	_glutApp_h_
//
//	class to enable better code sharing and modularity
//	for torus algorithms & GLUT
//

// we should really make this class completely abstract,
//	with no data, but cheat for now
class	glutApp {
public:
    // create one based on arguments
    static	glutApp	*createApp( int &argc, char *argv[] );

    // singleton interface
    static	glutApp	*getApp();

protected:
    glutApp();

    virtual void	createWindows() = 0;

    virtual	void	display() = 0;
    virtual	void	displayInit() = 0;
    virtual	void	idle() = 0;
    virtual	void	idleInit() = 0;
    virtual	void	keyboard( unsigned char key, int x, int y ) = 0;
    virtual	void	mouse( int button, int state, int x, int y ) = 0;

    void	defaultKeyboardCB( unsigned char key, int x, int y );

    static	glutApp	*_theApp;

    virtual	void	init( int &argc, char *argv[] );

    int		_width;
    int		_height;
    int		_wid;

private:

    static	void	 displayFuncCB();
    static	void	    idleFuncCB();
    static	void	keyboardFuncCB( unsigned char key, int x, int y );
    static	void	   mouseFuncCB( int button, int state, int x, int y );
};

#endif	// _glutApp_h_
