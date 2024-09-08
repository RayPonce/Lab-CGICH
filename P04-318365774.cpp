/*Pr�ctica 4: Modelado Jer�rquico.
Se implementa el uso de matrices adicionales para almacenar informaci�n de transformaciones geom�tricas que se quiere
heredar entre diversas instancias para que est�n unidas
Teclas de la F a la K para rotaciones de articulaciones
*/
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
//clases para dar orden y limpieza al c�digo
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
vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
Sphere sp = Sphere(1.0, 20, 20); //recibe radio, slices, stacks

void CrearCubo()
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
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

//funci�n para crear pir�mide cuadrangular unitaria
void CrearPiramideCuadrangular()
{
	vector<unsigned int> piramidecuadrangular_indices = {
		0,3,4,
		3,2,4,
		2,1,4,
		1,0,4,
		0,1,2,
		0,2,4

	};
	vector<GLfloat> piramidecuadrangular_vertices = {
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f,
	};
	Mesh* piramide = new Mesh();
	piramide->CreateMeshGeometry(piramidecuadrangular_vertices, piramidecuadrangular_indices, 15, 18);
	meshList.push_back(piramide);
}

//Crear cilindro
void CrearCilindro(int res, float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//c�lculo del paso interno en la circunferencia y variables que almacenar�n cada coordenada de cada v�rtice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;

	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//ciclo for para crear los v�rtices de las paredes del cilindro
	for (n = 0; n <= (res); n++) {
		if (n != res) {
			x = R * cos((n)*dt);
			z = R * sin((n)*dt);
		}
		//caso para terminar el c�rculo
		else {
			x = R * cos((0) * dt);
			z = R * sin((0) * dt);
		}
		for (i = 0; i < 6; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			case 3:
				vertices.push_back(x);
				break;
			case 4:
				vertices.push_back(0.5);
				break;
			case 5:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia inferior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(-0.5f);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia superior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(0.5);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//Se generan los indices de los v�rtices
	for (i = 0; i < vertices.size(); i++) indices.push_back(i);

	//se genera el mesh del cilindro
	Mesh* cilindro = new Mesh();
	cilindro->CreateMeshGeometry(vertices, indices, vertices.size(), indices.size());
	meshList.push_back(cilindro);
}

//funci�n para crear un cono
void CrearCono(int res, float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//c�lculo del paso interno en la circunferencia y variables que almacenar�n cada coordenada de cada v�rtice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;

	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//caso inicial para crear el cono
	vertices.push_back(0.0);
	vertices.push_back(0.5);
	vertices.push_back(0.0);

	//ciclo for para crear los v�rtices de la circunferencia del cono
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}
	vertices.push_back(R * cos(0) * dt);
	vertices.push_back(-0.5);
	vertices.push_back(R * sin(0) * dt);


	for (i = 0; i < res + 2; i++) indices.push_back(i);

	//se genera el mesh del cono
	Mesh* cono = new Mesh();
	cono->CreateMeshGeometry(vertices, indices, vertices.size(), res + 2);
	meshList.push_back(cono);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//Cilindro y cono reciben resoluci�n (slices, rebanadas) y Radio de circunferencia de la base y tapa

	CrearCubo();//�ndice 0 en MeshList
	CrearPiramideCuadrangular(); //�nidce 1 en MeshList
	CrearCilindro(50, 1.0f); //�ndice 2 en MeshList
	CrearCono(25, 2.0f); //�ndice 3 en MeshList
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.2f, 0.2f);
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	

	//Loop mientras no se cierra la ventana
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader

	glm::mat4 model(1.0);//Inicializar matriz de Modelo 4x4
	glm::mat4 modelaux(1.0);//Inicializar matriz de Modelo 4x4 auxiliar para la jerarqu�a

	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f); //inicializar Color para enviar a variable Uniform;

	while (!mainWindow.getShouldClose())
	{

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		//C�mara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		//para reiniciar la matriz de modelo con valor de la matriz identidad
		model = glm::mat4(1.0);
		
		//Llantas
		//llanta 1
		modelaux = model;
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, -1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//dibujar un cilindro
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMeshGeometry();
		model = modelaux;
		//llanta 2
		modelaux = model;
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//dibujar un cilindro
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMeshGeometry();
		model = modelaux;
		//llanta 3
		modelaux = model;
		model = glm::translate(model, glm::vec3(-1.5f, 0.5f, -1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion6()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//dibujar un cilindro
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMeshGeometry();
		model = modelaux;
		//llanta 4
		modelaux = model;
		model = glm::translate(model, glm::vec3(-1.5f, 0.5f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion7()), glm::vec3(0.0f, 0.0f, 1.0f)); //Presionar tecla P para girar
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//dibujar un cilindro
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMeshGeometry();
		model = modelaux;

		//Base gr�a
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(4.0f, 3.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[1]->RenderMesh(); //dibuja cubo y pir�mide triangular

		model = modelaux;

		//Cuerpo de la gr�a
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(4.0f, 3.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular

		model = modelaux;

		// SE EMPIEZA EL DIBUJO DEL BRAZO
		//articulaci�n 1
		//rotaci�n alrededor de la articulaci�n que une con la cabina
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		//dibujar una peque�a esfera
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();
		model = modelaux;


		model = glm::translate(model, glm::vec3(-2.0f, 2.0f, 0.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(5.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la l�nea de proyecci�n solo se manda una vez a menos que en tiempo de ejecuci�n
		//se programe cambio entre proyecci�n ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[0]->RenderMesh(); //dibuja cubo, pir�mide triangular, pir�mide base cuadrangular

		//para descartar la escala que no quiero heredar se carga la informaci�n de la matrix auxiliar
		model = modelaux;
		//articulaci�n 2
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		//dibujar una peque�a esfera
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = modelaux;
		//segundo brazo
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 5.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular

		model = modelaux;

		//articulaci�n 3 
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		//dibujar una peque�a esfera
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();
		model = modelaux;

		//tercer brazo
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 5.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular

		model = modelaux;

		//articulaci�n 4 
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));
		modelaux = model;
		//dibujar una peque�a esfera
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();
		model = modelaux;

		//canasta
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular

		model = modelaux;

		/*-----------------------------------------------------------------------------------------*/
		/*-----------------------ANIMAL ROBOT 3D---------------------------------------------------*/
		/*-----------------------------------------------------------------------------------------*/
		/*--------------------Descomentar a partir de la siguiente l�nea---------------------------*/
		

		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		//
		////Patas
		////Articulaci�n 1 Pata 1
		//modelaux = model;
		//model = glm::translate(model, glm::vec3(-1.0f, -1.5f, 0.5f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		////Dibujar cubo
		//model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular
		////Articulaci�n 2 Pata 1
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f));
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		//model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh();
		//model = modelaux;
		//

		////Articulaci�n 1 Pata 2
		//modelaux = model;
		//model = glm::translate(model, glm::vec3(1.0f, -1.5f, 0.5f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f));
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		////Dibujar cubo
		//model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular
		////Articulaci�n 2 Pata 2
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f));
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		//model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh();
		//model = modelaux;

		////Articulaci�n 1 Pata 3
		//modelaux = model;
		//model = glm::translate(model, glm::vec3(-1.0f, -1.5f, -0.5f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		////Dibujar cubo
		//model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular
		////Articulaci�n 2 Pata 3
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion6()), glm::vec3(0.0f, 0.0f, 1.0f));
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		//model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh();
		//model = modelaux;

		////Articulaci�n 1 Pata 4
		//modelaux = model;
		//model = glm::translate(model, glm::vec3(1.0f, -1.5f, -0.5f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion7()), glm::vec3(0.0f, 0.0f, 1.0f));
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		////Dibujar cubo
		//model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMeshGeometry(); //dibuja cubo y pir�mide triangular
		////Articulaci�n 2 Pata 4
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion8()), glm::vec3(0.0f, 0.0f, 1.0f)); //Presionar O
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		//model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMeshGeometry();
		//model = modelaux;

		////Cuerpo
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(4.0f, 3.0f, 2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular
		//model = modelaux;
		//
		////Articulaci�n Cola
		//modelaux = model;
		//model = glm::translate(model, glm::vec3(2.0f, 1.5f, 0.0f));
		////rotaci�n alrededor de la articulaci�n
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion9()), glm::vec3(0.0f, 1.0f, 0.0f));//Presionar tecla I
		////dibujar una peque�a esfera
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//sp.render();
		////Dibujar cono
		//model = glm::translate(model, glm::vec3(2.0f, 2.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(315.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.8f, 8.0f, 0.8f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[3]->RenderMeshGeometry(); //cono
		//model = modelaux;

		////Cabeza
		//model = glm::translate(model, glm::vec3(-2.0f, 2.0f, 0.0f));
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(2.5f, 1.0f, 2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 0.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular
		//model = modelaux;

		//model = glm::translate(model, glm::vec3(0.5f, 1.0f, 0.0f));
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(1.5f, 1.5f, 2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[0]->RenderMesh(); //dibuja cubo y pir�mide triangular
		//model = modelaux;

		//model = glm::translate(model, glm::vec3(-0.6f, 0.0f, 0.0f));//Ojos
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(0.5f, 1.0f, 2.1f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[0]->RenderMesh();
		//model = modelaux;

		//model = glm::translate(model, glm::vec3(0.5f, 1.25f, 0.4f));//Orejas
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(0.3f, 1.0f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(0.0f, 1.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		//meshList[3]->RenderMeshGeometry(); //cono
		//model = modelaux;

		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.8f));//Orejas
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(0.3f, 1.0f, 0.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[3]->RenderMeshGeometry(); //cono
		//model = modelaux;

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}
