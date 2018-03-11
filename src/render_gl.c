#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <iostream>
#include <math.h>

#define CHECK_ERROR                                             \
{                                                               \
  GLenum err = glGetError();                                    \
  if(err != GL_NO_ERROR)                                        \
    printf("Error in file %s (l. %d): %s\n",                    \
    __FILE__, __LINE__, gluErrorString(err));                   \
}

using std::string;
using std::stringstream;

static GLuint vaoQuad, *program, cubemapColor, cubemapMinMaxDepth;
static float dist = 0, exposure = 1;
static int screenWidth = 1080, screenHeight = 720;
static int cubemapSize = 2048;

static int framectr = 0;

static void reloadShaders();

void updateUniforms()
{
  glUseProgram(program[0]);
  GLint distLoc = glGetUniformLocation(program[0], "dist");
  glUniform1f(distLoc, dist);
  GLint expLoc = glGetUniformLocation(program[0], "exposure");
  glUniform1f(expLoc, exposure);
  glUseProgram(0);
}

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(key == GLFW_KEY_Q && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
    return;
  }

  if(key == GLFW_KEY_N && action & (GLFW_PRESS | GLFW_REPEAT))
    dist += 0.5;
  if(key == GLFW_KEY_H && action & (GLFW_PRESS | GLFW_REPEAT))
    dist -= 0.5;
  if(key == GLFW_KEY_J && action & (GLFW_PRESS | GLFW_REPEAT))
    exposure *= 2;
  if(key == GLFW_KEY_M && action & (GLFW_PRESS | GLFW_REPEAT))
    exposure /= 2;
  if(key == GLFW_KEY_B && action & (GLFW_PRESS | GLFW_REPEAT))
    reloadShaders();

  updateUniforms();
}

static bool drag = false;
static double prevx = 0, prevy = 0;

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(!drag)
    return;

  if(prevx == 0 && prevy == 0)
  {
    prevx = xpos;
    prevy = ypos;
    return;
  } else {
    //set rotation

    prevx = xpos;
    prevy = ypos;
  }
  updateUniforms();
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if(button == GLFW_MOUSE_BUTTON_LEFT)
  {
    drag = action;
  }
  if(!drag)
  {
    prevx = 0;
    prevy = 0;
  }
}

static void resize_callback(GLFWwindow* window, int width, int height)
{
  screenWidth = width;
  screenHeight = height;
}

static void initQuad()
{
  static float quad[] = {
    -1.f,  -1.f,
    1.f,  -1.f,
    -1.f,   1.f,
    1.f,   1.f
  };
  static float tc[] = {
    0.f,   0.f,
    1.f,   0.f,
    0.f,   1.f,
    1.f,   1.f
  };

  GLuint vertices = 0, tcs = 0;
  glGenBuffers(1, &vertices);
  glBindBuffer(GL_ARRAY_BUFFER, vertices);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), (void*)quad, GL_STATIC_DRAW);
  glGenBuffers(1, &tcs);
  glBindBuffer(GL_ARRAY_BUFFER, tcs);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), (void*)tc, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vaoQuad);
  glBindVertexArray(vaoQuad);
  glBindBuffer(GL_ARRAY_BUFFER, vertices);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, tcs);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

char *readFile(string path, int *fsize)
{
  FILE *file;
  unsigned int filesize;
  char *fileContent;

  file = fopen(path.c_str(), "rb");
  if(!file)
  {
    printf("Could not open file %s for reading.\n", path.c_str());
    return 0;
  }

  fseek(file, 0, SEEK_END);
  filesize = ftell(file);
  fseek(file, 0, SEEK_SET);

  fileContent = new char[filesize + 1];
  if(fread(fileContent, sizeof(char), filesize, file) != filesize)
  {
    printf("An error occured, reading file %s.\n", path.c_str());
    return 0;
  }

  fclose(file);
  fileContent[filesize] = '\0';

  if(fsize != 0)
    *fsize = filesize;

  return fileContent;
}

GLuint loadShader(string path, GLenum type)
{
  GLuint shaderId;

  int filesize;
  char *fileContent = readFile(path, &filesize);

  shaderId = glCreateShader(type);
  glShaderSource(shaderId, 1, (const char**)&fileContent, (const int*)&filesize);

  glCompileShader(shaderId);
  delete [] fileContent;

  GLint success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
  {
    GLint errLength;
    char *errMsg;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errLength);
    if(errLength > 1)
    {
      errMsg = new char[errLength];
      glGetShaderInfoLog(shaderId, errLength, 0, errMsg);
      printf("Error in %s:\n%s", path.c_str(), errMsg);
      if(success == GL_FALSE)
        exit(-1);
    }
  }

  return shaderId;
}

GLuint loadCompileProgram(string vsPath, string tcPath, string tePath, string gsPath, string fsPath)
{
  GLuint prog = glCreateProgram();

  if(vsPath.length() > 0)
  {
    GLuint vs = loadShader(vsPath, GL_VERTEX_SHADER);
    glAttachShader(prog, vs);
  }
  if(tcPath.length() > 0)
  {
    GLuint tcs = loadShader(tcPath, GL_TESS_CONTROL_SHADER);
    glAttachShader(prog, tcs);
  }
  if(tePath.length() > 0)
  {
    GLuint tes = loadShader(tePath, GL_TESS_EVALUATION_SHADER);
    glAttachShader(prog, tes);
  }
  if(gsPath.length() > 0)
  {
    GLuint gs = loadShader(gsPath, GL_GEOMETRY_SHADER);
    glAttachShader(prog, gs);
  }
  if(fsPath.length() > 0)
  {
    GLuint fs = loadShader(fsPath, GL_FRAGMENT_SHADER);
    glAttachShader(prog, fs);
  }

  return prog;
}

GLuint loadCompileComputeProgram(string csPath)
{
  GLuint prog = glCreateProgram();

  if(csPath.length() > 0)
  {
    GLuint cs = loadShader(csPath, GL_COMPUTE_SHADER);
    glAttachShader(prog, cs);
  }

  return prog;
}

void linkProgram(GLuint *program)
{
  GLuint prog = *program;
  glLinkProgram(prog);

  GLint success;
  glGetProgramiv(prog, GL_LINK_STATUS, &success);
  GLint errLength;
  char *errMsg;
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &errLength);
  if(errLength > 1)
  {
    errMsg = new char[errLength];
    glGetProgramInfoLog(prog, errLength, 0, errMsg);
    printf("Error while linking the shaders:\n%s", errMsg);
    if(success == GL_FALSE)
      exit(-1);
  }
}

static void initPrograms()
{
  program = new GLuint[2];    
  program[0] = loadCompileProgram("src/shader/vert.glsl", "", "", "src/shader/geom.glsl", "src/shader/frag.glsl");
  CHECK_ERROR;

  linkProgram(&program[0]);
  CHECK_ERROR;
  glUseProgram(program[0]);
  CHECK_ERROR;
  GLint cubemapLoc = glGetUniformLocation(program[0], "cubemap");
  CHECK_ERROR;
  glUniform1i(cubemapLoc, 0);
  CHECK_ERROR;
  glActiveTexture(GL_TEXTURE0);
  CHECK_ERROR;
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapColor);
  CHECK_ERROR;
  GLint minmaxdepthmapLoc = glGetUniformLocation(program[0], "minmaxdepthmap");
  CHECK_ERROR;
  glUniform1i(minmaxdepthmapLoc, 1);
  CHECK_ERROR;
  glActiveTexture(GL_TEXTURE1);
  CHECK_ERROR;
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapMinMaxDepth);
  CHECK_ERROR;
  updateUniforms();
  CHECK_ERROR;

  program[1] = loadCompileComputeProgram("src/shader/minmax.cs.glsl");
  CHECK_ERROR;
  linkProgram(&program[1]);
  CHECK_ERROR;
}

static void reloadShaders()
{
  glUseProgram(0);
  initPrograms();
}

char* readPfm(int *width, int *height, float *exposure, string path)
{
  int filesize = 0;
  char *data = readFile(path, &filesize);
  stringstream ss(data);

  string filetype;
  ss >> filetype;

  if(filetype.compare("PF"))
  {
    fprintf(stderr, "Filetype %s unknown\n", filetype.c_str());
    return data;
  }

  int w, h;
  ss >> w;
  ss >> h;

  float exp;
  ss >> exp;

  int datapos = ss.tellg();
  datapos++;

  fprintf(stderr, "Pfm-file: %s (%d x %d, %f)\n", path.c_str(), w, h, exp);
  char *ret = new char[filesize-datapos];
  memcpy(ret, data + datapos, filesize-datapos);
  delete [] data;

  if(width)
    *width = w;
  if(height)
    *height = h;
  if(exposure)
    *exposure = exp;
  return ret;
}

char* readMat(int *width, int *height, string path)
{
  int filesize = 0;
  char *data = readFile(path, &filesize);
  //8 Byte header (int width, int height)
  int w, h, datapos;
  w = *(int*)data;
  h = *(int*)(data+4);
  datapos = 8;
  fprintf(stderr, "Mat-file: %s (%d x %d)\n", path.c_str(), w, h);

  float *dat = new float[2*(filesize-datapos)/sizeof(float)];
  //swap rows and duplicate data for min-max mipmap
  for(int i = h-1; i >= 0; i--)
    for(int j = 0; j < w; j++)
      dat[2*((h-i-1)*w+j)] = dat[2*((h-i-1)*w+j)+1] = *(float*)(data+datapos+(i*w+j)*sizeof(float));
  char *ret = (char*)dat;
  delete [] data;

  if(width)
    *width = w;
  if(height)
    *height = h;

  return ret;
}

char* readPpm(int *width, int *height, int *maxVal, string path)
{
  int filesize = 0;
  char *data = readFile(path, &filesize);
  stringstream ss(data);

  string filetype;
  ss >> filetype;

  if(filetype.compare("P6"))
  {
    fprintf(stderr, "Filetype %s unknown\n", filetype.c_str());
    return data;
  }

  char dummy[256];
  while(ss.peek() != '#')
    ss.read(dummy, 1);
  //gimp comment
  ss.getline(dummy, 256);

  int w, h, m;
  ss >> w;
  ss >> h;

  ss >> m;

  int datapos = ss.tellg();
  datapos++;
  fprintf(stderr, "Ppm-file: %s (%d x %d, %d, %x) #%s\n", path.c_str(), w, h, m, ss.peek(), dummy);

  char *ret = new char[filesize-datapos];
  //swap rows
  for(int i = h-1; i >= 0; i--)
    memcpy(ret+i*w*3, data + datapos+(h-i-1)*w*3, w*3);
  delete [] data;

  if(width)
    *width = w;
  if(height)
    *height = h;
  if(maxVal)
    *maxVal = m;
  return ret;
}

static void loadCubemap()
{
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
  glGenTextures(1, &cubemapMinMaxDepth);

  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapMinMaxDepth);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, log2f(1000));

  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, 0);
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, 0);
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, 0);
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, 0);
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, 0);
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, 0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapMinMaxDepth);
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
  CHECK_ERROR;

  glGenTextures(1, &cubemapColor);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapColor);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, log2f(cubemapSize));
  CHECK_ERROR;

  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapColor);
  string path = "scenes/castle/";

  char *data;
  data = readPpm(0, 0, 0, path + "cube_image_01.ppm");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB8, cubemapSize, cubemapSize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  delete [] data;

  data = readPpm(0, 0, 0, path + "cube_image_05.ppm");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB8, cubemapSize, cubemapSize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  delete [] data;

  data = readPpm(0, 0, 0, path + "cube_image_00.ppm");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB8, cubemapSize, cubemapSize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  delete [] data;

  data = readPpm(0, 0, 0, path + "cube_image_03.ppm");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB8, cubemapSize, cubemapSize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  delete [] data;

  data = readPpm(0, 0, 0, path + "cube_image_04.ppm");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB8, cubemapSize, cubemapSize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  delete [] data;

  data = readPpm(0, 0, 0, path + "cube_image_02.ppm");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB8, cubemapSize, cubemapSize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  delete [] data;
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);


  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapMinMaxDepth);

  data = readMat(0, 0, path + "cube_depth_01.mat");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, data);
  delete [] data;

  data = readMat(0, 0, path + "cube_depth_05.mat");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, data);
  delete [] data;

  data = readMat(0, 0, path + "cube_depth_00.mat");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, data);
  delete [] data;

  data = readMat(0, 0, path + "cube_depth_03.mat");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, data);
  delete [] data;

  data = readMat(0, 0, path + "cube_depth_04.mat");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, data);
  delete [] data;

  data = readMat(0, 0, path + "cube_depth_02.mat");
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RG16F, 1000, 1000, 0, GL_RG, GL_FLOAT, data);
  delete [] data;

  CHECK_ERROR;

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

static void filterCubemapPass()
{
  glUseProgram(program[1]);
  CHECK_ERROR;
  int levels = floor(log2f(1000));

  for(int i = 0; i < levels; i++)
  {
    glBindImageTexture(0, cubemapMinMaxDepth, i, GL_TRUE, 0, GL_READ_ONLY, GL_RG16F);            
    CHECK_ERROR;
    glBindImageTexture(1, cubemapMinMaxDepth, i+1, GL_TRUE, 0, GL_READ_WRITE, GL_RG16F);
    CHECK_ERROR;
    int computeDim = 1024 / (1<<(i+1)) / 16;
    if(computeDim == 0)
      computeDim = 1;
    glDispatchCompute(computeDim, computeDim, 6);
    CHECK_ERROR;
  }
  glUseProgram(0);
  CHECK_ERROR;
}

static void renderSecondPass()
{
  glClearColor(0, 0, 0, 0);
  glViewport(0, 0, screenWidth, screenHeight);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(program[0]);
  glBindVertexArray(vaoQuad);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapColor);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapMinMaxDepth);

  GLint minDepthLoc = glGetUniformLocation(program[0], "minDepth");
  GLint maxDepthLoc = glGetUniformLocation(program[0], "maxDepth");

  glUniform1f(minDepthLoc, 0);
  glUniform1f(maxDepthLoc, 4000);
  glDrawArrays(GL_LINES_ADJACENCY, 0, 4);
}


int main(int argc, char **argv)
{
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(screenWidth, screenHeight, "Preview", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);
  glfwSetWindowSizeCallback(window, resize_callback);
  glfwSetCursorPosCallback(window, cursor_pos_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  glewExperimental = GL_TRUE;
  glewInit();
  CHECK_ERROR;
  loadCubemap();
  CHECK_ERROR;
  initQuad();
  CHECK_ERROR;
  initPrograms();
  CHECK_ERROR;

  float begin = glfwGetTime();
  do
  {
    filterCubemapPass();
    CHECK_ERROR;
    renderSecondPass();
    CHECK_ERROR;
    framectr++;
    glfwSwapBuffers(window);
    glfwPollEvents();
    float time = glfwGetTime() - begin;
    if(time > 10)
    {
      fprintf(stdout, "%d frames in %f seconds\n--> %f fps, %f ms / frame\n", framectr, time, framectr / time, 1000 * time / framectr);
      begin = glfwGetTime();
      framectr = 0;
    }
  } while(!glfwWindowShouldClose(window));

  float time = glfwGetTime() - begin;
  fprintf(stdout, "%d frames in %f seconds\n--> %f fps, %f ms / frame\n", framectr, time, framectr / time, 1000 * time / framectr);
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

