// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_CONFIG_H_
#define _QGL_CONFIG_H_

#ifdef BUILD_QGL
    #define QGL_EXPORT __declspec(dllexport)
#else
    #define QGL_EXPORT __declspec(dllimport)
#endif

#define QGL_VERSION "0.0.0"

#endif
