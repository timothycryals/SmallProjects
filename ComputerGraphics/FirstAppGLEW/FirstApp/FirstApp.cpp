/* sierpinski gasket using vertex buffer objects */

#include "Angel.h"

enum ShaderType { uniform, vertex };

const int NumPoints = 126;
ShaderType shaderType = vertex;
GLuint program = 0;
GLuint uniformShader = 0;
GLuint vertexShader = 0;

GLuint loc = 0;
GLuint loc2 = 0;

GLuint uColorLoc = 0;

//----------------------------------------------------------------------------
/* This function initializes an array of 3d vectors 
   and sends it to the graphics card along with shaders
   properly connected to them.
*/

void
init(void)
{
	vec3 tPoints[NumPoints];
	vec3 colors[NumPoints];

	//-----------------------Points for letter T---------------
	tPoints[0] = vec3(-1, 0.6, 0);
	tPoints[1] = vec3(-0.8, 0.6, 0);
	tPoints[2] = vec3(-1, 0.55, 0);

	tPoints[3] = vec3(-0.8, 0.6, 0);
	tPoints[4] = vec3(-0.8, 0.55, 0);
	tPoints[5] = vec3(-1, 0.55, 0);

	tPoints[6] = vec3(-0.92, 0.55, 0);
	tPoints[7] = vec3(-0.88, 0.55, 0);
	tPoints[8] = vec3(-0.92, 0.2, 0);

	tPoints[9] = vec3(-0.88, 0.55, 0);
	tPoints[10] = vec3(-0.88, 0.2, 0);
	tPoints[11] = vec3(-0.92, 0.2, 0);
	//---------------------------------------------------------------

	//---------------------Points for letter I-----------------------
	tPoints[12] = vec3(-0.75, 0.6, 0);
	tPoints[13] = vec3(-0.6, 0.6, 0);
	tPoints[14] = vec3(-0.75, 0.55, 0);

	tPoints[15] = vec3(-0.6, 0.55, 0);
	tPoints[16] = vec3(-0.75, 0.55, 0);
	tPoints[17] = vec3(-0.6, 0.6, 0);

	tPoints[18] = vec3(-0.67, 0.55, 0);
	tPoints[19] = vec3(-0.69, 0.55, 0);
	tPoints[20] = vec3(-0.67, 0.25, 0);

	tPoints[21] = vec3(-0.69, 0.25, 0);
	tPoints[22] = vec3(-0.67, 0.25, 0);
	tPoints[23] = vec3(-0.69, 0.55, 0);

	tPoints[24] = vec3(-0.75, 0.25, 0);
	tPoints[25] = vec3(-0.75, 0.2, 0);
	tPoints[26] = vec3(-0.6, 0.25, 0);

	tPoints[27] = vec3(-0.75, 0.2, 0);
	tPoints[28] = vec3(-0.6, 0.2, 0);
	tPoints[29] = vec3(-0.6, 0.25, 0);
	//--------------------------------------------------------------

	//--------------------------Points for letter M--------------------

	tPoints[30] = vec3(-0.55, 0.2, 0);
	tPoints[31] = vec3(-0.55, 0.6, 0);
	tPoints[32] = vec3(-0.52, 0.2, 0);

	tPoints[33] = vec3(-0.52, 0.2, 0);
	tPoints[34] = vec3(-0.55, 0.6, 0);
	tPoints[35] = vec3(-0.52, 0.6, 0);

	tPoints[36] = vec3(-0.52, 0.52, 0);
	tPoints[37] = vec3(-0.46, 0.2, 0);
	tPoints[38] = vec3(-0.48, 0.2, 0);

	tPoints[39] = vec3(-0.52, 0.6, 0);
	tPoints[40] = vec3(-0.52, 0.52, 0);
	tPoints[41] = vec3(-0.46, 0.2, 0);

	tPoints[42] = vec3(-0.46, 0.2, 0);
	tPoints[43] = vec3(-0.48, 0.2, 0);
	tPoints[44] = vec3(-0.42, 0.52, 0);

	tPoints[45] = vec3(-0.42, 0.6, 0);
	tPoints[46] = vec3(-0.48, 0.2, 0);
	tPoints[47] = vec3(-0.42, 0.52, 0);

	tPoints[48] = vec3(-0.42, 0.2, 0);
	tPoints[49] = vec3(-0.39, 0.6, 0);
	tPoints[50] = vec3(-0.39, 0.2, 0);

	tPoints[51] = vec3(-0.42, 0.6, 0);
	tPoints[52] = vec3(-0.39, 0.6, 0);
	tPoints[53] = vec3(-0.42, 0.2, 0);
	//-----------------------------------------------------------------

	//--------------------------------Points for letter O------------------------

	tPoints[54] = vec3(-0.35, 0.6, 0);
	tPoints[55] = vec3(-0.35, 0.55, 0);
	tPoints[56] = vec3(-0.20, 0.6, 0);

	tPoints[57] = vec3(-0.20, 0.6, 0);
	tPoints[58] = vec3(-0.20, 0.55, 0);
	tPoints[59] = vec3(-0.35, 0.55, 0);

	tPoints[60] = vec3(-0.35, 0.55, 0);
	tPoints[61] = vec3(-0.32, 0.55, 0);
	tPoints[62] = vec3(-0.35, 0.25, 0);

	tPoints[63] = vec3(-0.32, 0.25, 0);
	tPoints[64] = vec3(-0.32, 0.55, 0);
	tPoints[65] = vec3(-0.35, 0.25, 0);

	tPoints[66] = vec3(-0.35, 0.25, 0);
	tPoints[67] = vec3(-0.35, 0.2, 0);
	tPoints[68] = vec3(-0.20, 0.25, 0);

	tPoints[69] = vec3(-0.20, 0.25, 0);
	tPoints[70] = vec3(-0.20, 0.2, 0);
	tPoints[71] = vec3(-0.35, 0.2, 0);

	tPoints[72] = vec3(-0.23, 0.55, 0);
	tPoints[73] = vec3(-0.2, 0.55, 0);
	tPoints[74] = vec3(-0.23, 0.25, 0);

	tPoints[75] = vec3(-0.2, 0.25, 0);
	tPoints[76] = vec3(-0.2, 0.55, 0);
	tPoints[77] = vec3(-0.23, 0.25, 0);

	//----------------------------------------Points for letter T--------------------
	tPoints[78] = vec3(-0.15, 0.6, 0);
	tPoints[79] = vec3(0.05, 0.6, 0);
	tPoints[80] = vec3(-0.15, 0.55, 0);

	tPoints[81] = vec3(-0.15, 0.55, 0);
	tPoints[82] = vec3(0.05, 0.55, 0);
	tPoints[83] = vec3(0.05, 0.6, 0);

	tPoints[84] = vec3(-0.07, 0.55, 0);
	tPoints[85] = vec3(-0.03, 0.55, 0);
	tPoints[86] = vec3(-0.07, 0.2, 0);

	tPoints[87] = vec3(-0.03, 0.55, 0);
	tPoints[88] = vec3(-0.03, 0.2, 0);
	tPoints[89] = vec3(-0.07, 0.2, 0);

	//-------------------------------------------------------------------------------------

	//-----------------------------------------Points for letter H-------------------------

	tPoints[90] = vec3(0.1, 0.2, 0);
	tPoints[91] = vec3(0.1, 0.6, 0);
	tPoints[92] = vec3(0.13, 0.2, 0);

	tPoints[93] = vec3(0.13, 0.2, 0);
	tPoints[94] = vec3(0.1, 0.6, 0);
	tPoints[95] = vec3(0.13, 0.6, 0);

	tPoints[96] = vec3(0.13, 0.42, 0);
	tPoints[97] = vec3(0.22, 0.42, 0);
	tPoints[98] = vec3(0.13, 0.38, 0);

	tPoints[99] = vec3(0.13, 0.38, 0);
	tPoints[100] = vec3(0.22, 0.42, 0);
	tPoints[101] = vec3(0.22, 0.38, 0);

	tPoints[102] = vec3(0.22, 0.2, 0);
	tPoints[103] = vec3(0.22, 0.6, 0);
	tPoints[104] = vec3(0.25, 0.2, 0);

	tPoints[105] = vec3(0.25, 0.2, 0);
	tPoints[106] = vec3(0.22, 0.6, 0);
	tPoints[107] = vec3(0.25, 0.6, 0);

	//----------------------------------------------------------------------------------------

	//---------------------------------Points for letter Y------------------------------------

	tPoints[108] = vec3(0.3, 0.52, 0);
	tPoints[109] = vec3(0.36, 0.35, 0);
	tPoints[110] = vec3(0.4, 0.35, 0);

	tPoints[111] = vec3(0.40, 0.35, 0);
	tPoints[112] = vec3(0.3, 0.6, 0);
	tPoints[113] = vec3(0.3, 0.52, 0);

	tPoints[114] = vec3(0.36, 0.35, 0);
	tPoints[115] = vec3(0.4, 0.35, 0);
	tPoints[116] = vec3(0.46, 0.52, 0);

	tPoints[117] = vec3(0.46, 0.6, 0);
	tPoints[118] = vec3(0.36, 0.35, 0);
	tPoints[119] = vec3(0.46, 0.52, 0);

	tPoints[120] = vec3(0.36, 0.35, 0);
	tPoints[121] = vec3(0.36, 0.2, 0);
	tPoints[122] = vec3(0.4, 0.35, 0);

	tPoints[123] = vec3(0.4, 0.35, 0);
	tPoints[124] = vec3(0.4, 0.2, 0);
	tPoints[125] = vec3(0.36, 0.2, 0);


	//Create some colors
	vec3 base_colors[8] = {
		vec3(0.0, 0.0, 0.0),
		vec3(0.0, 0.0, 1.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 1.0, 1.0),
		vec3(1.0, 0.0, 0.0),
		vec3(1.0, 0.0, 1.0),
		vec3(1.0, 1.0, 0.0),
		vec3(1.0, 1.0, 1.0)
	};


	//Set vertex colors
	for (int c = 0; c < 12; c++) {
		colors[c] = base_colors[0];
	}

	for (int v = 12; v < 30; v++) {
		colors[v] = base_colors[1];
	}

	for (int b = 30; b < 54; b++) {
		colors[b] = base_colors[2];
	}

	for (int n = 54; n < 78; n++) {
		colors[n] = base_colors[3];
	}

	for (int m = 78; m < 90; m++) {
		colors[m] = base_colors[4];
	}

	for (int m = 78; m < 90; m++) {
		colors[m] = base_colors[4];
	}

	for (int x = 90; x < 108; x++) {
		colors[x] = base_colors[5];
	}

	for (int z = 108; z < 126; z++) {
		colors[z] = base_colors[6];
	}




    // Specifiy the vertices for a triangle
	//vec3 vertices[] = {
	//	vec3( -1.0, -1.0, 0.0 ),
	//	vec3(  0.0,  1.0, 0.0 ),
	//	vec3(  1.0, -1.0, 0.0 )
	//};

 //   // Select an arbitrary initial point inside of the triangle
 //   points[0] = vec3( 0.0, 0.0, 0.0 );

 //   // compute and store NumPoints - 1 new points
 //   for ( int i = 1; i < NumPoints; ++i ) {
 //       int j = rand() % 3;   // pick a vertex from the triangle at random

 //       // Compute the point halfway between the selected vertex
 //       //   and the previous point
 //       points[i] = ( points[i - 1] + vertices[j] ) / 2.0;
 //   }

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(tPoints) + sizeof(colors), NULL, GL_STATIC_DRAW );

	//Fill the array buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tPoints), tPoints);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(tPoints), sizeof(colors), colors);

    // Load shaders and use the resulting shader program
	vertexShader = InitShader("vertexColor.vert", "vertexColor.frag");
	uniformShader = InitShader("uniformColor.vert", "uniformColor.frag");

	switch (shaderType) 
	{
		case vertex:
			program = vertexShader;
			break;
		case uniform:
			program = uniformShader;
			break;
	}

	// make these shaders the current shaders
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	loc2 = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(tPoints)));

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
	if (shaderType == vertex) {
		glClear(GL_COLOR_BUFFER_BIT);				// clear the window
		glDrawArrays(GL_TRIANGLES, 0, 12);    // draw the points for the letter T
		glDrawArrays(GL_TRIANGLES, 12, 18);
		glDrawArrays(GL_TRIANGLES, 30, 24);
		glDrawArrays(GL_TRIANGLES, 54, 24);
		glDrawArrays(GL_TRIANGLES, 78, 12);
		glDrawArrays(GL_TRIANGLES, 90, 18);
		glDrawArrays(GL_TRIANGLES, 108, 60);
		glFlush();									// flush the buffer

	}
	else {
		vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);				// clear the window
		glUniform4fv(uColorLoc, 1, color);
		glDrawArrays(GL_TRIANGLES, 0, 12);    // draw the points for the letter T
		color = vec4(1.0, 1.0, 0.0, 1.0);
		glUniform4fv(uColorLoc, 1, color);
		glDrawArrays(GL_TRIANGLES, 12, 18);
		color = vec4(1.0, 0.0, 0.0, 1.0);
		glUniform4fv(uColorLoc, 1, color);
		glDrawArrays(GL_TRIANGLES, 30, 24);
		color = vec4(0.5, 0.0, 1.0, 1.0);
		glUniform4fv(uColorLoc, 1, color);
		glDrawArrays(GL_TRIANGLES, 54, 24);
		color = vec4(0.0, 0.0, 1.0, 1.0);
		glUniform4fv(uColorLoc, 1, color);
		glDrawArrays(GL_TRIANGLES, 78, 12);
		color = vec4(0.0, 1.0, 0.0, 1.0);
		glUniform4fv(uColorLoc, 1, color);
		glDrawArrays(GL_TRIANGLES, 90, 18);
		color = vec4(0.0, 1.0, 1.0, 1.0);
		glUniform4fv(uColorLoc, 1, color);
		glDrawArrays(GL_TRIANGLES, 108, 60);
		glFlush();									// flush the buffer
	}
	
	////GLuint uColorLoc = glGetUniformLocation(program, "uColor");
	////vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
 //   glClear( GL_COLOR_BUFFER_BIT );				// clear the window
	////glUniform4fv(uColorLoc, 1, color);
 //   glDrawArrays( GL_TRIANGLES, 0, 12 );    // draw the points for the letter T
	////color = vec4(1.0, 1.0, 0.0, 1.0);
	////glUniform4fv(uColorLoc, 1, color);
	//glDrawArrays(GL_TRIANGLES, 12, 18);
	//glDrawArrays(GL_TRIANGLES, 30, 24);
	//glDrawArrays(GL_TRIANGLES, 54, 24);
	//glDrawArrays(GL_TRIANGLES, 78, 12);
	//glDrawArrays(GL_TRIANGLES, 90, 18);
	//glDrawArrays(GL_TRIANGLES, 108, 60);
 //   glFlush();									// flush the buffer
}

//----------------------------------------------------------------------------
/* This function handles the keyboard and it is called by GLUT once it is 
   declared as the keyboard function. The application should not call it
   directly.
*/

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:					// escape key
        exit( EXIT_SUCCESS );	// terminates the program
        break;

	case 'w': case 'W' :
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	case 'f' : case 'F':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case 'v' : case 'V':
		shaderType = vertex;
		program = vertexShader;
		glUseProgram(vertexShader);
		break;
	case 'u' : case 'U':
		shaderType = uniform;
		program = uniformShader;
		glUseProgram(uniformShader);
		uColorLoc = glGetUniformLocation(uniformShader, "uColor");
		break;
    }

	glutPostRedisplay();
}

//----------------------------------------------------------------------------
/* This is the main function that calls all the functions to initialize
   and setup the OpenGL environment through GLUT and GLEW.
*/

int
main( int argc, char **argv )
{
	// Initialize GLUT
    glutInit( &argc, argv );
	// Initialize the display mode to a buffer with Red, Green, Blue and Alpha channels
    glutInitDisplayMode( GLUT_RGBA );
	// Set the window size
    glutInitWindowSize( 1000, 512 );
	// Here you set the OpenGL version
    glutInitContextVersion( 3, 2 );
	//Use only one of the next two lines
    //glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );
    glutCreateWindow( "Simple GLSL example" );

    // Uncomment if you are using GLEW
	glewInit(); 

    // initialize the array and send it to the graphics card
	init();

    // provide the function that handles the display
	glutDisplayFunc( display );
	// provide the functions that handles the keyboard
    glutKeyboardFunc( keyboard );

    // Wait for input from the user (the only meaningful input is the key escape)
	glutMainLoop();
    return 0;
}