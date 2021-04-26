size	256 256
colormap	"data/rainbow.map"
write 	"/tmp/eat.bw"
seed	random	3	10000
action  dir    grad( tofit( "data/y-.bw" ), tofit( "data/x.bw" ) ) .01
