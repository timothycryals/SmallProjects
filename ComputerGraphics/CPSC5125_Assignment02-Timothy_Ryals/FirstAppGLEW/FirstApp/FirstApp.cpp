/* sierpinski gasket using vertex buffer objects */

#include "Angel.h"

float getEuclideanDistance(vec2 a, vec2 b);

enum DrawState {Moving, Waiting, NoShape};
enum TranslateDirection { Left, Right, Up, Down };

const int NumPoints = 100;
GLuint currentShader = 0;
GLuint red = 0;
GLuint green = 0;
GLuint blue = 0;
GLfloat rotateInDegrees = 0.0;
vec4 points[NumPoints];
vec3 colors[NumPoints];
mat4 transformation;
mat4 translation;

const int timesToDraw = 5000;

int numBlades;
float degreesToRotate;
enum DrawState currentDrawState = NoShape;
enum TranslateDirection yMovement;
enum TranslateDirection xMovement;

vec2 targetPosition = vec2(0.0, 0.0);
vec2 spawnPosition = vec2(0.0, 0.0);
vec2 destinationPosition = vec2(0.0, 0.0);

vec2 destinationVector = vec2(0.0, 0.0);
GLfloat xIncrement = 0;
GLfloat yIncrement = 0;

//----------------------------------------------------------------------------
/* This function initializes an array of 3d vectors 
   and sends it to the graphics card along with shaders
   properly connected to them.
*/

void
init( void )
{

    // Specifiy the vertices for a single blade of a star
	vec4 vertices[] = {
		vec4(  0.0, 0.0, 0.0, 1.0 ),
		vec4( -0.05, 0.05, 0.0, 1.0 ),
		vec4(  0.05, 0.05, 0.0, 1.0 ),
		vec4(  0.0, 0.15, 0.0, 1.0 ),
		vec4(  0.05, 0.05, 0.0, 1.0),
		vec4(  -0.05, 0.05, 0.0, 1.0)
	};
	// Create some colors
	vec3 base_colors[] = {
		vec3(0.0, 0.0, 0.0),
		vec3(0.0, 0.0, 1.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 1.0, 1.0),
		vec3(1.0, 0.0, 0.0),
		vec3(1.0, 0.0, 1.0),
		vec3(1.0, 1.0, 0.0),
		vec3(1.0, 1.0, 1.0)
	};

    // Select an arbitrary initial point inside of the triangle
    points[0] = vertices[1];
	points[1] = vertices[0];
	points[2] = vertices[2];
	points[3] = vertices[3];
	points[4] = vertices[4];
	points[5] = vertices[5];

	/*mat4 translation = Translate(0.0, -0.5, 0.0);
	mat4 rotationAboutZ = RotateZ(30.0);
	mat4 scaling = Scale(0.1, 1.0, 1.0);
	mat4 transformation =  rotationAboutZ * translation * scaling;
	points[4] = transformation *vertices[1];
	points[5] = transformation * vertices[0];
	points[6] = transformation * vertices[2];
	points[7] = transformation * vertices[3];*/

	// Set the vertex colors
	colors[0] = base_colors[6];
	colors[1] = base_colors[6];
	colors[2] = base_colors[6];
	colors[3] = base_colors[6];
	colors[4] = base_colors[5];
	colors[5] = base_colors[2];
	colors[6] = base_colors[4];
	colors[7] = base_colors[5];


    // compute and store NumPoints - 1 new points
	/*
    for ( int i = 1; i < NumPoints; ++i ) {
        int j = rand() % 3;   // pick a vertex from the triangle at random

        // Compute the point halfway between the selected vertex
        //   and the previous point
        points[i] = ( points[i - 1] + vertices[j] ) / 2.0;
    }
	*/

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    //glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
	// Setup the Array Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);

	// Fill the Array Buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    // Load shaders and use the resulting shader program
	red = InitShader("uniformColor.vert", "uniformColor.frag");
	green = InitShader("green.vert", "green.frag");
	blue = InitShader("blue.vert", "blue.frag");
	currentShader = red;
	// make these shaders the current shaders
    glUseProgram( currentShader );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation(currentShader, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc2 = glGetAttribLocation(currentShader, "vColor");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

	glClearColor( 0.5, 0.5, 0.5, 1.0 ); // gray background
}

//----------------------------------------------------------------------------
/* This function handles the display and it is automatically called by GLUT
   once it is declared as the display function. The application should not
   call it directly.
*/

void
display( void )
{
	mat4 rotateBlades;
	mat4 translateBlades;
	mat4 newTransformation;
	GLuint uColorLoc = glGetUniformLocation(currentShader, "uColor");
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
	mat4 identity = mat4(1.0);
	glClear(GL_COLOR_BUFFER_BIT);	// clear the window
	glUseProgram(currentShader);
	if (currentDrawState == NoShape) {
		glFlush();
		return;
	}
	else {
		for (int i = 0; i < numBlades; ++i) {
			if (i != 0) {
				rotateBlades = RotateZ(degreesToRotate * i);
				if (currentDrawState == Waiting) {
					translateBlades = Translate(spawnPosition.x, spawnPosition.y, 0.0);
				}
				else {
					translateBlades = translation;
				}
				newTransformation = translateBlades * rotateBlades * transformation;
				glUniform4fv(uColorLoc, 1, color);
				glUniformMatrix4fv(glGetUniformLocation(currentShader, "modelView"), 1, true, newTransformation);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
			else {
				if (currentDrawState == Waiting) {
					translateBlades = Translate(spawnPosition.x, spawnPosition.y, 0.0);
				}
				else {
					translateBlades = translation;
				}
				newTransformation = translateBlades * transformation;
				
				//newTransformation = translateBlades * transformation;
				glUniform4fv(uColorLoc, 1, color);
				glUniformMatrix4fv(glGetUniformLocation(currentShader, "modelView"), 1, true, newTransformation);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
	}

	
	
	//mat4 identity = mat4(1.0);
 //   glClear( GL_COLOR_BUFFER_BIT );	// clear the window
	//glUseProgram(currentShader);
	////glUseProgram(red);
	//glUniform4fv(uColorLoc, 1, color);
	//glUniformMatrix4fv(glGetUniformLocation(currentShader, "modelView"), 1, true, identity);
 //   glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );    // draw the points
	//glUseProgram(blue);
	color = vec4(1.0, 1.0, 0.0, 1.0);
	
	
    glFlush();									// flush the buffer
}

float getEuclideanDistance(vec2 a, vec2 b) {

	float distance = sqrtf((pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
	return distance;
}

void
idle()
{
	mat4 rotationAboutZ;
	switch (currentDrawState) {

	case NoShape:
		return;

	case Waiting:
		rotateInDegrees += 0.1;
		rotationAboutZ = RotateZ(rotateInDegrees);
		transformation = rotationAboutZ;
		break;

	case Moving:
		destinationVector.x += xIncrement;
		destinationVector.y += yIncrement;
		rotateInDegrees += 0.1;
		translation = Translate(spawnPosition.x + destinationVector.x, spawnPosition.y + destinationVector.y, 0.0);
		rotationAboutZ = RotateZ(rotateInDegrees);
		transformation = rotationAboutZ;
		break;
	}


	float distance = getEuclideanDistance(spawnPosition + destinationVector, destinationPosition);
	if ( distance < 0.01f){
		printf("Shape has reached its destination");
		currentDrawState = NoShape;
		xIncrement = 0;
		yIncrement = 0;
		rotateInDegrees = 0.0;
		destinationVector, destinationPosition, spawnPosition, targetPosition = vec2(0.0, 0.0);
		numBlades = 0;
		degreesToRotate = 0.0;
	}

	
	//points[4] = transformation * points[0];
	//points[5] = transformation * points[1];
	//points[6] = transformation * points[2];
	//points[7] = transformation * points[3];
	// Send the points to the GPU
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glutPostRedisplay();
}

//----------------------------------------------------------------------------
/* This function handles the keyboard and it is called by GLUT once it is 
   declared as the keyboard function. The application should not call it
   directly.
*/

void
keyboard( unsigned char key, int x, int y )
{
	switch (key) {
	case 033:					// escape key
		exit(EXIT_SUCCESS);	// terminates the program
		break;
	case 'r':
	case 'R':
		currentShader = red;
		break;
	case 'g':
	case 'G':
		currentShader = green;
		break;
	case 'b':
	case 'B':
		currentShader = blue;
		break;

	case '2':
		if (currentDrawState == NoShape) {
			numBlades = 2;
			degreesToRotate = 360 / numBlades;
			currentDrawState = Waiting;
			spawnPosition = targetPosition;
		}
		break;

	case '3':
		if (currentDrawState == NoShape) {
			numBlades = 3;
			degreesToRotate = 360 / numBlades;
			currentDrawState = Waiting;
			spawnPosition = targetPosition;
		}
		break;

	case '4':
		if (currentDrawState == NoShape) {
			numBlades = 4;
			degreesToRotate = 360 / numBlades;
			currentDrawState = Waiting;
			spawnPosition = targetPosition;
		}
		break;

	case '5':
		if (currentDrawState == NoShape) {
			numBlades = 5;
			degreesToRotate = 360 / numBlades;
			currentDrawState = Waiting;
			spawnPosition = targetPosition;
		}
		break;

	} 
	glutPostRedisplay();
}



void mouse(int button, int state, int x, int y) {
	if (currentDrawState == Waiting) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			float xCoord = glutGet(GLUT_WINDOW_WIDTH) / 2;
			float yCoord = glutGet(GLUT_WINDOW_HEIGHT) / 2;
			//printf("%6.4f , %6.4f", x / xCoord, y / yCoord);
			destinationPosition.x = (float)((x / xCoord) - 1);
			destinationPosition.y = (float)-((y / yCoord) - 1);

			//angleToMove = angleFromVectors(spawnPosition, destinationPosition);

			if (spawnPosition.x < destinationPosition.x) {
				xMovement = Right;
				destinationVector.x = destinationPosition.x - spawnPosition.x;
			}
			else {
				xMovement = Left;
				destinationVector.x = spawnPosition.x - destinationPosition.x;
			}

			if (destinationVector.x < 0) {
				destinationVector.x = -destinationVector.x;
			}

			if (spawnPosition.y < destinationPosition.y) {
				yMovement = Up;
				destinationVector.y = destinationPosition.y - spawnPosition.y;
			}
			else {
				yMovement = Down;
				destinationVector.y = spawnPosition.y - destinationPosition.y;
			}

			if (destinationVector.y < 0) {
				destinationVector.y = -destinationVector.y;
			}

			
			switch (xMovement) {

			case Left:
				destinationVector.x = -(destinationVector.x / timesToDraw);
				break;

			case Right:
				destinationVector.x = (destinationVector.x / timesToDraw);
				break;
			}

			switch (yMovement) {

			case Up:
				destinationVector.y = (destinationVector.y / timesToDraw);
				break;

			case Down:
				destinationVector.y = -(destinationVector.y / timesToDraw);
				break;
			}

			xIncrement = destinationVector.x;
			yIncrement = destinationVector.y;

			currentDrawState = Moving;
		}
	}
}

void simpleMenu(GLint choice)
{
	switch (choice)
	{
		case 0:
			currentShader = red;
			break;
		case 1:
			currentShader = green;
			break;
		case 2:
			currentShader = blue;
			break;
		default:
			break;
	}
	glutPostRedisplay();

}

void GetMousePosition(int x, int y) {

	float xCoord = glutGet(GLUT_WINDOW_WIDTH) / 2;
	float yCoord = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	//printf("%6.4f , %6.4f", x / xCoord, y / yCoord);
	targetPosition.x = (float) ((x / xCoord) - 1);
	targetPosition.y = (float) -((y / yCoord) - 1);
}

//----------------------------------------------------------------------------
/* This is the main function that calls all the functions to initialize
   and setup the OpenGL environment through GLUT and GLEW.
*/

int
main(int argc, char **argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	// Initialize the display mode to a buffer with Red, Green, Blue and Alpha channels
	glutInitDisplayMode(GLUT_RGBA);
	// Set the window size
	glutInitWindowSize(512, 512);
	// Here you set the OpenGL version
	glutInitContextVersion(4, 4);
	//Use only one of the next two lines
	//glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutCreateWindow("Simple GLSL example");

	// Uncomment if you are using GLEW
	glewInit();

	// initialize the array and send it to the graphics card
	init();

	// create a simple menu
	GLint menu = glutCreateMenu(simpleMenu);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//glutAddSubMenu("Colors", 1);

	// provide the function that handles the display
	glutDisplayFunc(display);
	// provide the functions that handles the keyboard
	glutKeyboardFunc(keyboard);

	glutMouseFunc(mouse);

	glutPassiveMotionFunc(GetMousePosition);
	// provide the function that handles the idle state
	glutIdleFunc(idle);

	// Wait for input from the user (the only meaningful input is the key escape)
	glutMainLoop();
	return 0;
}