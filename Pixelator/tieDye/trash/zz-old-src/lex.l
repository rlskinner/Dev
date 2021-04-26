%{

#include	"y.tab.h"
%}

D				[0-9]
E                               [DEde][-+]?{D}+
PM				[-+]?

%%
"/*"				{ comment(); /* C-Style */ }

[ \n\t\f]+			; /* ignore white space */

{PM}{D}+			{
				sscanf( yytext, "%d", &yylval.ival );
				return(INT); /* found an INT */
				}

{PM}{D}+\.{D}*({E})?	|
{PM}{D}*\.{D}+({E})?	|
{D}+{E}				{ /* forms of real numbers:
				   *  	XX.[XX][e]
				   *   [XX].XX[e]
				   *	XXeXX
				   */
				sscanf( yytext, "%lf", &yylval.rval );
				return(REAL); /* found a real # */
				}

size				{ return( SIZE ); }

colormap			{ return( COLORMAP ); }
write				{ return( WRITE ); }
exit				{ return( EXIT ); }
sgi				{ return( SGI ); }
fit				{ return( FIT ); }

seed				{ return( SEED ); }
random				{ return( RANDOM ); }

action				{ return( ACTION ); }
nbor4				{ return( NEIGHBOR4 ); }
nbor8				{ return( NEIGHBOR8 ); }
edge				{ return( EDGE ); }
dir				{ return( DIR ); }
line				{ return( LINE ); }
corner				{ return( CORNER ); }
ring				{ return( RING ); }
scatterRing			{ return( SCATTERRING ); }
cone				{ return( CONE ); }
cross				{ return( CROSS ); }
at				{ return( AT ); }
image				{ return( IMAGE ); }
scale				{ return( SCALE ); }
tofit				{ return( TOFIT ); }
const				{ return( CONST ); }

grad				{ return( GRAD ); }

blur				{ return( BLUR ); }
compass				{ return( COMPASS ); }
invert				{ return( INVERT ); }
neg				{ return( NEG ); }
offset				{ return( OFFSET ); }
scale				{ return( SCALE ); }
sharpen				{ return( SHARPEN ); }
thresh				{ return( THRESH ); }
zoom				{ return( ZOOM ); }

lastdir				{ return( LASTDIR ); }


'%'				{ return( PERCENT ); }



[\(\)\,\|\{\}\[\]]		{
					/* found ( ) , | { } [ ] */
					return(yytext[0]);	
				}

\"(\\.|[^\\"])*\"		{ 
					strcpy( yylval.str, &yytext[1] );
					yylval.str[strlen(yylval.str)-1] = 0;
					return( STR ); 
				}

.				{ 
				/*  illegal char */
				yyerror("bad character detected");  
				}
%%

comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0)
		/*putchar(c)*/ ;

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	/*if (c != 0)
		putchar(c1);*/
}
