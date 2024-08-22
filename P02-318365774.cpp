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
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderRojo = "shaders/shaderRojo.vert";
static const char* vShaderAzul = "shaders/shaderAzul.vert";
static const char* vShaderVerde = "shaders/shaderVerde.vert";
static const char* vShaderCafe = "shaders/shaderCafe.vert";
static const char* vShaderVerdeF = "shaders/shaderVerdeF.vert";

float angulo = 0.0f;

//Pirámide azul
void CreaPiramideAzul()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.55f,	0.3f, 0.5f,
		0.55f, 0.3f, 0.5f,
		0.0f, 1.0f, 0.5f,
		0.0f, 0.3f, 0.0f
	};
	Mesh* P_Azul = new Mesh();
	P_Azul->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(P_Azul);
}

//Pirámide Verde 1
void CreaPiramideVerde1()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		0.55f,	-0.8f,		0.5f,
		1.0f,	-0.8f,		0.5f,
		0.775f,	-0.15f,		0.5f,
		0.775f, -0.8f,		0.0f,
	};
	Mesh* P_Verde = new Mesh();
	P_Verde->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(P_Verde);
}

//Pirámide Verde 2
void CreaPiramideVerde2()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.55f,	 -0.8f,	 0.5f,
		-1.0f,	 -0.8f,	 0.5f,
		-0.775f, -0.15f, 0.5f,
		-0.775f, -0.8f,	 0.0f,
	};
	Mesh* P_Verde = new Mesh();
	P_Verde->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(P_Verde);
}

//Cubo rojo
void CrearCuboRojo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -1.0f, 0.5f,
		0.5f, -1.0f, 0.5f,
		0.5f, 0.3f, 0.5f,
		-0.5f, 0.3f, 0.5f,
		// back
		-0.5f, -1.0f, 0.5f,
		0.5f, -1.0f, 0.5f,
		0.5f, 0.3f, 0.5f,
		-0.5f, 0.3f, 0.5f,
	};
	Mesh* cuboRojo = new Mesh();
	cuboRojo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cuboRojo);
}

//Cubo verde
void CrearCuboVerde()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.2f,	-1.0f,	0.5f,
		0.2f,	-1.0f,	0.5f,
		0.2f,	-0.55f,	0.5f,
		-0.2f,	-0.55f,	0.5f,
		// back
		-0.2f,	-1.0f,	0.5f,
		0.2f,	-1.0f,	0.5f,
		0.2f,	-0.55f,	0.5f,
		-0.2f,	-0.55f,	0.5f,
	};
	Mesh* cuboVerde = new Mesh();
	cuboVerde->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cuboVerde);
}

//Cubo verde 2
void CrearCuboVerde2()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.05f,	-0.25f,	0.5f,
		-0.4f,	-0.25f,	0.5f,
		-0.05f,	0.2f,	0.5f,
		-0.4f,	0.2f,	0.5f,
		// back
		-0.05f,	-0.25f,	0.5f,
		-0.4f,	-0.25f,	0.5f,
		-0.05f,	0.2f,	0.5f,
		-0.4f,	0.2f,	0.5f,
	};
	Mesh* cuboVerde = new Mesh();
	cuboVerde->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cuboVerde);
}

//Cubo verde 3
void CrearCuboVerde3()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		0.05f,	-0.25f,	0.5f,
		0.4f,	-0.25f,	0.5f,
		0.05f,	0.2f,	0.5f,
		0.4f,	0.2f,	0.5f,
		// back
		0.05f,	-0.25f,	0.5f,
		0.4f,	-0.25f,	0.5f,
		0.05f,	0.2f,	0.5f,
		0.4f,	0.2f,	0.5f,
	};
	Mesh* cuboVerde = new Mesh();
	cuboVerde->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cuboVerde);
}

//Cubo café
void CrearCuboCafe()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.85f,	-1.0f,	0.5f,
		-0.7f,	-1.0f,	0.5f,
		-0.7f,	-0.8f,	0.5f,
		-0.85f,	-0.8f,	0.5f,
		// back
		-0.85f,	-1.0f,	0.5f,
		-0.7f,	-1.0f,	0.5f,
		-0.7f,	-0.8f,	0.5f,
		-0.85f,	-0.8f,	0.5f,
	};
	Mesh* cuboCafe = new Mesh();
	cuboCafe->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cuboCafe);
}

//Cubo café 2
void CrearCuboCafe2()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		0.85f,	-1.0f,	0.5f,
		0.7f,	-1.0f,	0.5f,
		0.7f,	-0.8f,	0.5f,
		0.85f,	-0.8f,	0.5f,
		// back
		0.85f,	-1.0f,	0.5f,
		0.7f,	-1.0f,	0.5f,
		0.7f,	-0.8f,	0.5f,
		0.85f,	-0.8f,	0.5f,
	};
	Mesh* cuboCafe = new Mesh();
	cuboCafe->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cuboCafe);
}

//Letras con mi nombre
void CrearLetrasyFiguras()
{
	GLfloat vertices_letraR[] = {
		//X		Y		Z		R	  G		B
		-0.8f, 0.2f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.8f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.7f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.7f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.8f, 0.2f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.7f, 0.2f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.8f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.8f, 0.7f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.7f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.8f, 0.7f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.8f, 0.5f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.5f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.8f, 0.4f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.8f, 0.4f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.5f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.4f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.5f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.5f, 0.8f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.475f, 0.45f, 0.0f,	0.0f, 0.1f, 1.0f,
		-0.525f, 0.45f, 0.0f,	0.0f, 0.1f, 1.0f,
		-0.5f, 0.2f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.475f, 0.45f, 0.0f,	0.0f, 0.1f, 1.0f,
		-0.5f, 0.2f, 0.0f,		0.0f, 0.1f, 1.0f,
		-0.4f, 0.2f, 0.0f,		0.0f, 0.1f, 1.0f,
	};
	MeshColor* letra_R = new MeshColor();
	letra_R->CreateMeshColor(vertices_letraR, 180);
	meshColorList.push_back(letra_R);

	GLfloat vertices_letraP[] = {
		//X		Y	  Z		R	   G		B
		0.4f, 0.2f, 0.0f,	0.55f, 0.788f,0.4f,
		0.4f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.5f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.5f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.4f, 0.2f, 0.0f,	0.55f, 0.788f,0.4f,
		0.5f, 0.2f, 0.0f,	0.55f, 0.788f,0.4f,
		0.4f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.4f, 0.7f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.7f, 0.0f,	0.55f, 0.788f,0.4f,
		0.4f, 0.7f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.4f, 0.5f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.5f, 0.0f,	0.55f, 0.788f,0.4f,
		0.4f, 0.4f, 0.0f,	0.55f, 0.788f,0.4f,
		0.4f, 0.4f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.5f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.4f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.5f, 0.0f,	0.55f, 0.788f,0.4f,
		0.7f, 0.5f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.8f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.7f, 0.8f, 0.0f,	0.55f, 0.788f,0.4f,
		0.7f, 0.5f, 0.0f,	0.55f, 0.788f,0.4f,
	};
	MeshColor* letra_P = new MeshColor();
	letra_P->CreateMeshColor(vertices_letraP, 144);
	meshColorList.push_back(letra_P);

	GLfloat vertices_letraD[] = {
		//X		Y		Z		R	   G		B
		-0.2f, -0.2f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.2f, -0.8f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.1f, -0.2f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.2f, -0.8f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.1f, -0.2f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.1f, -0.8f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.2f, -0.2f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.2f, -0.3f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.2f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.3f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.2f, -0.3f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.2f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.2f, -0.8f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.2f, -0.7f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.7f, 0.0f,		0.75f, 0.12f, 0.89f,
		-0.2f, -0.8f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.8f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.7f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.2f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.3f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.2f, -0.3f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.7f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.8f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.2f, -0.7f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.3f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.2f, -0.3f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.7f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.1f, -0.7f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.2f, -0.3f, 0.0f,		0.75f, 0.12f, 0.89f,
		0.2f, -0.7f, 0.0f,		0.75f, 0.12f, 0.89f,
	};		
	MeshColor* letra_D = new MeshColor();
	letra_D->CreateMeshColor(vertices_letraD, 180);
	meshColorList.push_back(letra_D);

}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para rojo
	shader1->CreateFromFiles(vShaderRojo, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader(); //shader para azul
	shader2->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader para verde
	shader3->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader para cafe
	shader4->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader para verde fuerte
	shader5->CreateFromFiles(vShaderVerdeF, fShader);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();//shader para ver letras de mi nombre
	shader6->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader6);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	CreaPiramideAzul(); //índice 0 en MeshList
	CreaPiramideVerde1(); //índice 1 en MeshList
	CreaPiramideVerde2(); //índice 2 en MeshList
	CrearCuboRojo();//índice 3 en MeshList
	CrearCuboVerde(); //índice 4 en MeshList
	CrearCuboVerde2(); //índice 5 en MeshList
	CrearCuboVerde3(); //índice 6 en MeshList
	CrearCuboCafe(); //índice 7 en MeshList
	CrearCuboCafe2(); //índice 8 en MeshList
	CrearLetrasyFiguras(); //ínidice 5 en shaderList
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

		//Dibujar cubos verdes
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();
		meshList[5]->RenderMesh();
		meshList[6]->RenderMesh();

		//Dibujar pirámide azul
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Dibujar cubo rojo
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();

		//Dibujar pirámides verdes
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		meshList[2]->RenderMesh();

		//Dibujar pirámides verdes
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[7]->RenderMesh();
		meshList[8]->RenderMesh();

		//-------------Descomentar este código para ver las letras--------------------
		////Letras de mi nombre
		//shaderList[5].useShader();
		//uniformModel= shaderList[5].getModelLocation();
		//uniformProjection = shaderList[5].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();
		//meshColorList[1]->RenderMeshColor();
		//meshColorList[2]->RenderMeshColor();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}