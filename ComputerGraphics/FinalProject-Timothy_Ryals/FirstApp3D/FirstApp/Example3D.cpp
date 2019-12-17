//Author: Timothy Ryals
//Project: Final Project
//Purpose: Draw 3 objects on screen and make materials accesible through a menu
//		   with an option to apply a texture and change the offset.

/* sierpinski gasket using vertex buffer objects */

#include "Angel.h"
#include "SOIL.h"

enum ColorEditMode { AMBIENT, DIFFUSE, SPECULAR, SHININESS};

const int NumPoints = 100;
int limit = 0;
vec4 points[NumPoints];
vec3 normals[NumPoints];
vec2 texCoords[NumPoints];
GLdouble theta = 1.0, speed = 10;
GLuint rate = 33;
GLdouble direction = 1.0;
GLfloat scale = 1.0f, zoom = 1.0f;
GLuint program0, program1 = 0;
GLfloat aspectRatio = 1.0f;
GLint animate = 0;
GLint startSquare, endSquare, startCube, endCube, startTetra, endTetra;
ColorEditMode currentMode = AMBIENT;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;
typedef Angel::vec3 normal3;

point4 light_position( 1.0, 1.0, 1.0, 1.0 );
// Initialize shader lighting parameters
color4 light_ambient( 0.1, 0.1, 0.1, 1.0 );
color4 light_diffuse( 1.0, 1.0, 1.0, 1.0 );
color4 light_specular( 1.0, 1.0, 1.0, 1.0 );

color4 material_ambient( 0.0215, 0.1745, 0.0215, 1.0 );
color4 material_diffuse( 0.07568, 0.61424, 0.07568, 1.0 );
color4 material_specular( 0.633, 0.727811, 0.633, 1.0 );
float  material_shininess = 0.6;

color4 emerald_ambient( 0.0215, 0.1745, 0.0215, 1.0 );
color4 emerald_diffuse( 0.07568, 0.61424, 0.07568, 1.0 );
color4 emerald_specular( 0.633, 0.727811, 0.633, 1.0 );
float  emerald_shininess = 76.8;

color4 ruby_ambient( 0.1745,	0.01175,	0.01175, 1.0 );
color4 ruby_diffuse( 0.61424,	0.04136,	0.04136, 1.0 );
color4 ruby_specular( 0.727811,	0.626959,	0.626959, 1.0 );
float  ruby_shininess = 76.8;

color4 cyan_rubber_ambient( 0.0,	0.05,	0.05, 1.0 );
color4 cyan_rubber_diffuse( 0.4,	0.5,	0.5, 1.0 );
color4 cyan_rubber_specular( 0.04,	0.7,	0.7	, 1.0 );
float  cyan_rubber_shininess = .078125 * 128;

color4 gold_ambient( 0.24725,	0.1995,	0.0745, 1.0 );
color4 gold_diffuse( 0.75164,	0.60648,	0.22648, 1.0 );
color4 gold_specular( 0.628281,	0.555802,	0.366065	, 1.0 );
float  gold_shininess = .4 * 128;

color4 jade_ambient(0.135, 0.2225, 0.1575, 1.0);
color4 jade_diffuse(0.54, 0.89, 0.63, 1.0);
color4 jade_specular(0.316228, 0.316228, 0.316228, 1.0);
float  jade_shininess = .1 * 128;

color4 obsidian_ambient(0.05375, 0.05, 0.06625, 1.0);
color4 obsidian_diffuse(0.18275, 0.17, 0.22525, 1.0);
color4 obsidian_specular(0.332741, 0.328634, 0.346435, 1.0);
float  obsidian_shininess = .3 * 128;

color4 pearl_ambient(0.25, 0.20725, 0.20725, 1.0);
color4 pearl_diffuse(1, 0.829, 0.829, 1.0);
color4 pearl_specular(0.296648, 0.296648, 0.296648, 1.0);
float  pearl_shininess = .088 * 128;

color4 turquoise_ambient(0.1, 0.18725, 0.1745, 1.0);
color4 turquoise_diffuse(0.396, 0.74151, 0.69102, 1.0);
color4 turquoise_specular(0.297254, 0.30829, 0.306678, 1.0);
float  turquoise_shininess = .1 * 128;

color4 brass_ambient(0.329412, 0.223529, 0.027451, 1.0);
color4 brass_diffuse(0.780392, 0.113725, 0.113725, 1.0);
color4 brass_specular(0.992157, 0.941176, 0.807843, 1.0);
float  brass_shininess = .21794872 * 128;

color4 bronze_ambient(0.2125, 0.1275, 0.054, 1.0);
color4 bronze_diffuse(0.714, 0.4284, 0.18144, 1.0);
color4 bronze_specular(0.393548, 0.271906, 0.166721, 1.0);
float  bronze_shininess = .2 * 128;

color4 chrome_ambient(0.25, 0.25, 0.25, 1.0);
color4 chrome_diffuse(0.4, 0.4, 0.4, 1.0);
color4 chrome_specular(0.774597, 0.774597, 0.774597, 1.0);
float  chrome_shininess = .6 * 128;

color4 copper_ambient(0.19125, 0.0735, 0.0225, 1.0);
color4 copper_diffuse(0.7038, 0.27048, 0.0828, 1.0);
color4 copper_specular(0.256777, 0.137622, 0.086014, 1.0);
float  copper_shininess = .1 * 128;

color4 silver_ambient(0.19225, 0.19225, 0.19225, 1.0);
color4 silver_diffuse(0.50754, 0.50754, 0.50754, 1.0);
color4 silver_specular(0.508273, 0.508273, 0.508273, 1.0);
float  silver_shininess = .4 * 128;

color4 black_plastic_ambient(0.0, 0.0, 0.0, 1.0);
color4 black_plastic_diffuse(0.01, 0.01, 0.01, 1.0);
color4 black_plastic_specular(0.5, 0.5, 0.5, 1.0);
float  black_plastic_shininess = .25 * 128;

color4 cyan_plastic_ambient(0.0, 0.1, 0.06, 1.0);
color4 cyan_plastic_diffuse(0.0, 0.50980392, 0.50980392, 1.0);
color4 cyan_plastic_specular(0.50196078, 0.50196078, 0.50196078, 1.0);
float  cyan_plastic_shininess = .25 * 128;

color4 green_plastic_ambient(0.0, 0.0, 0.0, 1.0);
color4 green_plastic_diffuse(0.1, 0.35, 0.1, 1.0);
color4 green_plastic_specular(0.45, 0.55, 0.45, 1.0);
float  green_plastic_shininess = .25 * 128;

color4 red_plastic_ambient(0.0, 0.0, 0.0, 1.0);
color4 red_plastic_diffuse(0.5, 0.0, 0.0, 1.0);
color4 red_plastic_specular(0.7, 0.6, 0.6, 1.0);
float  red_plastic_shininess = .25 * 128;

color4 white_plastic_ambient(0.0, 0.0, 0.0, 1.0);
color4 white_plastic_diffuse(0.55, 0.55, 0.55, 1.0);
color4 white_plastic_specular(0.7, 0.7, 0.7, 1.0);
float  white_plastic_shininess = .25 * 128;

color4 yellow_plastic_ambient(0.0, 0.0, 0.0, 1.0);
color4 yellow_plastic_diffuse(0.5, 0.5, 0.0, 1.0);
color4 yellow_plastic_specular(0.6, 0.6, 0.5, 1.0);
float  yellow_plastic_shininess = .25 * 128;

color4 black_rubber_ambient(0.02, 0.02, 0.02, 1.0);
color4 black_rubber_diffuse(0.01, 0.01, 0.01, 1.0);
color4 black_rubber_specular(0.4, 0.4, 0.4, 1.0);
float  black_rubber_shininess = .078125 * 128;

color4 green_rubber_ambient(0.0, 0.05, 0.0, 1.0);
color4 green_rubber_diffuse(0.4, 0.5, 0.4, 1.0);
color4 green_rubber_specular(0.04, 0.7, 0.04, 1.0);
float  green_rubber_shininess = .078125 * 128;

color4 red_rubber_ambient(0.05, 0.0, 0.0, 1.0);
color4 red_rubber_diffuse(0.5, 0.4, 0.4, 1.0);
color4 red_rubber_specular(0.7, 0.04, 0.04, 1.0);
float  red_rubber_shininess = .078125 * 128;

color4 white_rubber_ambient(0.05, 0.05, 0.05, 1.0);
color4 white_rubber_diffuse(0.5, 0.5, 0.5, 1.0);
color4 white_rubber_specular(0.7, 0.7, 0.7, 1.0);
float  white_rubber_shininess = .078125 * 128;

color4 yellow_rubber_ambient(0.05, 0.05, 0.0, 1.0);
color4 yellow_rubber_diffuse(0.5, 0.5, 0.4, 1.0);
color4 yellow_rubber_specular(0.7, 0.7, 0.04, 1.0);
float  yellow_rubber_shininess = .078125 * 128;

typedef struct
{
	point4 position;
	vec3 rotation;
	vec3 scale;
} Transform;

typedef struct
{
	color4 diffuse;
	color4 specular;
	color4 ambient;
	float shininess;
} Material;
/*
typedef struct
{
	point4 position;
	color4 diffuse;
	color4 specular;
	color4 ambient;
} LightStruct;

typedef struct
{
	point4 eye;
	point4 at;
	vec4 up;
} CameraStruct;
*/
Material emerald = { emerald_diffuse, emerald_specular, emerald_ambient, emerald_shininess};
Material ruby = { ruby_diffuse, ruby_specular, ruby_ambient, ruby_shininess };
Material cyan = { cyan_rubber_diffuse, cyan_rubber_specular, cyan_rubber_ambient, cyan_rubber_shininess };
Material gold = { gold_diffuse, gold_specular, gold_ambient, gold_shininess };
Material jade = { jade_diffuse, jade_specular, jade_ambient, jade_shininess };
Material obsidian = { obsidian_diffuse, obsidian_specular, obsidian_ambient, obsidian_shininess };
Material pearl = { pearl_diffuse, pearl_specular, pearl_ambient, pearl_shininess };
Material turquoise = { turquoise_diffuse, turquoise_specular, turquoise_ambient, turquoise_shininess };
Material brass = { brass_diffuse, brass_specular, brass_ambient, brass_shininess };
Material bronze = { bronze_diffuse, bronze_specular, bronze_ambient, bronze_shininess };
Material chrome = { chrome_diffuse, chrome_specular, chrome_ambient, chrome_shininess };
Material copper = { copper_diffuse, copper_specular, copper_ambient, copper_shininess };
Material silver = { silver_diffuse, silver_specular, silver_ambient, silver_shininess };
Material black_plastic = { black_plastic_diffuse, black_plastic_specular, black_plastic_ambient, black_plastic_shininess };
Material cyan_plastic = { cyan_plastic_diffuse, cyan_plastic_specular, cyan_plastic_ambient, cyan_plastic_shininess };
Material green_plastic = { green_plastic_diffuse, green_plastic_specular, green_plastic_ambient, green_plastic_shininess };
Material red_plastic = { red_plastic_diffuse, red_plastic_specular, red_plastic_ambient, red_plastic_shininess };
Material white_plastic = { white_plastic_diffuse, white_plastic_specular, white_plastic_ambient, white_plastic_shininess };
Material yellow_plastic = { yellow_plastic_diffuse, yellow_plastic_specular, yellow_plastic_ambient, yellow_plastic_shininess };
Material black_rubber = { black_rubber_diffuse, black_rubber_specular, black_rubber_ambient, black_rubber_shininess };
Material cyan_rubber = { cyan_rubber_diffuse, cyan_rubber_specular, cyan_rubber_ambient, cyan_rubber_shininess };
Material green_rubber = { green_rubber_diffuse, green_rubber_specular, green_rubber_ambient, green_rubber_shininess };
Material red_rubber = { red_rubber_diffuse, red_rubber_specular, red_rubber_ambient, red_rubber_shininess };
Material white_rubber = { white_rubber_diffuse, white_rubber_specular, white_rubber_ambient, white_rubber_shininess };
Material yellow_rubber = { yellow_rubber_diffuse, yellow_rubber_specular, yellow_rubber_ambient, yellow_rubber_shininess };







vec4 eye = vec4(0.0, 0.0, 5.0 * zoom, 1.0);
vec4 at = vec4(0.0, 0.0, 0.0, 1.0);
vec4 up = vec4(0.0, 1.0, 0.0, 0.0);

//CameraStruct mainCamera = { vec4(0.0, 0.0, 5.0, 1.0),vec4(0.0, 0.0, 0.0, 1.0), vec4(0.0, 1.0, 0.0, 0.0) };
//LightStruct mainLight = { light_position, light_diffuse, light_specular, light_ambient };

class Camera
{
public:
	point4 eye;
	point4 at;
	vec4 up;
	GLfloat fov;
	GLfloat aspectRatio;
	GLfloat nearZ;
	GLfloat farZ;

	Camera();
	void update();
	mat4 modelView();
	mat4 projection();
};

Camera::Camera()
{
	eye = vec4(0.0, 0.0, 5.0, 1.0);
	at = vec4(0.0, 0.0, 0.0, 1.0);
	up = vec4(0.0, 1.0, 0.0, 1.0);
	fov = 30.0;
	aspectRatio = 1;
	nearZ = 0.1;
	farZ = 1000;
}

void Camera::update()
{

}

mat4 Camera::modelView()
{
	return LookAt(eye, at, up);
}

mat4 Camera::projection()
{
	return Perspective(fov, aspectRatio, nearZ, farZ);
}

class Light
{
public:
	Transform transform;
	color4 diffuse;
	color4 specular;
	color4 ambient;

	Light();
	void update();
};

Light::Light()
{
	transform.position = point4(0);
	transform.rotation = vec3(0);
	transform.scale = vec3(1);
	diffuse = light_diffuse;
	specular = light_specular;
	ambient = light_ambient;
}

void Light::update()
{

}

class GraphicObject
{
public:
	GLint start;
	GLint nVertices;
	GLuint shader;
	GLuint textureID0;
	GLuint textureID1;
	GLuint textureID2;
	vec2 textureOffset;
	Transform transform;
	//point4 position;
	//vec3 rotation;
	//vec3 scale;
	vec3 rotationSpeed;
	vec3 velocity;
	Material material;
	//LightStruct *light;
	Light *light;
	Camera *camera;
	void (*actualDraw)(int);

	GraphicObject();
	void update();
	void draw();
};

GraphicObject::GraphicObject()
{
	start = 4;
	nVertices = 24;
	shader = 0;
	transform.position = point4(0);
	transform.rotation = vec3(0);
	transform.scale = vec3(1);
	rotationSpeed = vec3(0);
	velocity = vec3(0);
	textureOffset = vec2(0);
}

void GraphicObject::update()
{
	transform.rotation = transform.rotation + rotationSpeed;
	transform.position = transform.position + velocity;
}

void GraphicObject::draw()
{
	glUseProgram(shader);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(shader, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint loc2 = glGetAttribLocation(shader, "vNormal");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

	GLuint loc3 = glGetAttribLocation(shader, "vTexCoord");
	glEnableVertexAttribArray(loc3);
	glVertexAttribPointer(loc3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points) + sizeof(normals)));

	// compute a translation transformation
	mat4 positionTransformation = Translate(transform.position);
	// compute a rotation transformation about Z
	mat4 rotationTransformation = RotateX(transform.rotation.x) * RotateY(transform.rotation.y) * RotateZ(transform.rotation.z);
	// compute a scaling transformation
	mat4 scaleTransformation = Scale(scale);

	// computer the ModelView transformation
	mat4 modelView = positionTransformation * rotationTransformation * scaleTransformation;

	//modelView = LookAt(camera->eye, camera->at, camera->up) * modelView;
	modelView = camera->modelView() * modelView;

	// Send the ModelView to the shader
	glUniformMatrix4fv(glGetUniformLocation(shader, "ModelView"), 1, GL_TRUE, modelView);

	// computer the Projection transformation with Perspective
	//mat4 projection = Perspective(30.0, aspectRatio, 0.1, 1000);
	//mat4 projection = Perspective(camera->fov, camera->aspectRatio, camera->nearZ, camera->farZ);
	mat4 projection = camera->projection();

	// Send the Projection to the shader
	glUniformMatrix4fv(glGetUniformLocation(shader, "Projection"), 1, GL_TRUE, projection);

	glUniform2fv(glGetUniformLocation(shader, "vTexOffset"), 1, textureOffset);

	// Send the material to the shader
	glUniform4fv(glGetUniformLocation(shader, "MaterialAmbient"), 1, material.ambient);
	glUniform4fv(glGetUniformLocation(shader, "MaterialDiffuse"), 1, material.diffuse);
	glUniform4fv(glGetUniformLocation(shader, "MaterialSpecular"), 1, material.specular);
	glUniform1f(glGetUniformLocation(shader, "Shininess"), material.shininess);

	// send the light color parameters to the shader
	glUniform4fv(glGetUniformLocation(shader, "LightAmbient"), 1, light->ambient);
	glUniform4fv(glGetUniformLocation(shader, "LightDiffuse"), 1, light->diffuse);
	glUniform4fv(glGetUniformLocation(shader, "LightSpecular"), 1, light->specular);
	glUniform4fv(glGetUniformLocation(shader, "LightPosition"), 1, light->transform.position);

	glUniform2fv(glGetUniformLocation(shader, "TextureOffset"), 1, textureOffset);

	glEnable(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(shader, "texture"), 0);
	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, textureID0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	glUniform1i(glGetUniformLocation(shader, "specularTexture"), 1);
	glActiveTexture(GL_TEXTURE1); 
	glBindTexture(GL_TEXTURE_2D, textureID1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	(*actualDraw)(start);

	glDisable(GL_TEXTURE_2D);

	/*
	glDrawArrays(GL_TRIANGLE_STRIP, start, 4);    // draw the points
	glDrawArrays(GL_TRIANGLE_STRIP, start + 4, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, start + 8, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, start + 12, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, start + 16, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, start + 20, 4);
	*/
}

GraphicObject *theOne, *theOther, *theTetra;
Light *theLight;
Camera *theCamera;
GLuint globalTextureID0, globalTextureID1;

void drawSquare(int start)
{
	glDrawArrays(GL_TRIANGLE_STRIP, start, 4);
}

void drawCube(int start)
{
	for (int square = 0; square < 6; square++)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, start + square * 4, 4);
	}
	/*
	glDrawArrays(GL_TRIANGLE_STRIP, start + 0, 4);    // draw the points
	glDrawArrays(GL_TRIANGLE_STRIP, start + 4, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, start + 8, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, start + 12, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, start + 16, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, start + 20, 4);
	*/
}

void drawTetrahedron(int start)
{
	for (int triangle = 0; triangle < 4; triangle++)
	{
		glDrawArrays(GL_TRIANGLES, start + triangle * 3, 3);
	}
}

void
rotationMenu(int choice)
{
	switch(choice)
	{
	case 1:
		speed *= 1.1;
		break;
	case 2:
		speed *= 0.9;
		break;
	default:
		break;
	}
}

void
scaleMenu(int choice)
{
	switch(choice)
	{
	case 1:
		scale *= 1.1;
		break;
	case 2:
		scale *= 0.9;
		break;
	default:
		break;
	}
}

void
materialMenu(int choice)
{
	switch (choice)
	{
	case 0:
		exit(0);
		break;
	default:
		break;
	}
}

void
standardMatMenu(int choice)
{
	Material *objectMaterial;

	switch (choice)
	{
	case 1:
		objectMaterial = &emerald;
		break;
	case 2:
		objectMaterial = &jade;
		break;
	case 3:
		objectMaterial = &obsidian;
		break;
	case 4:
		objectMaterial = &pearl;
		break;
	case 5:
		objectMaterial = &ruby;
		break;
	case 6:
		objectMaterial = &turquoise;
		break;
	case 7:
		objectMaterial = &brass;
		break;
	case 8:
		objectMaterial = &bronze;
		break;
	case 9:
		objectMaterial = &chrome;
		break;
	case 10:
		objectMaterial = &copper;
		break;
	case 11:
		objectMaterial = &gold;
		break;
	case 12:
		objectMaterial = &silver;
		break;
	default:
		break;
	}

	if (objectMaterial) {
		theOne->material = *objectMaterial;
		theOther->material = *objectMaterial;
		theTetra->material = *objectMaterial;
	}

}

void
plasticMatMenu(int choice) 
{
	Material *objectMaterial;

	switch (choice)
	{
	case 1:
		objectMaterial = &black_plastic;
		break;
	case 2:
		objectMaterial = &cyan_plastic;
		break;
	case 3:
		objectMaterial = &green_plastic;
		break;
	case 4:
		objectMaterial = &red_plastic;
		break;
	case 5:
		objectMaterial = &white_plastic;
		break;
	case 6:
		objectMaterial = &yellow_plastic;
		break;
	default:
		break;
	}

	if (objectMaterial) {
		theOne->material = *objectMaterial;
		theOther->material = *objectMaterial;
		theTetra->material = *objectMaterial;
	}
}

void
texOffsetMenu(int choice)
{
	switch (choice)
	{
	case 1:
		theOne->textureOffset.y += 0.1;
		theOther->textureOffset.y += 0.1;
		theTetra->textureOffset.y += 0.1;
		break;
	case 2:
		theOne->textureOffset.y -= 0.1;
		theOther->textureOffset.y -= 0.1;
		theTetra->textureOffset.y -= 0.1;
		break;
	case 3:
		theOne->textureOffset.x -= 0.1;
		theOther->textureOffset.x -= 0.1;
		theTetra->textureOffset.x -= 0.1;
		break;
	case 4:
		theOne->textureOffset.x += 0.1;
		theOther->textureOffset.x += 0.1;
		theTetra->textureOffset.x += 0.1;
		break;
	default:
		break;
	}
}

void
rubberMatMenu(int choice)
{
	Material *objectMaterial;

	switch (choice)
	{
	case 1:
		objectMaterial = &black_rubber;
		break;
	case 2:
		objectMaterial = &cyan_rubber;
		break;
	case 3:
		objectMaterial = &green_rubber;
		break;
	case 4:
		objectMaterial = &red_rubber;
		break;
	case 5:
		objectMaterial = &white_rubber;
		break;
	case 6:
		objectMaterial = &yellow_rubber;
		break;
	default:
		break;
	}

	if (objectMaterial) {
		theOne->material = *objectMaterial;
		theOther->material = *objectMaterial;
		theTetra->material = *objectMaterial;
	}
}

void
modMaterialMenu(int choice)
{
	switch (choice)
	{
	case 1:
		currentMode = AMBIENT;
		break;
	case 2:
		currentMode = DIFFUSE;
		break;
	case 3:
		currentMode = SPECULAR;
		break;
	case 4:
		currentMode = SHININESS;
		break;
	default:
		break;
	}
}

void
textureMenu(int choice)
{
	switch (choice) 
	{
	case 0:
		theOne->textureID0 = NULL;

		theOther->textureID0 = NULL;

		theTetra->textureID0 = NULL;
		
		theOne->shader = program0;
		theOther->shader = program0;
		theOther->shader = program0;
		break;
	}

}

void
texSelectionMenu(int choice)
{
	switch (choice)
	{
	case 1:
		theOne->textureID0 = globalTextureID0;
		theOther->textureID0 = globalTextureID0;
		theTetra->textureID0 = globalTextureID0;
		break;
	case 2:
		theOne->textureID0 = globalTextureID1;
		theOther->textureID0 = globalTextureID1;
		theTetra->textureID0 = globalTextureID1;
		break;
	default:
		return;
	}
	theOne->shader = program1;
	theOther->shader = program1;
	theTetra->shader = program1;
}

void
mMenu(int choice)
{
	switch(choice)
	{
	case 0:
		exit(0);
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------

void computeSquare()
{
	// this defines points for a square
	points[limit + 0] = point4(0.5, -0.5, 0.0, 1.0);
	points[limit + 1] = point4(-0.5, -0.5, 0.0, 1.0);
	points[limit + 2] = point4(0.5, 0.5, 0.0, 1.0);
	points[limit + 3] = point4(-0.5, 0.5, 0.0, 1.0);

	// this defines appropriate normals
	normals[limit + 0] = normal3(0.0, 0.0, 1.0);
	normals[limit + 1] = normal3(0.0, 0.0, 1.0);
	normals[limit + 2] = normal3(0.0, 0.0, 1.0);
	normals[limit + 3] = normal3(0.0, 0.0, 1.0);

	// this defines the texture coordinates
	texCoords[limit + 0] = vec2(1, 0);
	texCoords[limit + 1] = vec2(0, 0);
	texCoords[limit + 2] = vec2(1, 1);
	texCoords[limit + 3] = vec2(0, 1);

	limit += 4;
}

void
computeCube()
{
	GLint localLimit = limit;
	// this defines points for the front square
	points[localLimit + 0] = point4(0.5, -0.5, 0.0, 1.0);
	points[localLimit + 1] = point4(-0.5, -0.5, 0.0, 1.0);
	points[localLimit + 2] = point4(0.5, 0.5, 0.0, 1.0);
	points[localLimit + 3] = point4(-0.5, 0.5, 0.0, 1.0);

	// this defines appropriate normals
	normals[localLimit + 0] = normal3(0.0, 0.0, 1.0);
	normals[localLimit + 1] = normal3(0.0, 0.0, 1.0);
	normals[localLimit + 2] = normal3(0.0, 0.0, 1.0);
	normals[localLimit + 3] = normal3(0.0, 0.0, 1.0);

	// this defines the texture coordinates
	texCoords[localLimit + 0] = vec2(1, 0);
	texCoords[localLimit + 1] = vec2(0, 0);
	texCoords[localLimit + 2] = vec2(1, 1);
	texCoords[localLimit + 3] = vec2(0, 1);

	localLimit += 4;
	// this defines points for the back square
	mat4 transformation = Translate(0, 0, -0.5) * RotateY(180);
	points[localLimit + 0] = transformation * points[limit + 0];
	points[localLimit + 1] = transformation * points[limit + 1];
	points[localLimit + 2] = transformation * points[limit + 2];
	points[localLimit + 3] = transformation * points[limit + 3];

	normals[localLimit + 0] = normal3(0.0, 0.0, -1.0);
	normals[localLimit + 1] = normal3(0.0, 0.0, -1.0);
	normals[localLimit + 2] = normal3(0.0, 0.0, -1.0);
	normals[localLimit + 3] = normal3(0.0, 0.0, -1.0);

	// this defines the texture coordinates
	texCoords[localLimit + 0] = vec2(1, 0);
	texCoords[localLimit + 1] = vec2(0, 0);
	texCoords[localLimit + 2] = vec2(1, 1);
	texCoords[localLimit + 3] = vec2(0, 1);

	localLimit += 4;
	// this defines points for the right square
	transformation = Translate(0.5, 0, 0) * RotateY(90);
	points[localLimit + 0] = transformation * points[limit + 0];
	points[localLimit + 1] = transformation * points[limit + 1];
	points[localLimit + 2] = transformation * points[limit + 2];
	points[localLimit + 3] = transformation * points[limit + 3];

	normals[localLimit + 0] = normal3(1.0, 0.0, 0.0);
	normals[localLimit + 1] = normal3(1.0, 0.0, 0.0);
	normals[localLimit + 2] = normal3(1.0, 0.0, 0.0);
	normals[localLimit + 3] = normal3(1.0, 0.0, 0.0);

	// this defines the texture coordinates
	texCoords[localLimit + 0] = vec2(1, 0);
	texCoords[localLimit + 1] = vec2(0, 0);
	texCoords[localLimit + 2] = vec2(1, 1);
	texCoords[localLimit + 3] = vec2(0, 1);

	localLimit += 4;
	// this defines points for the left square
	transformation = Translate(-0.5, 0, 0) * RotateY(-90);
	points[localLimit + 0] = transformation * points[limit + 0];
	points[localLimit + 1] = transformation * points[limit + 1];
	points[localLimit + 2] = transformation * points[limit + 2];
	points[localLimit + 3] = transformation * points[limit + 3];

	normals[localLimit + 0] = normal3(-1.0, 0.0, 0.0);
	normals[localLimit + 1] = normal3(-1.0, 0.0, 0.0);
	normals[localLimit + 2] = normal3(-1.0, 0.0, 0.0);
	normals[localLimit + 3] = normal3(-1.0, 0.0, 0.0);

	// this defines the texture coordinates
	texCoords[localLimit + 0] = vec2(1, 0);
	texCoords[localLimit + 1] = vec2(0, 0);
	texCoords[localLimit + 2] = vec2(1, 1);
	texCoords[localLimit + 3] = vec2(0, 1);

	localLimit += 4;
	// this defines points for the top square
	transformation = Translate(0, 0.5, 0) * RotateX(90);
	points[localLimit + 0] = transformation * points[limit + 0];
	points[localLimit + 1] = transformation * points[limit + 1];
	points[localLimit + 2] = transformation * points[limit + 2];
	points[localLimit + 3] = transformation * points[limit + 3];

	normals[localLimit + 0] = normal3(0.0, 1.0, 0.0);
	normals[localLimit + 1] = normal3(0.0, 1.0, 0.0);
	normals[localLimit + 2] = normal3(0.0, 1.0, 0.0);
	normals[localLimit + 3] = normal3(0.0, 1.0, 0.0);

	// this defines the texture coordinates
	texCoords[localLimit + 0] = vec2(1, 0);
	texCoords[localLimit + 1] = vec2(0, 0);
	texCoords[localLimit + 2] = vec2(1, 1);
	texCoords[localLimit + 3] = vec2(0, 1);

	localLimit += 4;
	// this defines points for the botton square
	transformation = Translate(0, -0.5, 0) * RotateX(-90);
	points[localLimit + 0] = transformation * points[limit + 0];
	points[localLimit + 1] = transformation * points[limit + 1];
	points[localLimit + 2] = transformation * points[limit + 2];
	points[localLimit + 3] = transformation * points[limit + 3];

	normals[localLimit + 0] = normal3(0.0, -1.0, 0.0);
	normals[localLimit + 1] = normal3(0.0, -1.0, 0.0);
	normals[localLimit + 2] = normal3(0.0, -1.0, 0.0);
	normals[localLimit + 3] = normal3(0.0, -1.0, 0.0);

	// this defines the texture coordinates
	texCoords[localLimit + 0] = vec2(1, 0);
	texCoords[localLimit + 1] = vec2(0, 0);
	texCoords[localLimit + 2] = vec2(1, 1);
	texCoords[localLimit + 3] = vec2(0, 1);

	localLimit += 4;
	// this translate points for the front square
	transformation = Translate(0, 0, 0.5);
	points[limit + 0] = transformation * points[limit + 0];
	points[limit + 1] = transformation * points[limit + 1];
	points[limit + 2] = transformation * points[limit + 2];
	points[limit + 3] = transformation * points[limit + 3];
	

	limit = localLimit;


}

void
computeTetrahedron()
{
	GLint localLimit = limit;

	//Define points for front triangle
	points[localLimit + 0] = point4( -0.25, 0.0, 0.0, 1.0 ); //Left Point
	points[localLimit + 1] = point4( 0.25, 0.0, 0.0, 1.0 ); //Right Point
	points[localLimit + 2] = point4( 0.0, 0.48, -0.25, 1.0); //Peak Point

	//Define normals
	normals[localLimit + 0] = normal3(0.0, 0.0, 1.0);
	normals[localLimit + 1] = normal3(0.0, 0.0, 1.0);
	normals[localLimit + 2] = normal3(0.0, 0.0, 1.0);

	//Define texture coordinates
	texCoords[localLimit + 0] = vec2(0, 0);
	texCoords[localLimit + 1] = vec2(1, 0);
	texCoords[localLimit + 2] = vec2(0.5, 1);

	localLimit += 3;

	//Define points for back-left triangle
	points[localLimit + 0] = point4(0.0, 0.0, -.5, 1.0); //Left Point
	points[localLimit + 1] = point4(-0.25, 0.0, 0.0, 1.0); //Right Point
	points[localLimit + 2] = point4(0.0, 0.48, -0.25, 1.0);; //Peak Point

	//Define normals for back-left triangle
	normals[localLimit + 0] = normal3(-1.0, 0.0, 0);
	normals[localLimit + 1] = normal3(-1.0, 0.0, 0);
	normals[localLimit + 2] = normal3(-1.0, 0.0, 0);

	//Define texture coordinates
	texCoords[localLimit + 0] = vec2(0, 0);
	texCoords[localLimit + 1] = vec2(1, 0);
	texCoords[localLimit + 2] = vec2(0.5, 1);

	localLimit += 3;

	//Define points for back-right triangle
	points[localLimit + 0] = point4(0.25, 0.0, 0.0, 1.0); //Left Point
	points[localLimit + 1] = point4(0.0, 0.0, -0.5, 1.0); //Right Point
	points[localLimit + 2] = point4(0.0, 0.48, -0.25, 1.0);; //Peak Point

	//Define normals for back-right triangle
	normals[localLimit + 0] = normal3(1.0, 0.0, 0);
	normals[localLimit + 1] = normal3(1.0, 0.0, 0);
	normals[localLimit + 2] = normal3(1.0, 0.0, 0);

	//Define texture coordinates
	texCoords[localLimit + 0] = vec2(0, 0);
	texCoords[localLimit + 1] = vec2(1, 0);
	texCoords[localLimit + 2] = vec2(0.5, 1);

	localLimit += 3;

	//Define points for bottom triangle
	points[localLimit + 0] = point4(-0.25, 0.0, 0.0, 1.0); //Left Point
	points[localLimit + 1] = point4(0.25, 0.0, 0.0, 1.0); //Right Point
	points[localLimit + 2] = point4(0.0, 0.0, -0.48, 1.0);; //Peak Point

	//Define normals for bottom triangle
	normals[localLimit + 0] = normal3(1.0, 0.0, 0);
	normals[localLimit + 1] = normal3(1.0, 0.0, 0);
	normals[localLimit + 2] = normal3(1.0, 0.0, 0);

	//Define texture coordinates
	texCoords[localLimit + 0] = vec2(0, 0);
	texCoords[localLimit + 1] = vec2(1, 0);
	texCoords[localLimit + 2] = vec2(0.5, 1);

	localLimit += 3;

	limit = localLimit;

}

void
init( void )
{
	globalTextureID0 = SOIL_load_OGL_texture
	(
		"img_test.bmp", 
		SOIL_LOAD_AUTO, 
		SOIL_CREATE_NEW_ID, 
		SOIL_FLAG_POWER_OF_TWO | 
		SOIL_FLAG_MIPMAPS | 
		SOIL_FLAG_INVERT_Y | 
		SOIL_FLAG_MULTIPLY_ALPHA | 
		SOIL_FLAG_DDS_LOAD_DIRECT
	);

	globalTextureID1 = SOIL_load_OGL_texture
	(
		"Graphics.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO |
		SOIL_FLAG_MIPMAPS |
		SOIL_FLAG_INVERT_Y |
		SOIL_FLAG_MULTIPLY_ALPHA |
		SOIL_FLAG_DDS_LOAD_DIRECT
	);

	startSquare = limit;
 	computeSquare();
	endSquare = limit;
	startCube = limit;
	computeCube();
	endCube = limit;
	startTetra = limit;
	computeTetrahedron();
	endTetra = limit;
	theOne = new GraphicObject();
	theOther = new GraphicObject();
	theTetra = new GraphicObject();
	theLight = new Light();
	theCamera = new Camera();

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(normals) + sizeof(texCoords), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(normals), normals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(normals), sizeof(texCoords), texCoords);

    // Load shaders and use the resulting shader program
	program0 = InitShader( "vertexShading.vert", "vertexShading.frag" );
	program1 = InitShader("fragmentShading.vert", "fragmentShading.frag");
	theOne->shader = program0;
	theOne->transform.position = point4(-1, 0, 0, 1);
	theOne->material = red_rubber;
	theOne->rotationSpeed = vec3(1, 0.5, 0.33);
	//theOne->velocity = vec3(0, 0.01, 0);
	theOne->camera = theCamera;
	theOne->light = theLight;
	theOne->start = startSquare;
	theOne->nVertices = 4;
	theOne->actualDraw = drawSquare;

	
	theOther->shader = program1;
	theOther->textureID0 = globalTextureID0;
	theOther->transform.position = point4(1, 0, 0, 1);
	theOther->material = emerald;
	theOther->rotationSpeed = vec3(0.5, 1, 0.33);
	//theOther->velocity = vec3(0.01, 0, 0);
	theOther->camera = theCamera;
	theOther->light = theLight;
	theOther->start = startCube;
	theOther->nVertices = 4;
	theOther->actualDraw = drawCube;

	theTetra->shader = program0;
	//theTetra->textureID0 = globalTextureID0;
	theTetra->transform.position = point4(-.1, 0.8, 0, 1);
	theTetra->material = emerald;
	theTetra->rotationSpeed = vec3(0.5, 1, 0.33);
	//theOther->velocity = vec3(0.01, 0, 0);
	theTetra->camera = theCamera;
	theTetra->light = theLight;
	theTetra->start = startTetra;
	theTetra->nVertices = 3;
	theTetra->actualDraw = drawTetrahedron;
	glUseProgram( program1 );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program1, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint loc2 = glGetAttribLocation( program1, "vNormal" );
    glEnableVertexAttribArray( loc2 );
    glVertexAttribPointer( loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)) );

	GLuint loc3 = glGetAttribLocation(program1, "vTexCoord");
	glEnableVertexAttribArray(loc3);
	glVertexAttribPointer(loc3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points) + sizeof(normals)));

	glEnable(GL_DEPTH_TEST);
	glClearColor( 0.5, 0.5, 0.5, 1.0 ); // gray background
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window
    //glDrawArrays( GL_TRIANGLE_STRIP, 0, limit );    // draw the points
	theOne->draw();
	theOther->draw();
	theTetra->draw();
	glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
	case '-':
		//zoom *= 1.1f;
		theCamera->fov = theCamera->fov * 1.1f;
		break;
	case '+':
		//zoom *= 0.9f;
		theCamera->fov = theCamera->fov * 0.9f;
		break;
	case 'a':
	case 'A':
		animate = animate == 1 ? 0 : 1;
		break;
	default:
		break;
    }
	glutPostRedisplay();
}

void
specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		theCamera->eye.y += 0.1;
		break;
	case GLUT_KEY_DOWN:
		theCamera->eye.y -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		theCamera->eye.x -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		theCamera->eye.x += 0.1;
		break;
	}
	glutPostRedisplay();
}

void
reshape( int w, int h )
{
	//aspectRatio = (GLfloat)w/(GLfloat)h;
	theCamera->aspectRatio = (GLfloat)w / (GLfloat)h;
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

void
timerFunction(GLint value)
{
	if (animate)
	{
		theta += speed;
		if (theta > 360.0)
		{
			theta -= 360.0;
		}

		theOne->update();
		theOther->update();
		theTetra->update();
		theLight->transform.position = RotateY(theta) * theLight->transform.position;
	}

	glutTimerFunc(rate, timerFunction, 1);
	glutPostRedisplay();
}
//----------------------------------------------------------------------------

void
createMenus()
{
	GLint rotMenu = glutCreateMenu(rotationMenu);
	glutAddMenuEntry("Increase Speed", 1);
	glutAddMenuEntry("Decrease Speed", 2);

	GLint scalMenu = glutCreateMenu(scaleMenu);
	glutAddMenuEntry("Increase Scale", 1);
	glutAddMenuEntry("Decrease Scale", 2);

	

	GLint standardMenu = glutCreateMenu(standardMatMenu);
	glutAddMenuEntry("Emerald", 1);
	glutAddMenuEntry("Jade", 2);
	glutAddMenuEntry("Obsidian", 3);
	glutAddMenuEntry("Pearl", 4);
	glutAddMenuEntry("Ruby", 5);
	glutAddMenuEntry("Turquoise", 6);
	glutAddMenuEntry("Brass", 7);
	glutAddMenuEntry("Bronze", 8);
	glutAddMenuEntry("Chrome", 9);
	glutAddMenuEntry("Copper", 10);
	glutAddMenuEntry("Gold", 11);
	glutAddMenuEntry("Silver", 12);

	GLint plasticMenu = glutCreateMenu(plasticMatMenu);
	glutAddMenuEntry("Black", 1);
	glutAddMenuEntry("Cyan", 2);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("Red", 4);
	glutAddMenuEntry("White", 5);
	glutAddMenuEntry("Yellow", 6);

	GLint rubberMenu = glutCreateMenu(rubberMatMenu);
	glutAddMenuEntry("Black", 1);
	glutAddMenuEntry("Cyan", 2);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("Red", 4);
	glutAddMenuEntry("White", 5);
	glutAddMenuEntry("Yellow", 6);

	/*GLint modMatMenu = glutCreateMenu(modMaterialMenu);
	glutAddMenuEntry("Ambient", 1);
	glutAddMenuEntry("Diffuse", 2);
	glutAddMenuEntry("Specular", 3);
	glutAddMenuEntry("Shininess", 4);*/

	GLint matMenu = glutCreateMenu(materialMenu);
	glutAddSubMenu("Standard", standardMenu);
	glutAddSubMenu("Plastic", plasticMenu);
	glutAddSubMenu("Rubber", rubberMenu);
	//glutAddSubMenu("Modify", modMatMenu);

	GLint texSelMenu = glutCreateMenu(texSelectionMenu);
	glutAddMenuEntry("Test Image", 1);
	glutAddMenuEntry("Name", 2);

	GLint texOffMenu = glutCreateMenu(texOffsetMenu);
	glutAddMenuEntry("Down", 1);
	glutAddMenuEntry("Up", 2);
	glutAddMenuEntry("Right", 3);
	glutAddMenuEntry("Left", 4);

	GLint texMenu = glutCreateMenu(textureMenu);
	glutAddSubMenu("Add Texture", texSelMenu);
	glutAddSubMenu("Offset", texOffMenu);
	glutAddMenuEntry("Remove Texture", 0);

	GLint mainMenu = glutCreateMenu(mMenu);
	glutAddSubMenu("Rotation", rotMenu);
	glutAddSubMenu("Scale", scalMenu);
	glutAddSubMenu("Material", matMenu);
	glutAddSubMenu("Texture", texMenu);
	glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize( 512, 512 );
	// Here you set the OpenGL version
    glutInitContextVersion( 4 , 4 );
	//Use only one of the next two lines
    //glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );
    glutCreateWindow( "First App in 3D" );

    // Uncomment if you are using GLEW
	glewInit(); 

    init();
	createMenus();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
	glutSpecialFunc( specialKeys );
	glutReshapeFunc( reshape );
	glutTimerFunc(rate, timerFunction, 1);

    glutMainLoop();
    return 0;
}

/*
		// compute new theta
		theta += speed;
		if (theta > 360.0)
		{
			theta -= 360.0;
		}

		// compute a translation transformation
		mat4 position = Translate(-1, 0, 0);
		// compute a rotation transformation about Z
		mat4 rotation = RotateX(theta) * RotateY( 3 * theta);
		// compute a scaling transformation
		mat4 scaling = Scale(scale, scale, scale);

		// computer the ModelView transformation
		mat4 modelView = position * rotation * scaling;

		// Position the camera, its up vector and orientation
		vec4 eye = vec4(0.0, 0.0, 5.0 * zoom, 1.0);
		vec4 at = vec4(0.0, 0.0, 0.0, 1.0);
		vec4 up = vec4(0.0, 1.0, 0.0, 0.0);

		// combine the transformations of camera and ModelView
		modelView = LookAt(eye, at, up) * modelView;

		// Send the ModelView to the shader
		glUniformMatrix4fv(glGetUniformLocation(program, "ModelView"), 1, GL_TRUE, modelView);

		// computer the Projection transformation with Perspective
		mat4 projection = Perspective(30.0, aspectRatio, 0.1, 1000);

		// Send the Projection to the shader
		glUniformMatrix4fv(glGetUniformLocation(program, "Projection"), 1, GL_TRUE, projection);

		// Send the material to the shader
		glUniform4fv(glGetUniformLocation(program, "MaterialAmbient"), 1, gold_ambient);
		glUniform4fv(glGetUniformLocation(program, "MaterialDiffuse"), 1, gold_diffuse);
		glUniform4fv(glGetUniformLocation(program, "MaterialSpecular"), 1, gold_specular);
		glUniform1f(glGetUniformLocation(program, "Shininess"), gold_shininess);

		// set the light position
		light_position = RotateY(theta / 2) * vec4(0.0, 0.0, 5.0, 1.0);

		// send the light color parameters to the shader
		glUniform4fv(glGetUniformLocation(program, "LightAmbient"), 1, light_ambient);
		glUniform4fv(glGetUniformLocation(program, "LightDiffuse"), 1, light_diffuse);
		glUniform4fv(glGetUniformLocation(program, "LightSpecular"), 1, light_specular);
		glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);

*/