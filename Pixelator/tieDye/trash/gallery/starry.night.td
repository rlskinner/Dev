size	256 204
write	"gallery/starry-out.bw"
colormap        "data/rainbow.map"
/*
seed	image	thresh( "data/starry.bw", 200 )
*/
seed	line 0.4 0.6 0.6 0.6	const( 1 )
seed	line 0.9 0.8 0.95 0.8	const( 200 )
action	nbor8	contour( "data/starry.bw", "data/starry.bw", 0.5 )
