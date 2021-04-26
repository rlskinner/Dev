size	256 256
colormap	"data/rainbow.map"
write 	"/tmp/eat.bw"
/* seed	line	0.0 0.0 0.0 0.0 const( 10000 ) */
/* action	edge	const( .01 ) */
seed	random	20	const( 1 ) 
/*
action  ring	5    const( .1 )
action  corner    grad( "data/y-.bw", "data/x.bw" )
*/
action  edge    grad( "data/y-.bw", "data/x.bw" )
