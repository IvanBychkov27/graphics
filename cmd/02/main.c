// OpenGL. 2 - Рисуем треугольник.
// https://www.youtube.com/watch?v=PwKA9msNIKg&list=PLOMmu5g25xfUUk6dFM-0DZENdVkpC2Tdv&index=2
// gcc main.c -o main -lglut -lGL -lGLEW  - компиляция
//  ./main  - запуск

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

GLuint prog;
GLuint vbo;

char *readFile(const char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (!f) {
        perror("fopen failed");
        exit(1);
    }
    if (fseek(f, 0, SEEK_END) == -1) {
        perror("fseek failed");
        exit(1);
    }
    long len = ftell(f);
    if (len == -1) {
        perror("ftell failed");
        exit(1);
    }
    if (fseek(f, 0, SEEK_SET) == -1) {
        perror("fseek failed");
        exit(1);
    }
    char *res = malloc(len + 1);
    if (!res) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    if (fread(res, 1, len, f) != (size_t)len) {
        fprintf(stderr, "fread failed for file %s\n", fileName);
        exit(1);
    }
    if (fclose(f) == EOF) {
        perror("fclose failed");
        exit(1);
    }
    res[len] = 0;
    return res;
}

GLuint createShader(const char *shaderFile, GLenum shaderType) {
    const char *strShaderType;
    if (shaderType == GL_VERTEX_SHADER) {
        strShaderType = "vertex";
    } else if (shaderType == GL_GEOMETRY_SHADER) {
        strShaderType = "geometry";
    } else if (shaderType == GL_FRAGMENT_SHADER) {
        strShaderType = "fragment";
    } else {
        fprintf(stderr, "Unrecognized shader type\n");
        exit(1);
    }
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        fprintf(stderr, "Error creating shader of type %s\n", strShaderType);
        exit(1);
    }
    GLchar *content = readFile(shaderFile);
    glShaderSource(shader, 1, (const GLchar **) &content, NULL);
    free(content);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        GLchar *info = malloc(sizeof(GLchar) * (infoLen + 1));
        glGetShaderInfoLog(shader, infoLen, NULL, info);
        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, info);
        exit(1);
    }
    return shader;
}

void createProg(GLuint *shaders, int len) {
    int i = 0;
    prog = glCreateProgram();
    if (!prog) {
        fprintf(stderr, "Failed to create shader program\n");
        exit(1);
    }
    for (; i < len; i++) {
        glAttachShader(prog, shaders[i]);
    }
    glLinkProgram(prog);
    GLint status;
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLen;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLen);
        GLchar *info = malloc(sizeof(GLchar) * (infoLen + 1));
        glGetProgramInfoLog(prog, infoLen, NULL, info);
        fprintf(stderr, "Linker failure: %s\n", info);
        exit(1);
    }
}

void createBuffer();

void init() {
    createBuffer();

    GLuint shaders[] = {
        createShader("shader.vs", GL_VERTEX_SHADER),
        createShader("shader.fs", GL_FRAGMENT_SHADER)
    };
    int len = sizeof(shaders) / sizeof(shaders[0]);
    createProg(shaders, len);
    int i = 0;
    for (; i < len; i++) {
        glDeleteShader(shaders[i]);
    }
}

void createBuffer() {
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void display() {
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(prog);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(300, 200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My second window");

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(res));
        return 1;
    }
    printf("GL version: %s\n", glGetString(GL_VERSION));

    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}