size	1024 1024
colormap	"data/rainbow.map"
write 	"gallery/swirl4.bw"
seed	random	5	const( 10000 )  
action(positive)  cone	3    grad( tofit( "data/y-.bw" ), tofit( "data/x.bw" ) )
