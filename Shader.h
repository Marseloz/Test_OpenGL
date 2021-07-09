#include <string>

class Shader{
private:
public:
    unsigned int ID; // the program ID

    Shader(const char* vertexPath, const char* fragmentPath);    // constructor reads and builds the shader

    void use();// use/activate the shader

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};