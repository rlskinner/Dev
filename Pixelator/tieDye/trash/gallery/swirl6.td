size	1024 1024
colormap	"data/rainbow.map"
write 	"gallery/swirl6.bw"
seed	line 0.5 0.0 0.5 1.0	const( .00010000 )  
seed	line 0.0 0.5 1.0 0.5 	const( .00010000 )  
action  corner    grad( tofit( "data/y-.bw" ), tofit( "data/x.bw" ) )
