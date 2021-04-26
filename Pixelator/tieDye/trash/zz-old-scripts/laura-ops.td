size	150 150 at 0 700
colormap	"data/rainbow.map"
seed	image 	tofit(
		sharpen(  
		thresh( 
		    invert( "images/laura-zapf.rgb" ), 
		    128 ) ,
		1.0, 1.5 )
		)
action  corner  1

