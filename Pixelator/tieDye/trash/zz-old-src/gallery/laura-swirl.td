size	256 256
colormap	"data/rainbow.map"
write 	"/tmp/eat.bw"
seed	image 	thresh( invert( "images/laura-zapf.rgb" ), 128 )
action  cone	3    grad( tofit( "data/y-.bw" ), tofit( "data/x.bw" ) )
