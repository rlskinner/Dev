size	512 512
colormap	"data/rainbow.map"
write 	"/tmp/eat.bw"
seed	line	0.51 0.5 0.51 0.5	const( 10000 )  
action(positive)  cone	3    grad( tofit( "data/y-.bw" ), tofit( "data/x.bw" ) )
