size	247   113 
seed	line	0 .5	1.0	.5	const( 10000 )
/* action	edge	const( .01 ) */
/* seed	random	100	const( 1 ) */
/* */
action(positive)	edge	grad(
		    compass( 
			blur(
			    invert( "images/laura-zapf.rgb" ),
			    0.0,
			    5.0
			), 
			90.0 
		    ),
		    compass( 
			blur(
			    invert( "images/laura-zapf.rgb" ),
			    0.0,
			    5.0
			), 
			0.0 
		    )
		)
/**/
