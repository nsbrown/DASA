To compile dasademo.c on UNIX: 
	gcc -o dasademo dasademo.c

To compile dasaGraphicsServer.c (v.2) on Mac: 
	gcc -o dasaGraphicsServer2  -framework GLUT -framework OpenGL  dasadraw.c dasaGraphicsServer.c

To run dasaGraphicsServer (v.2):
	./dasaGraphicsServer