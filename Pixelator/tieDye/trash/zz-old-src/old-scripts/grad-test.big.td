size	160 160
seed	line	0 .5	1.0	.5	const( 10000 )
/* action	edge	const( .01 ) */
/* seed	random	100	const( 1 ) */
/* */
action	edge	grad(
		    compass( 
			tofit( "images/sine.bw" ),
			90.0 
		    ),
		    compass( 
			tofit( "images/sine.bw" ),
			0.0 
		    )
		)
/**/
