// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_SHADER_H_
#define _QGL_SHADER_H_

#include "config.h"

#include <string>
#include <tr1/memory>

namespace qgl
{
    /**
     * GLSL Shader
     *
     * The Shader class wraps and manages a GLSL shader program. A program is
     * always build up of a vertex shader and a fragment shader, even though
     * openGL may allow more complex setups.
     *
     * @todo Add more set_uniform functions.
     **/
    class QGL_EXPORT Shader
    {
    public:
        /**
         * Default Constructor
         **/
        Shader();

        /**
         * Destructor
         **/
        ~Shader();

        /**
         * Get the unique id of the shader.
         **/
        unsigned int get_id() const;

        /**
         * Set the vertex code.
         **/
        void set_vertex_code(const std::string& value);

        /**
         * Get the vertex code.
         **/
        const std::string& get_vertex_code() const;

        /**
         * Set the fragment code.
         **/
        void set_fragment_code(const std::string& value);

        /**
         * Get the fragment code.
         **/
        const std::string& get_fragment_code() const;

        /**
         * Compile the shader.
         *
         * @throw std::runtime_error
         * If the compile failed std::runtime_error is thrown.
         **/
        void compile();

        /**
         * Check if the shader is compiled.
         **/
        bool is_compiled() const;

        /**
         * Bind the shader.
         **/
        void bind() const;

        /**
         * Unbind the shader.
         **/
        void unbind() const;

        /**
         * Set a float uniform variable.
         **/
        void set_uniform(const std::string& id, float value);

    private:
        std::string vertex_code;
        std::string fragment_code;
        bool compiled;

        unsigned int progtam_id;
        unsigned int vertex_id;
        unsigned int fragment_id;

        Shader(const Shader&);
        const Shader& operator = (const Shader&);
    };

    typedef std::tr1::shared_ptr<Shader> ShaderPtr;
}

#endif
