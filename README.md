# CuttingProblem
Algorithms for the cutting 2d problem

The visualization needs Opengl
https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MinGW.zip

You should follow the instructions of the readme in order to install OpenGL.




The program has the following parameters:

-Instancia nombre_instancia
-t 100 %tiempo en segundos
-Visible (1/0) %si es visible o no
-Seed 1 %semillas
-Rotate 1 %si admite rotación 0 si no

For instance:

-Instancia Instancias\Con11.txt  -Visible 1  -Rotate 0

The instances should have this format:

First line: Number of items
Second line: L W
Each line for item: l w minq maxq value

5 
10	10
3	7	0	2	35
8	2	0	2	40
10	2	0	1	27
5	4	0	3	23
2	9	0	2	43
