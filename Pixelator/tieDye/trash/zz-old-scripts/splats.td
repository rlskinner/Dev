size	256 256
colormap	"data/rainbow.map"
/* seed	line	0.0 0.0 0.0 0.0 const( 10000 ) */
/* action	edge	const( .01 ) */
seed	random	20	const( 1 ) 
/*
action(positive)  ring	5    grad( const( 1 ), const( 1 ) )
*/
action(positive)  edge    grad( const( 1 ), const( 1 ) )
action(positive)	corner	grad( const( 1 ), const( 1 ) )
