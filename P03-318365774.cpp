//práctica 3: Modelado Geométrico y Cámara Sintética.
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
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include"Sphere.h"
#include"Window.h"
#include"Camera.h"
//tecla E: Rotar sobre el eje X
//tecla R: Rotar sobre el eje Y
//tecla T: Rotar sobre el eje Z


using std::vector;

//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
const float PI = 3.14159265f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
Camera camera;
Window mainWindow;
vector<Mesh*> meshList;
vector<MeshColor*> meshColorList;
vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
Sphere sp = Sphere(1.0, 50, 50); //recibe radio, slices, stacks

// Pyraminx: Tetraedro regular
void CrearPyramix()
{
	unsigned int indices_pyramix[] = {
		0, 1, 2, // Cara 1
		0, 1, 3, // Cara 2
		1, 2, 3, // Cara 3
		2, 0, 3  // Cara 4
	};

	GLfloat vertices_pyramix[] = {
		// Coordenadas de los vértices
		0.0f, 0.5f, 0.0f,  // Vértice superior
		-0.5f, -0.5f, 0.5f, // Vértice 1 (base)
		0.5f, -0.5f, 0.5f,  // Vértice 2 (base)
		0.0f, -0.5f, -0.5f  // Vértice 3 (base)
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices_pyramix, indices_pyramix, 12, 12);
	meshList.push_back(obj1);
}

void CrearPyraR()
{
	unsigned int indices_pyramix[] = {
		0, 1, 2, // Cara 1
		0, 1, 3, // Cara 2
		1, 2, 3, // Cara 3
		2, 0, 3  // Cara 4
	};

	GLfloat vertices_pyramix[] = {
		// Coordenadas de los vértices
		0.0f, 0.45f, 0.05f,  // Vértice superior
		-0.45f, -0.45f, 0.505f, // Vértice 1 (base)
		0.45f, -0.45f, 0.505f,  // Vértice 2 (base)
		0.0f, -0.45f, 0.0f  // Vértice 3 (base)
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices_pyramix, indices_pyramix, 12, 12);
	meshList.push_back(obj1);
}

void CrearPyraV()
{
	unsigned int indices_pyramix[] = {
		0, 1, 2, // Cara 1
		0, 1, 3, // Cara 2
		1, 2, 3, // Cara 3
		2, 0, 3  // Cara 4
	};

	GLfloat vertices_pyramix[] = {
		// Coordenadas de los vértices
		-0.02f, 0.45f, 0.0f,  // Vértice superior
		-0.485f, -0.45f, 0.45f, // Vértice 1 (base)
		-0.1f, -0.45f, 0.0f,  // Vértice 2 (base)
		-0.05f, -0.45f, -0.45f  // Vértice 3 (base)
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices_pyramix, indices_pyramix, 12, 12);
	meshList.push_back(obj1);
}

void CrearPyraAz()
{
	unsigned int indices_pyramix[] = {
		0, 1, 2, // Cara 1
		0, 1, 3, // Cara 2
		1, 2, 3, // Cara 3
		2, 0, 3  // Cara 4
	};

	GLfloat vertices_pyramix[] = {
		// Coordenadas de los vértices
		0.02f, 0.45f, 0.0f,  // Vértice superior
		0.485f, -0.45f, 0.45f, // Vértice 1 (base)
		0.1f, -0.45f, 0.0f,  // Vértice 2 (base)
		0.05f, -0.45f, -0.45f  // Vértice 3 (base)
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices_pyramix, indices_pyramix, 12, 12);
	meshList.push_back(obj1);
}

void CrearPyraAm()
{
	unsigned int indices_pyramix[] = {
		0, 1, 2, // Cara 1
		0, 1, 3, // Cara 2
		1, 2, 3, // Cara 3
		2, 0, 3  // Cara 4
	};

	GLfloat vertices_pyramix[] = {
		// Coordenadas de los vértices
		0.0f, 0.0f, 0.0f,  // Vértice superior
		-0.47f, -0.505f, 0.47f, // Vértice 1 (base)
		0.47f, -0.505f, 0.47f,  // Vértice 2 (base)
		0.0f, -0.505f, -0.45f  // Vértice 3 (base)
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices_pyramix, indices_pyramix, 12, 12);
	meshList.push_back(obj1);
}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

}

int main()
{
	mainWindow = Window(720, 720);
	mainWindow.Initialise();
	//Cilindro y cono reciben resolución (slices, rebanadas) y Radio de circunferencia de la base y tapa

	CrearPyramix();//índice 0 en MeshList
	CrearPyraR();//índice 1 en MeshList
	CrearPyraV();//índice 2 en MeshList
	CrearPyraAz();//índice 3 en MeshList
	CrearPyraAm();//índice 4 en MeshList
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.3f);


	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	glm::mat4 model(1.0);//Inicializar matriz de Modelo 4x4

	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f); //inicializar Color para enviar a variable Uniform;

	while (!mainWindow.getShouldClose())
	{

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		//Cámara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		model = glm::mat4(1.0);
		//Traslación inicial para posicionar en -Z a los objetos
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[0]->RenderMesh();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[1]->RenderMesh();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[2]->RenderMesh();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[3]->RenderMesh();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[4]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}
	
		