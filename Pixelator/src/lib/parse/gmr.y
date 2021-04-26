
%{

#include	<stdio.h>
#include	"parse.h"
#include	"../util/image.h"

#define	TRUE	1
#define	FALSE	0

%}
%union	{
	int	ival;		/* integer value */
	double	rval;		/* floating point value */
	char	str[256];	/* character string */
	void	*vstar;		/* pointer */
}

/* terminal symbols returned by lex */
%token <ival>	INT 
%token <rval>	REAL 
%token <str>	STR

%token <ival>	COLORMAP 
%token <ival>	SIZE
%token <ival>	WRITE
%token <ival>	EXIT
%token <ival>	SGI
%token <ival>	FIT

%token <ival>	EDGE 
%token <ival>	DIR 
%token <ival>	DISK 
%token <ival>	LINE 
%token <ival>	RANDOM 
%token <ival>	NEIGHBOR4 
%token <ival>	NEIGHBOR8 
%token <ival>	CORNER 
%token <ival>	RING 
%token <ival>	SCATTERRING 
%token <ival>	CONE 
%token <ival>	CROSS 
%token <ival>	AT 
%token <ival>	CONST
%token <ival>	IMAGE 
%token <ival>	TOFIT

%token <ival>	BLUR
%token <ival>	COMPASS
%token <ival>	INVERT
%token <ival>	NEG
%token <ival>	OFFSET
%token <ival>	ROBERTS
%token <ival>	SCALE
%token <ival>	SHARPEN
%token <ival>	THRESH
%token <ival>	ZOOM

%token <ival>	CONTOUR
%token <ival>	GRAD
%token <ival>	LASTDIR

%token <ival>	SEED
%token <ival>	ACTION

%token <ival>	PERCENT

%token <ival>	ANY
%token <ival>	EMPTY
%token <ival>	WAITING
%token <ival>	SET
%token <ival>	ADD
%token <ival>	MULTIPLY
%token <ival>	ALL
%token <ival>	MIN
%token <ival>	MAX
%token <ival>	POSITIVE
%token <ival>	NEGATIVE

%type <vstar>	weight
%type <vstar>	image
%type <ival>	imageType

%type <rval>	real


/* %type <ival>	bool */
/* %token <ival>	TRUE FALSE  */



%start commandlist
%%

/*
 *  a list of commands
 */
commandlist:	| commandlist command
		;

command:	  option
		| seed
		| action
		;

/*
 *  all size and display options
 */
option:		  size
		| COLORMAP STR		{ _loadColormap( $2 ); }
		| WRITE STR imageType	{ _writeImage( $2, $3 ); }
		| EXIT			{ _exitWhenDone(); }
		;

imageType:				{ $$ = 0; }
		| SGI			{ $$ = 1; }
		| FIT			{ $$ = 0; }
		;

size:		  SIZE INT		{ _setSize( $2, $2 ); }
		| SIZE INT INT		{ _setSize( $2, $3 ); }
		| SIZE INT INT AT INT INT	
					{ _setSizeAt( $2, $3, $5, $6 ); }
		;

seed:		  SEED seedTypes
		;

seedTypes:	  edgeSeed
		| lineSeed
		| diskSeed
		| randomSeed
		| imageSeed
		;

edgeSeed:	  EDGE weight			{ _edgeSeed( $2 ); }
		;

diskSeed:	  DISK INT INT INT weight	
					{ _diskSeed( $2, $3, $4, $5 ); }
		;

lineSeed:	  LINE real real real real weight	
					{ _lineSeed( $2, $3, $4, $5, $6 ); }
		;

randomSeed:	  RANDOM INT weight		{ _randomIntSeed( $2, $3 ); }
		| RANDOM real PERCENT weight	{ _randomPerCentSeed( $2, $4 );}
		;

imageSeed:	  IMAGE image 			
			{ _imageSeed( $2, FALSE, 1.0, 1.0 ); }
		| IMAGE image SCALE real		
			{ _imageSeed( $2, FALSE, $4, $4 ); }
		| IMAGE image SCALE real real	
			{ _imageSeed( $2, FALSE, $4, $5 ); }
		| IMAGE image SCALE TOFIT		
			{ _imageSeed( $2, TRUE, 1.0, 1.0 ); }
		;


action:		  ACTION { _initActionOptions(); } actionOptions actionTypes
		;

actionOptions:	
		| '(' actionOption actionOptionList ')'  
		;

actionOptionList:
		| ',' actionOption actionOptionList
		;

actionOption:	  stateOption
		| functionOption
		| weightOption
		;

stateOption:	  ANY  			{ _setStateOption( ANY ); }
		| EMPTY  		{ _setStateOption( EMPTY ); }
		| WAITING  		{ _setStateOption( WAITING ); }
		;

functionOption:	  SET  			{ _setFunctionOption( SET ); }
		| ADD  			{ _setFunctionOption( ADD ); }
		| MULTIPLY  		{ _setFunctionOption( MULTIPLY ); }
		;

weightOption:	  ALL  			{ _setWeightOption( ALL ); }
		| MAX  			{ _setWeightOption( MAX ); }
		| MIN  			{ _setWeightOption( MIN ); }
		| POSITIVE  		{ _setWeightOption( POSITIVE ); }
		| NEGATIVE  		{ _setWeightOption( NEGATIVE ); }
		;

	
actionTypes:	  nbor4Action
		| nbor8Action
		| edgeAction
		| dirAction
		| cornerAction
		| ringAction
		| scatterRingAction
		| coneAction
		| crossAction
		;

nbor4Action:	  NEIGHBOR4 weight		{ _nborAction( 4, $2 ); }
nbor8Action:	  NEIGHBOR8 weight		{ _nborAction( 8, $2 ); }
edgeAction:	  EDGE weight			{ _edgeAction( $2 ); }
dirAction:	  DIR weight weight		{ _dirAction( $2, $3 ); }
cornerAction:	  CORNER weight			{ _cornerAction( $2 ); }
ringAction:	  RING INT weight		{ _ringAction( $2, $3 ); }
scatterRingAction: SCATTERRING INT weight	{ _scatterRingAction( $2, $3 );}
coneAction:	  CONE INT weight		{ _coneAction( $2, $3 ); }
crossAction:	  CROSS INT weight		{ _crossAction( $2, $3 ); }


image:		  STR				
			{ $$ = _openImageFile( $1 ); }
		| real 
			{ $$ = _constImage( $1 ); }
		| BLUR '(' image ')'
			{ $$ = _blurImage( $3, DEFAULT_VALUE, DEFAULT_VALUE );}
		| BLUR '(' image ',' real ')'
			{ $$ = _blurImage( $3, $5, DEFAULT_VALUE ); }
		| BLUR '(' image ',' real ',' real ')'
			{ $$ = _blurImage( $3, $5, $7 ); }
		| COMPASS '(' image ',' real ')'	
			{ $$ = _compassImage( $3, $5 ); }
		| SCALE '(' image ',' real ')'	
			{ $$ = _scaleImage( $5, $3 ); }
		| OFFSET '(' INT ',' INT ',' image ')'
			{ $$ = $7; printf( "offset( %d, %d, %x )\n", $3, $5, $7 ); }
		| TOFIT '(' image ')'
			{ $$ = _zoomImageToFit( $3 ); }
		| ZOOM '(' image ',' real ',' real ')'
			{ $$ = _zoomImage( $3, $5, $7 ); }
		| INVERT '(' image ')'
			{ $$ = _invertImage( $3 ); }
		| NEG '(' image ')'
			{ $$ = _negImage( $3 ); }
		| ROBERTS '(' image ')'
			{ $$ = _robertsImage( $3, DEFAULT_VALUE ); }
		| ROBERTS '(' image ',' real ')'
			{ $$ = _robertsImage( $3, $5 ); }
		| SHARPEN '(' image ')'
			{ $$ = _sharpenImage( $3, DEFAULT_VALUE, DEFAULT_VALUE );}
		| SHARPEN '(' image ',' real ')'
			{ $$ = _sharpenImage( $3, $5, DEFAULT_VALUE ); }
		| SHARPEN '(' image ',' real ',' real ')'
			{ $$ = _sharpenImage( $3, $5, $7 ); }
		| THRESH '(' image ',' real ')'
			{ $$ = _threshImage( $3, $5  ); }
		;

weight:		  image 
			{ $$ = _imageWeight( $1 ); }
		| CONST '(' real ')'
			{ $$ = _constWeight( $3 ); }
		| CONTOUR '(' weight ',' weight ',' real ')'
			{ $$ = _contourWeight( $3, $5, $7 ); }
		| GRAD '(' weight ',' weight ')'
			{ $$ = _gradWeight( $3, $5 ); }
		| LASTDIR '(' weight ',' weight ')'
			{ $$ = _lastdirWeight( $3, $5 ); }
		;

real:		  REAL				{ $$ = $1; }
		| INT				{ $$ = (double)$1; }
%%




/*
 *  simple error function
 */
void
yyerror( s )
char	*s;
{
	extern	char	yytext[];
	extern	int	yylineno;
	char	in[256];

	gets( in );
	fprintf( stderr, "ERROR: %s on line %d at %s%s\n", 
			s, yylineno, yytext, in );
}


yywrap() { return(1); }





