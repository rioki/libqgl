// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_VECTOR_H_
#define _QGL_VECTOR_H_

#include "config.h"

#include <cassert>

namespace qgl
{
    /**
     * Multidimensional Vector
     **/
    template <unsigned int D, typename T = float>
    class Vector
    {
    public:
        /**
         * The dimension of the vector.
         **/
        static const unsigned int dimension = D;

        /**
         * The scalar type of the vector.
         **/
        typedef T scalar_type;

        /**
         * The index type.
         **/
        typedef unsigned int index_type;

        /**
         * Default Constructor
         *
         * @warning Like POD types the vector class does not initialize
         * to a specific value. This is done for performance reasons.
         * In addition there is no real sensible default vaue for vectors
         * and relying on one is not a good idea.
         **/
        Vector() {}

        /**
         * Copy Constructor.
         **/
        Vector(const Vector<D, T>& orig)
        {
            for (unsigned int i = 0; i < D; i++)
            {
                data[i] = orig.data[i];
            }
        }

        /**
         * Type Conversion Constructor
         **/
        template <typename T2>
        Vector(const Vector<D, T2>& orig)
        {
            for (unsigned int i = 0; i < D; i++)
            {
                data[i] = orig(i);
            }
        }

        /**
         * Destructor
         **/
        ~Vector() {}

        /**
         * Assignment Operator
         **/
        const Vector<D, T>& operator = (const Vector<D, T>& orig)
        {
            for (unsigned int i = 0; i < D; i++)
            {
                data[i] = orig.data[i];
            }
            return *this;
        }

        /**
         * Addition Assignment Operator
         **/
        const Vector<D, T>& operator += (const Vector<D, T>& other)
        {
            for (unsigned int i = 0; i < D; i++)
            {
                data[i] += other.data[i];
            }
            return *this;
        }

        /**
         * Addition Substracton Operator
         **/
        const Vector<D, T>& operator -= (const Vector<D, T>& other)
        {
            for (unsigned int i = 0; i < D; i++)
            {
                data[i] -= other.data[i];
            }
            return *this;
        }

        /**
         * Subscript operator
         **/
        T& operator () (unsigned int i)
        {
            assert(i < D);
            return data[i];
        }

        /**
         * Constant Subscript operator
         **/
        T operator () (unsigned int i) const
        {
            assert(i < D);
            return data[i];
        }

    private:
        T data[D];
    };

    /**
     * Unary Plus
     **/
    template <unsigned int D, typename T>
    const Vector<D, T>& operator + (const Vector<D, T>& v)
    {
        return v;
    }

    /**
     * Negation
     **/
    template <unsigned int D, typename T>
    Vector<D, T> operator - (const Vector<D, T>& v)
    {
        Vector<D, T> result;
        for (unsigned int i = 0; i < D; i++)
        {
            result(i) = -v(i);
        }
        return result;
    }

    /**
     * Addition
     **/
    template <unsigned int D, typename T>
    Vector<D, T> operator + (const Vector<D, T>& a, const Vector<D, T>& b)
    {
        Vector<D, T> result(a);
        result += b;
        return result;
    }

    /**
     * Subtraction
     **/
    template <unsigned int D, typename T>
    Vector<D, T> operator - (const Vector<D, T>& a, const Vector<D, T>& b)
    {
        Vector<D, T> result(a);
        result -= b;
        return result;
    }

    /**
     * Scalar Multiplication
     **/
    template <unsigned int D, typename T>
    Vector<D, T> operator * (const Vector<D, T>& v, T s)
    {
        Vector<D, T> result;
        for (unsigned int i = 0; i < D; i++)
        {
            result(i) = v(i) * s;
        }
        return result;
    }

    /**
     * Scalar Multiplication
     **/
    template <unsigned int D, typename T>
    Vector<D, T> operator * (T s, const Vector<D, T>& v)
    {
        Vector<D, T> result;
        for (unsigned int i = 0; i < D; i++)
        {
            result(i) = v(i) * s;
        }
        return result;
    }

    /**
     * Equal Operator
     **/
    template <unsigned int D, typename T>
    bool operator == (const Vector<D, T>& a, const Vector<D, T>& b)
    {
        for (unsigned int i = 0; i < D; i++)
        {
            if (a(i) != b(i))
            {
                return false;
            }
        }
        return true;
    }

    template <unsigned int D, typename T>
    bool operator != (const Vector<D, T>& a, const Vector<D, T>& b)
    {
        return !(a == b);
    }

    template <typename T>
    Vector<2, T> create_vector2(T x, T y)
    {
        Vector<2, T> result;
        result(0) = x;
        result(1) = y;
        return result;
    }

    template <typename T>
    Vector<3, T> create_vector3(T x, T y, T z)
    {
        Vector<3, T> result;
        result(0) = x;
        result(1) = y;
        result(2) = z;
        return result;
    }

    template <typename T>
    Vector<4, T> create_vector4(T x, T y, T z, T m)
    {
        Vector<4, T> result;
        result(0) = x;
        result(1) = y;
        result(2) = z;
        result(3) = m;
        return result;
    }

    typedef Vector<2, int> Vector2i;
    typedef Vector<2, unsigned int> Vector2ui;
    typedef Vector<2, float> Vector2f;
    typedef Vector<2, double> Vector2d;

    typedef Vector<3, int> Vector3i;
    typedef Vector<3, unsigned int> Vector3ui;
    typedef Vector<3, float> Vector3f;
    typedef Vector<3, double> Vector3d;

    typedef Vector<4, int> Vector4i;
    typedef Vector<4, unsigned int> Vector4ui;
    typedef Vector<4, float> Vector4f;
    typedef Vector<4, double> Vector4d;
}

#endif
