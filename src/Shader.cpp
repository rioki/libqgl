// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Shader.h"

#include <stdexcept>
#include <vector>
#include <GL/glew.h>


namespace qgl
{
//------------------------------------------------------------------------------
    Shader::Shader()
    : compiled(false) {}

//------------------------------------------------------------------------------
    Shader::~Shader()
    {
        if (compiled)
        {
            glDeleteShader(vertex_id);
            glDeleteShader(fragment_id);
            glDeleteProgram(progtam_id);
        }
    }

//------------------------------------------------------------------------------
    void Shader::set_vertex_code(const std::string& value)
    {
        vertex_code = value;
    }

//------------------------------------------------------------------------------
    const std::string& Shader::get_vertex_code() const
    {
        return vertex_code;
    }

//------------------------------------------------------------------------------
    void Shader::set_fragment_code(const std::string& value)
    {
        fragment_code = value;
    }

//------------------------------------------------------------------------------
    const std::string& Shader::get_fragment_code() const
    {
        return fragment_code;
    }

//------------------------------------------------------------------------------
    unsigned int compile_shader(unsigned int type, const std::string& code)
    {
		unsigned int id = glCreateShader(type);

		const char* str = code.c_str();
		glShaderSource(id, 1, &str, NULL);

		glCompileShader(id);

		int status = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			std::vector<char> buff(256, '\0');
			glGetShaderInfoLog(id, 256, NULL, &buff[0]);

			throw std::runtime_error(&buff[0]);
		}

		return id;
	}

//------------------------------------------------------------------------------
    void Shader::compile()
    {
        if (! compiled)
        {
            vertex_id = compile_shader(GL_VERTEX_SHADER, vertex_code);
            fragment_id = compile_shader(GL_FRAGMENT_SHADER, fragment_code);

            progtam_id = glCreateProgram();

            glAttachShader(progtam_id, vertex_id);
            glAttachShader(progtam_id, fragment_id);

            glLinkProgram(progtam_id);

            int status = 0;
            glGetProgramiv(progtam_id, GL_LINK_STATUS, &status);
            if (!status)
            {
                std::vector<char> buff(256, '\0');
                glGetShaderInfoLog(progtam_id, 256, NULL, &buff[0]);

                throw std::runtime_error(&buff[0]);
            }

            compiled = true;
        }
    }

//------------------------------------------------------------------------------
    bool Shader::is_compiled() const
    {
        return compiled;
    }

//------------------------------------------------------------------------------
    void Shader::bind() const
    {
        glUseProgram(progtam_id);
    }

//------------------------------------------------------------------------------
	void Shader::unbind() const
	{
	    glUseProgram(0);
    }

//------------------------------------------------------------------------------
	void Shader::set_uniform(const std::string& id, float value)
    {
        glUniform1f(glGetUniformLocation(progtam_id, id.c_str()), value);
    }
}
