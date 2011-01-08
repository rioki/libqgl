// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "utils.h"

#include <cstdlib>
#include <GL/glew.h>
#include <fstream>
#include <stdexcept>

// PORT: wrap win32 headers in ifdef
// we want at least Windows XP
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <shlobj.h>

namespace qgl
{
//------------------------------------------------------------------------------
    void draw_rect(float x, float y, float w, float h)
    {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);

        float w2 = w * 0.5f;
        float h2 = h * 0.5f;

        glBegin(GL_QUADS);

            glTexCoord2f(0.0, 0.0);
            glVertex2f(-w2, -h2);

            glTexCoord2f(1.0, 0.0);
            glVertex2f( w2, -h2);

            glTexCoord2f(1.0, 1.0);
            glVertex2f( w2,  h2);

            glTexCoord2f(0.0, 1.0);
            glVertex2f(-w2,  h2);

        glEnd();

        glPopMatrix();
    }

//------------------------------------------------------------------------------
    void draw_rect(const Vector2f& pos, const Vector2f& size)
    {
        draw_rect(pos(0), pos(1), size(0), size(1));
    }


//------------------------------------------------------------------------------
    float rand_float(float min, float max)
    {
        float dist = max - min;
        return ((static_cast<float>(std::rand()) / RAND_MAX) * dist) + min;
    }

//------------------------------------------------------------------------------
    std::vector<std::string> explode(const std::string& str, const std::string& delimiter)
    {
        std::vector<std::string> gibs;
        size_t start = 0;
        size_t end = 0;

        while ((start != std::string::npos) && (start < str.size()))
        {
            end = str.find(delimiter, start);

            std::string gib;
            if (end == std::string::npos)
            {
                gib = str.substr(start);
                start = std::string::npos;
            }
            else
            {
                gib = str.substr(start, end - start);
                start = end + delimiter.size();
            }
            gibs.push_back(gib);
        }

        return gibs;
    }

//------------------------------------------------------------------------------
    bool file_exists(const std::string& file)
    {
        FILE* fh = fopen(file.c_str(), "r");
        if (fh != NULL)
        {
            fclose(fh);
            return true;
        }
        else
        {
            return false;
        }
    }

//------------------------------------------------------------------------------
    std::string load_file(const std::string& file)
    {
        std::string tmp;

        std::ifstream input(file.c_str());
        char c = input.get();
        while (c != EOF)
        {
            tmp += c;
            c = input.get();
        }

        return tmp;
    }

//------------------------------------------------------------------------------
    std::string get_config_filename()
    {
        // PORT: we also need a portable version of this
        CHAR szAppData[MAX_PATH];
        HRESULT hr = SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, szAppData);
        if (hr < 0)
        {
            throw std::logic_error("Could not determain APPDATA folder.");
        }
        std::string app_data(szAppData);
        std::string config_dir = app_data + "\\qgl";
        SHCreateDirectoryExA(NULL, config_dir.c_str(), NULL);

        return config_dir + "\\Options.cfg";
    }
}
