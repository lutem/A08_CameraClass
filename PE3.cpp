#include "PE3.h"
#include <cmath>

using namespace std;

//Constructor
PE3::PE3(int argc, char** argv)
{
	init();

	//This program was written with milliseconds
	//in mind, whereas glfwGetTime returns the time
	//in seconds, so we multiply it with 1000.
	lastFrame = glfwGetTime() * 1000;
}

//This is our main update loop
void PE3::update()
{
	//Current frame's time, in milliseconds
	currentFrame = glfwGetTime() * 1000;

	//The time between our current and last frame
	float deltaF = currentFrame - lastFrame;

	//Time carried over from the previous frame:
	//timeStepsToProcess < dT
	//...
	timeStepsToProcess += deltaF;
	//...is now: 
	//timeStepsToProcess > dT

	//We're using a constant dT (60 fps).
	//If, after we're done processing our 
	//time steps, we have any time left
	//over, that carries over to the next frame.
	while (timeStepsToProcess >= deltaT)
	{
		timeStepsToProcess -= deltaT;

		if (simulationActive)


			for (int i = 0; i < NUM_BALLS; i++)
			{
				// update ball's velocity
				balls[i].vy += gravity;

				// sballs acceleration
				glm::vec3 centerPull = sBalls[i].pos;
				centerPull = glm::normalize(centerPull) * 0.009f;
				sBalls[i].vx -= centerPull[0];
				sBalls[i].vy -= centerPull[1];
				sBalls[i].vz -= centerPull[2];

				balls[i].vx *= friction;
				balls[i].vy *= friction;
				balls[i].vz *= friction;


				//Update the ball's position
				balls[i].pos.x += balls[i].vx;
				balls[i].pos.y += balls[i].vy;
				balls[i].pos.z += balls[i].vz;

				sBalls[i].pos.x += sBalls[i].vx;
				sBalls[i].pos.y += sBalls[i].vy;
				sBalls[i].pos.z += sBalls[i].vz;

				//balls
				glm::vec4 posi = glm::vec4(balls[i].pos, 1);
				posi = glm::transpose(modelMatrix) * posi;
				balls[i].pos.x = posi.x;
				balls[i].pos.y = posi.y;
				balls[i].pos.z = posi.z;
				glm::vec4 velo = glm::vec4(balls[i].vx, balls[i].vy, balls[i].vz, 1);
				velo = glm::transpose(modelMatrix) * velo;
				balls[i].vx = velo.x;
				balls[i].vy = velo.y;
				balls[i].vz = velo.z;

				// sballs
				posi = glm::vec4(sBalls[i].pos, 1);
				posi = glm::transpose(modelMatrix) * posi;
				sBalls[i].pos.x = posi.x;
				sBalls[i].pos.y = posi.y;
				sBalls[i].pos.z = posi.z;
				velo = glm::vec4(sBalls[i].vx, sBalls[i].vy, sBalls[i].vz, 1);
				velo = glm::transpose(modelMatrix) * velo;
				sBalls[i].vx = velo.x;
				sBalls[i].vy = velo.y;
				sBalls[i].vz = velo.z;

				// ball ball collision
				//balls[i].isColliding = 0;

				for (int j = 0; j < NUM_BALLS; j++) {
					if (j != i) {
						glm::vec3 diff = glm::vec3(balls[j].pos - balls[i].pos);
						if (pow((balls[j].radius + balls[i].radius), 2) > glm::dot(diff, diff)) {
							//balls[i].isColliding = 1;

							glm::vec3 w = glm::normalize(diff);

							float overlap = pow((balls[j].radius + balls[i].radius), 2) - glm::dot(diff, diff);

							// ball elastic collision code goes here
							glm::vec3 velI = glm::vec3(balls[i].vx, balls[i].vy, balls[i].vz);
							glm::vec3 velJ = glm::vec3(balls[j].vx, balls[j].vy, balls[j].vz);

							float projI = glm::dot(w, velI);
							float projJ = glm::dot(w, velJ);

							float endI = ((balls[i].mass - balls[j].mass) * projI + (balls[j].mass * 2) * projJ) / (balls[i].mass + balls[j].mass);
							float endJ = ((balls[j].mass - balls[i].mass) * projJ + (balls[i].mass * 2) * projI) / (balls[i].mass + balls[j].mass);

							glm::vec3 ortI = velI - (projI * w);
							glm::vec3 ortJ = velJ - (projJ * w);

							glm::vec3 finalI = (endI * w) + ortI;
							glm::vec3 finalJ = (endJ * w) + ortJ;

							balls[i].vx = finalI[0];
							balls[i].vy = finalI[1];
							balls[i].vz = finalI[2];

							balls[j].vx = finalJ[0];
							balls[j].vy = finalJ[1];
							balls[j].vz = finalJ[2];

							balls[i].pos -= ((float)(overlap / 2 + 0.05) * w);
							balls[j].pos += ((float)(overlap / 2 + 0.05) * w);
						}

						diff = glm::vec3(sBalls[j].pos - sBalls[i].pos);
						if (pow((sBalls[j].radius + sBalls[i].radius), 2) > glm::dot(diff, diff)) {
							//sBalls[i].isColliding = 1;

							glm::vec3 w = glm::normalize(diff);

							float overlap = pow((sBalls[j].radius + sBalls[i].radius), 2) - glm::dot(diff, diff);

							// ball elastic collision code goes here
							glm::vec3 velI = glm::vec3(sBalls[i].vx, sBalls[i].vy, sBalls[i].vz);
							glm::vec3 velJ = glm::vec3(sBalls[j].vx, sBalls[j].vy, sBalls[j].vz);

							float projI = glm::dot(w, velI);
							float projJ = glm::dot(w, velJ);

							float endI = ((sBalls[i].mass - sBalls[j].mass) * projI + (sBalls[j].mass * 2) * projJ) / (sBalls[i].mass + sBalls[j].mass);
							float endJ = ((sBalls[j].mass - sBalls[i].mass) * projJ + (sBalls[i].mass * 2) * projI) / (sBalls[i].mass + sBalls[j].mass);

							glm::vec3 ortI = velI - (projI * w);
							glm::vec3 ortJ = velJ - (projJ * w);

							glm::vec3 finalI = (endI * w) + ortI;
							glm::vec3 finalJ = (endJ * w) + ortJ;

							sBalls[i].vx = finalI[0];
							sBalls[i].vy = finalI[1];
							sBalls[i].vz = finalI[2];

							sBalls[j].vx = finalJ[0];
							sBalls[j].vy = finalJ[1];
							sBalls[j].vz = finalJ[2];

							sBalls[i].pos -= ((float)(overlap / 2 + 0.05) * w);
							sBalls[j].pos += ((float)(overlap / 2 + 0.05) * w);
						}
					}

					glm::vec3 diff = glm::vec3(sBalls[j].pos - balls[i].pos);
					if (pow((sBalls[j].radius + balls[i].radius), 2) > glm::dot(diff, diff)) {
						//sBalls[i].isColliding = 1;

						glm::vec3 w = glm::normalize(diff);

						float overlap = pow((sBalls[j].radius + balls[i].radius), 2) - glm::dot(diff, diff);

						// ball elastic collision code goes here
						glm::vec3 velI = glm::vec3(balls[i].vx, balls[i].vy, balls[i].vz);
						glm::vec3 velJ = glm::vec3(sBalls[j].vx, sBalls[j].vy, sBalls[j].vz);

						float projI = glm::dot(w, velI);
						float projJ = glm::dot(w, velJ);

						float endI = ((balls[i].mass - sBalls[j].mass) * projI + (sBalls[j].mass * 2) * projJ) / (balls[i].mass + sBalls[j].mass);
						float endJ = ((sBalls[j].mass - balls[i].mass) * projJ + (balls[i].mass * 2) * projI) / (balls[i].mass + sBalls[j].mass);

						glm::vec3 ortI = velI - (projI * w);
						glm::vec3 ortJ = velJ - (projJ * w);

						glm::vec3 finalI = (endI * w) + ortI;
						glm::vec3 finalJ = (endJ * w) + ortJ;

						balls[i].vx = finalI[0];
						balls[i].vy = finalI[1];
						balls[i].vz = finalI[2];

						sBalls[j].vx = finalJ[0];
						sBalls[j].vy = finalJ[1];
						sBalls[j].vz = finalJ[2];

						balls[i].pos -= ((float)(overlap / 2 + 0.05) * w);
						sBalls[j].pos += ((float)(overlap / 2 + 0.05) * w);
					}
				}

				//This part just inverts the normal component of a ball's velocity if it's touching
				//one of the walls of our cube
				if (balls[i].pos.x < -STAGE_WIDTH / 2. + balls[i].radius)
				{
					balls[i].pos.x = -STAGE_WIDTH / 2. + balls[i].radius;
					balls[i].vx *= -1;
				}
				else if (balls[i].pos.x > STAGE_WIDTH / 2. - balls[i].radius)
				{
					balls[i].pos.x = STAGE_WIDTH / 2. - balls[i].radius;
					balls[i].vx *= -1;
				}

				if (balls[i].pos.y < -STAGE_HEIGHT / 2. + balls[i].radius)
				{
					balls[i].pos.y = -STAGE_HEIGHT / 2. + balls[i].radius;
					balls[i].vy *= -1;
				}
				else if (balls[i].pos.y > STAGE_HEIGHT / 2. - balls[i].radius)
				{
					balls[i].pos.y = STAGE_HEIGHT / 2. - balls[i].radius;
					balls[i].vy *= -1;
				}

				if (balls[i].pos.z < -STAGE_DEPTH / 2. + balls[i].radius)
				{
					balls[i].pos.z = -STAGE_DEPTH / 2. + balls[i].radius;
					balls[i].vz *= -1;
				}
				else if (balls[i].pos.z > STAGE_DEPTH / 2. - balls[i].radius)
				{
					balls[i].pos.z = STAGE_DEPTH / 2. - balls[i].radius;
					balls[i].vz *= -1;
				}
				// sBalls
				if (sBalls[i].pos.x < -STAGE_WIDTH / 2. + sBalls[i].radius)
				{
					sBalls[i].pos.x = -STAGE_WIDTH / 2. + sBalls[i].radius;
					sBalls[i].vx *= -1;
				}
				else if (sBalls[i].pos.x > STAGE_WIDTH / 2. - sBalls[i].radius)
				{
					sBalls[i].pos.x = STAGE_WIDTH / 2. - sBalls[i].radius;
					sBalls[i].vx *= -1;
				}

				if (sBalls[i].pos.y < -STAGE_HEIGHT / 2. + sBalls[i].radius)
				{
					sBalls[i].pos.y = -STAGE_HEIGHT / 2. + sBalls[i].radius;
					sBalls[i].vy *= -1;
				}
				else if (sBalls[i].pos.y > STAGE_HEIGHT / 2. - sBalls[i].radius)
				{
					sBalls[i].pos.y = STAGE_HEIGHT / 2. - sBalls[i].radius;
					sBalls[i].vy *= -1;
				}

				if (sBalls[i].pos.z < -STAGE_DEPTH / 2. + sBalls[i].radius)
				{
					sBalls[i].pos.z = -STAGE_DEPTH / 2. + sBalls[i].radius;
					sBalls[i].vz *= -1;
				}
				else if (sBalls[i].pos.z > STAGE_DEPTH / 2. - sBalls[i].radius)
				{
					sBalls[i].pos.z = STAGE_DEPTH / 2. - sBalls[i].radius;
					sBalls[i].vz *= -1;
				}

				// balls
				posi = glm::vec4(balls[i].pos, 1);
				posi = modelMatrix * posi;
				balls[i].pos.x = posi.x;
				balls[i].pos.y = posi.y;
				balls[i].pos.z = posi.z;
				velo = glm::vec4(balls[i].vx, balls[i].vy, balls[i].vz, 1);
				velo = modelMatrix * velo;
				balls[i].vx = velo.x;
				balls[i].vy = velo.y;
				balls[i].vz = velo.z;

				// sballs
				posi = glm::vec4(sBalls[i].pos, 1);
				posi = modelMatrix * posi;
				sBalls[i].pos.x = posi.x;
				sBalls[i].pos.y = posi.y;
				sBalls[i].pos.z = posi.z;
				velo = glm::vec4(sBalls[i].vx, sBalls[i].vy, sBalls[i].vz, 1);
				velo = modelMatrix * velo;
				sBalls[i].vx = velo.x;
				sBalls[i].vy = velo.y;
				sBalls[i].vz = velo.z;
				
			}

	}

	lastFrame = currentFrame;
}

void PE3::init()
{
	glClearColor(0.4f, 0.4f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	//The cube's initial orientation
	//(an identity matrix)
	modelMatrix = glm::mat4();

	//Lets load our .obj!
	//Our vertices will be in sphere[0].mesh.positions
	//Our indices will be in sphere[0].mesh.indices
	std::string error = tinyobj::LoadObj(sphere, "sphere.obj");

	if (error.size() > 0)
		printf("Error: %s", error.c_str());

	//Laying pipes like a plumber
	//(Initialize rendering pipeline)
	initPipeline();

#pragma region Camera init
	//Initialize the view matrix
	myCam = CameraClass();
	myCam.SetPosition(cameraTrans);
	
	radius = 42.0f;
	centerCam = 0.0f;
	//phi = 90.0f;
	//theta = 0.0f;

	//glm::vec3 camPos = glm::vec3(radius * sin(glm::radians(phi)) * sin(glm::radians(theta)), radius * cos(glm::radians(phi)), radius * sin(glm::radians(phi))*cos(glm::radians(theta)));

	// cout << camPos[0] << " " << camPos[1] << " " << camPos[2];

	myCam.SetPosition(glm::vec3(0.0f, 0.0f, radius));
	myCam.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
#pragma endregion

	gravity = -0.005f;
	friction = 0.9995f;

	//Prepare our perspective matrix
	//This is our FOV
	//float angle = 45.0f;
	//Aspect ratio = Screen Width/ Screen Height
	//float imageAspectRatio = 500.0f / 500.0f;
	//float n = 0.1f;//near
	//float f = 100.0f;//far

	//Actually create the perspective matrix using the previously calculated values
	//projMatrix = glm::perspective(angle, imageAspectRatio, n, f);


	/*
	Load our initial model, perspective, and view matrices onto the GPU:

	(Uniform variables are variables on the GPU that are set by the user
	from outside the gpu. This is data you're free to "upload"to the GPU
	whenever you wish.)

	The "locations" correspond to actual locations on the GPU where your
	variable will live. In the case of this example, we're specifically
	stating that we will be loading matrices onto the GPU (evidenced by
	the Matrix4fv part of glUniformMatrix4fv, signifying that we're loading
	a 4x4 matrix comprising of floats). The 1 is the amount of matrices we're
	loading into the variable, and the following boolean controls whether
	the matrix is transposed or not.
	*/
	glUniformMatrix4fv(projLocation, 1, false, glm::value_ptr(myCam.getProjMat(false)));
	glUniformMatrix4fv(modelLocation, 1, false, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewLocation, 1, false, glm::value_ptr(myCam.getViewMat()));

	float random;

	srand(time(0));

	//Here we create the balls that are to be jumping around in our cube
	//We use random values for their starting speeds and sizes
	for (int i = 0; i < NUM_BALLS; i++)
	{
		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].pos.x = random*STAGE_WIDTH / 2.;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		sBalls[i].pos.x = random*STAGE_WIDTH / 2.;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].pos.y = random*STAGE_HEIGHT / 2.;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		sBalls[i].pos.y = random*STAGE_HEIGHT / 2.;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].pos.z = random*STAGE_DEPTH / 2.;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		sBalls[i].pos.z = random*STAGE_DEPTH / 2.;

		random = ((rand() / (GLfloat)RAND_MAX)) + 0.2;
		balls[i].radius = random * 2;

		random = ((rand() / (GLfloat)RAND_MAX)) + 0.2;
		sBalls[i].radius = random * 2;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].vx = MAX_SPEED*random;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		sBalls[i].vx = MAX_SPEED*random;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].vy = MAX_SPEED*random;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		sBalls[i].vy = MAX_SPEED*random;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		balls[i].vz = MAX_SPEED*random;

		random = (((rand() / (GLfloat)RAND_MAX) * 2.0f) - 1);
		sBalls[i].vz = MAX_SPEED*random;

		balls[i].isColliding = 0;

		balls[i].mass = 4 / 3 * M_PI * pow(balls[i].radius, 3);
		sBalls[i].mass = 4 / 3 * M_PI * pow(sBalls[i].radius, 3);
	}
}

void PE3::initPipeline()
{
	//Our OpenGL "program"
	//stores and links our compiled
	//shaders.
	program = glCreateProgram();

	//Set up our shaders!
	//Vertex shaders deal with the 
	//vertices of every object
	initShader(GL_VERTEX_SHADER, "vertex.glsl", program);

	//Fragment shaders deal with
	//the colours of each pixel
	initShader(GL_FRAGMENT_SHADER, "fragment.glsl", program);

	//Linking the program
	//creates executables
	//for our two shaders.
	//Also initializes all
	//uniform variables'
	//locations
	glLinkProgram(program);

	//Initialize our buffers
	//We will be using buffers to send our vertex information
	//(from our loaded .obj file, which is stored in vertex<> shapes
	initBuffers();

	//We need to get the location for our matrix variables after
	//the program has been linked.
	projLocation = glGetUniformLocation(program, "proj");//The perspective (projection) matrix
	modelLocation = glGetUniformLocation(program, "model");//The model matrix (the teapot)
	viewLocation = glGetUniformLocation(program, "view");//The view matrix (the camera)
	boolLocation = glGetUniformLocation(program, "collision");//The bool controlling the sphere's colour

	glUseProgram(program);
}

void PE3::initBuffers()
{
	//If anything in this section needs further explaining,
	//feel free to consult the comments in the previous example's
	//initBuffers() function

	vertexAttribLocation = glGetAttribLocation(program, "vertex_in");
	checkGLErrors("Query vertex attribute location");

	//Cube First
	//VAO
	glGenVertexArrays(1, &cubeVAOLocation);
	glBindVertexArray(cubeVAOLocation);
	/* -- Everything after this point will be recorded into our cube's VAO -- */

	//Set up the index buffer for our cube
	glGenBuffers(1, &cubeIBOLocation);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBOLocation);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(GLuint), &cubeIndices[0], GL_STATIC_DRAW);

	//Set up the vertex buffer for our cube
	glGenBuffers(1, &cubeVBOLocation);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOLocation);
	glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), &cube[0], GL_STATIC_DRAW);

	glVertexAttribPointer(vertexAttribLocation, 3, GL_FLOAT, 0, 0, 0);
	//Enable our VAO for reading, our last step for this VAO!
	glEnableVertexAttribArray(vertexAttribLocation);
	checkGLErrors("Cube buffers");

	//Now lets do the same for the sphere!
	//Notice how it gets its own VAO? Check out display()
	//to see how we're using it.
	glGenVertexArrays(1, &sphereVAOLocation);
	glBindVertexArray(sphereVAOLocation);
	/* -- Everything after this point will be  recorded into our sphere's VAO -- */
	glGenBuffers(1, &sphereIBOLocation);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBOLocation);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere[0].mesh.indices.size() * sizeof(GLuint), &sphere[0].mesh.indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &sphereVBOLocation);
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBOLocation);
	glBufferData(GL_ARRAY_BUFFER, sphere[0].mesh.positions.size() * 3 * sizeof(float), &sphere[0].mesh.positions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(vertexAttribLocation, 3, GL_FLOAT, 0, 0, 0);
	//Enable VAO for reading
	glEnableVertexAttribArray(vertexAttribLocation);
	checkGLErrors("Sphere buffers");

	//If anything in this section confused you, look here for further information:
	// http://www.opengl.org/wiki/Vertex_Array_Object

	//Lets clean up after ourselves...
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(program);
	checkGLErrors("Use program");
}

//In our current version of OpenGL (3.3 for this demo) we have to
//manually query for gl errors. In versions 4.3 and above, however,
//it's possible to add this function as a callback for whenever
//an error occurs. For more info see: https://www.opengl.org/wiki/Debug_Output
bool PE3::checkGLErrors(const char* description)
{
	GLenum error = glGetError();
	bool hadError = false;

	while (error != GL_NO_ERROR)
	{
		printf("[ERROR]@[%s]: %s\n", description, gluErrorString(error));
		error = glGetError();
		hadError = true;
	}

	return hadError;
}

bool PE3::initShader(GLenum type, std::string file, GLuint program)
{
	//Lets create a shader object on the GPU
	GLuint shader = glCreateShader(type);
	checkGLErrors("initShader: created shader");

	std::string source;

	if (!readFile(file, &source))
	{
		printf("ERROR: Could not read file %s", file.c_str());
	}

	//The string containing our shader's text
	GLchar const *shader_source = source.c_str();

	//Lets set it so that the shader stored at the location
	//entitled "shader" will be 
	glShaderSource(shader, 1, &shader_source, NULL);
	checkGLErrors("initShader: set shader source");

	glCompileShader(shader);
	checkGLErrors("initShader: compiled shader");

	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		printf("ERROR: Unable to compile shader %d!\n\nSource:\n%s\n", shader, source.c_str());
		int infoLength = 0;
		int maxL = infoLength;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxL);
		char* infoLog = new char[maxL];

		glGetProgramInfoLog(program, maxL, &infoLength, infoLog);
		//if (infoLength > 0)
		printf("GLPROGRAMIV:%s\n", infoLog);

		glDeleteShader(shader);
		shader = 0;
	}

	glAttachShader(program, shader);
	checkGLErrors("initShader: attached shader");

	return true;
}

//Just a generic function for reading a file!
bool PE3::readFile(std::string filename, std::string* target)
{
	std::ifstream shaderSource(filename.c_str());

	target->assign((std::istreambuf_iterator< char >(shaderSource)), std::istreambuf_iterator< char >());

	if (target->length() > 0)
		return true;

	return false;
}

void PE3::display()
{
	//Clears the color and depth buffers.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int i = 0;


	//Load the view matrix onto the shader 
	glUniformMatrix4fv(viewLocation, 1, false, value_ptr(myCam.getViewMat()));

	//Load the model matrix for the cube
	glUniformMatrix4fv(modelLocation, 1, false, value_ptr(modelMatrix));
	glUniform1i(boolLocation, 0);

	//Cube
	//Look ma, no buffers!
	//(Since we set up a Vertex Array Object when setting up our buffers, all we 
	//have to do is load the vertex array to have access to the buffers' "state"
	//which we previously setup. See initBuffers() for more)
	glBindVertexArray(cubeVAOLocation);
	glDrawElements(GL_LINE_STRIP, elements, GL_UNSIGNED_INT, NULL);

	//Sphere
	glBindVertexArray(sphereVAOLocation);

	glLineWidth(.5);

	//Each ball has its own position in the world,
	//so we're using a unique matrix for each ball.
	glm::mat4 ballMatrix;

	for (i = 0; i < NUM_BALLS; i++)
	{

		//Reset the matrix to the identity matrix
		ballMatrix = glm::mat4();

		//Translate it
		ballMatrix = glm::translate(ballMatrix, balls[i].pos);

		//Scale it (since a ball's default radius is 1, we can just
		//treat its radius as its scale!)
		ballMatrix = glm::scale(ballMatrix, glm::vec3(balls[i].radius));

		//Send it to the GPU
		glUniformMatrix4fv(modelLocation, 1, false, glm::value_ptr(ballMatrix));

		

		//Update the colour boolean
		/*if (balls[i].isColliding == 0)
			glUniform1i(boolLocation, 0);
		else {
			glUniform1i(boolLocation, 1);
		}*/

		glUniform1i(boolLocation, balls[i].isColliding);

		//Draw the ball
		glDrawElements(GL_LINES, sphere[0].mesh.indices.size(), GL_UNSIGNED_INT, NULL);

		// balls[i].isColliding = 0;
	}

	for (i = 0; i < NUM_BALLS; i++)
	{

		//Reset the matrix to the identity matrix
		ballMatrix = glm::mat4();

		//Translate it
		ballMatrix = glm::translate(ballMatrix, sBalls[i].pos);

		//Scale it (since a ball's default radius is 1, we can just
		//treat its radius as its scale!)
		ballMatrix = glm::scale(ballMatrix, glm::vec3(sBalls[i].radius));

		//Send it to the GPU
		glUniformMatrix4fv(modelLocation, 1, false, glm::value_ptr(ballMatrix));



		//Update the colour boolean
		/*if (balls[i].isColliding == 0)
		glUniform1i(boolLocation, 0);
		else {
		glUniform1i(boolLocation, 1);
		}*/

		glUniform1i(boolLocation, 6);

		//Draw the ball
		glDrawElements(GL_LINES, sphere[0].mesh.indices.size(), GL_UNSIGNED_INT, NULL);
	}

	glBindVertexArray(0);
	glFlush();
}

void PE3::reshape(int w, int h)
{
	//Prepare our perspective matrix
	//This is our FOV
	float angle = 45.0f;
	//Aspect ratio = Screen Width/ Screen Height
	float imageAspectRatio = (float)w / (float)h;
	float n = 0.1f;//near
	float f = 100.0f;//far

	//Actually create the perspective matrix using the previously calculated values
	projMatrix = glm::perspective(angle, imageAspectRatio, n, f);
	glUniformMatrix4fv(projLocation, 1, false, glm::value_ptr(projMatrix));
	glViewport(0, 0, w, h);
}

void PE3::keyboard(int key, int scancode, int action, int mods)
{
	//Sanity check
	if (action != GLFW_PRESS && action != GLFW_REPEAT)
		return;

	if (mods == GLFW_MOD_SHIFT)
		caps = !caps;

	switch (key)
	{


#pragma region Camera Controls
	case GLFW_KEY_W:
		myCam.MoveForwBack(-0.05f);
		break;
	case GLFW_KEY_S:
		myCam.MoveForwBack(0.05f);
		break;
	case GLFW_KEY_A:
		myCam.MoveLeftRight(-0.05f);
		break;
	case GLFW_KEY_D:
		myCam.MoveLeftRight(0.05f);
		break;
	case GLFW_KEY_Q:
		myCam.MoveUpDown(0.5f);
		break;
	case GLFW_KEY_E:
		myCam.MoveUpDown(-0.5f);
		break;
#pragma endregion


	case GLFW_KEY_CAPS_LOCK:
		caps = !caps;
		break;

	// p to pause
	case GLFW_KEY_P:
		simulationActive = !simulationActive;
		break;

	default:
		break;
	}

	if (mods == GLFW_MOD_SHIFT)
		caps = !caps;
}

PE3::~PE3()
{
	glDeleteProgram(program);

	for (int i = 0; i < shaders.size(); i++)
		glDeleteShader(shaders[i]);
}
