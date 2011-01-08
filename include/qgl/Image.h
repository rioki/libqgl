// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_IMAGE_H_
#define _QGL_IMAGE_H_

#include <string>
#include <SDL.h>
#include <tr1/memory>

#include "Vector.h"
#include "ColorFormat.h"

namespace qgl
{
    // REVIEW: The image should be divorced from the openGL handling.

    /**
     * 2D Image Buffer
     **/
    class QGL_EXPORT Image
    {
    public:
        /**
         * Default Constructor
         **/
        Image();

        /**
         * Create image from file.
         **/
        explicit Image(const std::string& f);

        /**
         * Wrap SDL Surface.
         **/
        explicit Image(SDL_Surface* s);

        /**
         * Destructor
         **/
        ~Image();

        /**
         * Get the file the image was loaded from.
         **/
        const std::string& get_file() const;

        /**
         * Get the image's width.
         **/
        unsigned int get_width() const;

        /**
         * Get the image's height.
         **/
        unsigned int get_height() const;

        /**
         * Get the image's size.
         **/
        Vector2ui get_size() const;

        /**
         * Get the data format.
         **/
        ColorFormat get_format() const;

        /**
         * Get the raw data.
         **/
        const void* get_data() const;

        /**
         * Bind the image to a openGL texture.
         **/
        void bind(unsigned int i = 0) const;

        /**
         * Unbind the image
         **/
        void unbind(unsigned int i = 0) const;

        /**
         * Upload the image to video memory.
         **/
        // REVIEW: thid method should be private
        void upload_to_opengl() const;

        /**
         * Load image from file.
         **/
        void load(const std::string& file);

    private:
        std::string file;
        SDL_Surface* surface;
        mutable bool loaded_opengl;
        mutable unsigned int gl_id;

        // prevent implicit copy
        Image(const Image&);
        const Image& operator = (const Image&);
    };

    typedef std::tr1::shared_ptr<Image> ImagePtr;
}

#endif
