size	1024 1024
colormap	"data/rainbow.map"
write 	"gallery/swirl5.bw"
seed	random	3	const( 10000 )  
action  corner    grad( tofit( "data/y-.bw" ), tofit( "data/x.bw" ) )
