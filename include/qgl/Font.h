// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_FONT_H_
#define _QGL_FONT_H_

#include "config.h"

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <tr1/memory>

#include "Vector.h"
#include "Image.h"
#include "SdlTtfSentry.h"

namespace qgl
{
    class Font;
    typedef std::tr1::shared_ptr<Font> FontPtr;

    /**
     * True Type Font
     **/
    class QGL_EXPORT Font
    {
    public:

        /**
         * Load the font from file.
         **/
        static FontPtr load_from_file(const std::string& file, unsigned int size);

        /**
         * Default Constructor
         **/
        Font();

        /**
         * Load font from file.
         **/
        Font(const std::string& file, unsigned int size);

        /**
         * Destructor
         **/
        ~Font();

        /**
         * Get the file the font was loaded from.
         **/
        std::string get_file() const;

        /**
         * Get the size the font was loaded in.
         **/
        unsigned int get_size() const;

        /**
         * Load a font.
         **/
        // REVIEW: deprecate the method and only use the constructor
        void load(const std::string& file, unsigned int size);

        /**
         * Estimate the size a given text will require.
         **/
        Vector2ui estimate(const std::string& text) const;

        /**
         * Estimate the size a given multiline text will require.
         **/
        Vector2ui estimate_multiline(const std::string& text) const;

        /**
         * Render the text into an image.
         **/
        ImagePtr render(const std::string& text) const;

        /**
         * Render the text into an image.
         **/
        ImagePtr render(const std::string& text, const Vector3f& color) const;

        /**
         * Render a text with multiple lines.
         **/
        std::vector<ImagePtr> render_multiline(const std::string& text) const;

        /**
         * Render a text with multiple lines.
         **/
        std::vector<ImagePtr> render_multiline(const std::string& text, const Vector3f& color) const;

    private:
        SdlTtfSentry sdl_ttf_sentry;

        std::string file;
        unsigned int size;
        TTF_Font* font;

        Font(const Font&);
        const Font& operator = (const Font&);
    };
}

#endif
