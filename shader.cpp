#include "SFML/Render/shaders/shader.h"

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std:: cout << "Failed to compile"  <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std:: cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}



static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


	std::string vertShader =
	   	"#version 410 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main()"
		"{\n"
		"gl_Position = position;\n"
		"}\n";

	std::string fragmentShader =
	   	"#version 410 core\n"
		"\n"
		"layout(location = 0) out vec4 color;"
		"\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

void shader_run()
{
	unsigned int shader = CreateShader(vertShader, fragmentShader);
	glUseProgram(shader);
}
