
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif
	{
	int	ival;		/* integer value */
	double	rval;		/* floating point value */
	char	str[256];	/* character string */
	void	*vstar;		/* pointer */
} YYSTYPE;
extern YYSTYPE yylval;
# define INT 257
# define REAL 258
# define STR 259
# define COLORMAP 260
# define SIZE 261
# define WRITE 262
# define EXIT 263
# define SGI 264
# define FIT 265
# define EDGE 266
# define DIR 267
# define DISK 268
# define LINE 269
# define RANDOM 270
# define NEIGHBOR4 271
# define NEIGHBOR8 272
# define CORNER 273
# define RING 274
# define SCATTERRING 275
# define CONE 276
# define CROSS 277
# define AT 278
# define CONST 279
# define IMAGE 280
# define TOFIT 281
# define BLUR 282
# define COMPASS 283
# define INVERT 284
# define NEG 285
# define OFFSET 286
# define ROBERTS 287
# define SCALE 288
# define SHARPEN 289
# define THRESH 290
# define ZOOM 291
# define CONTOUR 292
# define GRAD 293
# define LASTDIR 294
# define SEED 295
# define ACTION 296
# define PERCENT 297
# define ANY 298
# define EMPTY 299
# define WAITING 300
# define SET 301
# define ADD 302
# define MULTIPLY 303
# define ALL 304
# define MIN 305
# define MAX 306
# define POSITIVE 307
# define NEGATIVE 308
