#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    ID = 0;
    std::ifstream VertexFile(vertexPath);
    std::ifstream FragmentFile(fragmentPath);
    if (!VertexFile.is_open()||!FragmentFile.is_open()) {
        std::cout << "Error open vertex or fragment shaders files!!!\n";
    }
    else {
        std::stringstream sVertexStream, sFragmentStream;
        
        // read file's buffer contents into streams
        sVertexStream << VertexFile.rdbuf();
        sFragmentStream << FragmentFile.rdbuf();

        VertexFile.close();
        FragmentFile.close();

        std::string sVertex = sVertexStream.str(), sFragment = sFragmentStream.str();

        const char* VertexCode = sVertex.c_str(); //???????
        const char* FragmentCode = sFragment.c_str(); //???????

        //--------------------------------------------------------------------------------------
        unsigned int vertex, fragment; //id object buffers
        int success; //indication
        char infoLogBuff[512];

        // make vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &VertexCode, NULL);
        glCompileShader(vertex);

        //------------------ print compile errors if any ------------------------
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLogBuff);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogBuff << std::endl;
        }

        // make fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &FragmentCode, NULL);
        glCompileShader(fragment);

        //-------------------- print compile errors if any ------------------------
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLogBuff);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogBuff << std::endl;
        }

        //---------------------------------------------------------------------------------
        ID = glCreateProgram(); 

        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        //--------------------- print linking errors if any -------------------------
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLogBuff);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogBuff << std::endl;
        }

        //delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    GLint buff = glGetUniformLocation(ID, name.c_str());
    if(buff != -1){
        glUniform1i(buff, (int)value);
    }
    else {
        std::cout << "Error, could not find \"" << name << "\" in shader programs!\n";
    }
}

void Shader::setInt(const std::string& name, int value) const {
    GLint buff = glGetUniformLocation(ID, name.c_str());
    if(buff != -1){
        glUniform1i(buff, value);
    }
    else {
        std::cout << "Error, could not find \"" << name << "\" in shader programs!\n";
    }
}

void Shader::setFloat(const std::string& name, float value) const {
    GLint buff = glGetUniformLocation(ID, name.c_str());
    if(buff != -1){
        glUniform1f(buff, value);
    }
    else {
        std::cout << "Error, could not find \"" << name << "\" in shader programs!\n";
    }
}
