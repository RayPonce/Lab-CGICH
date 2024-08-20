//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá

//color café en RGB : 0.478, 0.255, 0.067

void CrearLetrasyFiguras()
{	
	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-0.55f,	0.3f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.55f,	0.3f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		0.55f,	-0.8f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-0.8f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.775f,	-0.15f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	GLfloat vertices_trianguloverde2[] = {
		//X			Y			Z			R		G		B
		-0.55f,	-0.8f,		0.5f,			0.0f,	0.5f,	0.0f,
		-1.0f,	-0.8f,		0.5f,			0.0f,	0.5f,	0.0f,
		-0.775f,	-0.15f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde2 = new MeshColor();
	trianguloverde2->CreateMeshColor(vertices_trianguloverde2, 18);
	meshColorList.push_back(trianguloverde2);

	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.3f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.3f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.3f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.2f,	-1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.2f,	-1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.2f,	-0.55f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.2f,	-1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.2f,	-0.55f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.2f,	-0.55f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	GLfloat vertices_cuadradoverde2[] = {
		//X			Y			Z			R		G		B
		-0.05f,	-0.25f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.4f,	-0.25f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.05f,	0.2f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.4f,	-0.25f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.05f,	0.2f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.4f,	0.2f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde2 = new MeshColor();
	cuadradoverde2->CreateMeshColor(vertices_cuadradoverde2, 36);
	meshColorList.push_back(cuadradoverde2);

	GLfloat vertices_cuadradoverde3[] = {
		//X			Y			Z			R		G		B
		0.05f,	-0.25f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	-0.25f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.05f,	0.2f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	-0.25f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.05f,	0.2f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	0.2f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde3 = new MeshColor();
	cuadradoverde3->CreateMeshColor(vertices_cuadradoverde3, 36);
	meshColorList.push_back(cuadradoverde3);


	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.85f,	-1.0f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.7f,	-1.0f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.7f,	-0.8f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.85f,	-1.0f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.7f,	-0.8f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.85f,	-0.8f,		0.5f,			0.478f,	0.255f,	0.067f,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);

	GLfloat vertices_cuadradocafe2[] = {
		//X			Y			Z			R		G		B
		0.85f,	-1.0f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.7f,	-1.0f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.7f,	-0.8f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.85f,	-1.0f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.7f,	-0.8f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.85f,	-0.8f,		0.5f,			0.478f,	0.255f,	0.067f,

	};

	MeshColor* cuadradocafe2 = new MeshColor();
	cuadradocafe2->CreateMeshColor(vertices_cuadradocafe2, 36);
	meshColorList.push_back(cuadradocafe2);
}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		
		meshColorList[4]->RenderMeshColor();
		meshColorList[5]->RenderMeshColor();
		meshColorList[6]->RenderMeshColor();
		meshColorList[0]->RenderMeshColor();
		meshColorList[3]->RenderMeshColor();
		meshColorList[7]->RenderMeshColor();
		meshColorList[8]->RenderMeshColor();
		meshColorList[1]->RenderMeshColor();
		meshColorList[2]->RenderMeshColor();

		
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
