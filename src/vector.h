#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

template<typename T>
struct Vector2 {
    
    Vector2( T x, T y ) {
        data[0] = x;
        data[1] = y;
    }
    
    T dot( const Vector2<T>& rhs ) const {
        return x*rhs.x + y*rhs.y;
    }
    
    bool operator==( const Vector2<T>& rhs ) const {
        return x == rhs.x && y == rhs.y;
    }
    
    bool operator!=( const Vector2<T>& rhs ) const {
        return x != rhs.x || y != rhs.y;
    }
    
    union {
        T data[2];
        struct { T x, y; };
        struct { T r, g; };
    };
};

template<typename T>
Vector2<T> operator*( T scale, const Vector2<T>& rhs ) {
    return Vector2<T> (
        rhs.data[0] * scale,
        rhs.data[1] * scale
    );
}

template<typename T>
struct Vector3  {
    
    Vector3( T x, T y, T z ) 
    :   r( x ),
        g( y ),
        b( z )
        {}
        
    Vector3()
    :   x( 0 ), 
        y( 0 ), 
        z( 0 ) 
        {}
        
    T norm() const {
        return sqrt( x*x + y*y + z*z );
    }
        
    T squaredLength() const {
        return x*x + y*y + z*z;
    }
    
    Vector3 cross( const Vector3<T>& rhs ) const {
        return Vector3 (
            y*rhs.z - z*rhs.y,
            z*rhs.x - x*rhs.z,
            x*rhs.y - y*rhs.x
        );
    }
    
    Vector3 operator+( const Vector3<T>& rhs ) const {
        return Vector3<T>( x + rhs.x, y + rhs.y, z + rhs.z );
    }
    
    Vector3 operator-( const Vector3<T>& rhs ) const {
        return Vector3<T>( x - rhs.x, y - rhs.y, z - rhs.z );
    }
    
    T dot( const Vector3<T>& rhs ) const {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }
    
    union {
        T data[3];
        struct { T x, y, z; };
        struct { T r, g, b; };
    };
};

template<typename T>
Vector3<T> operator*( T scale, const Vector3<T>& rhs ) {
    return Vector3<T>(
        rhs.data[0] * scale,
        rhs.data[1] * scale,
        rhs.data[2] * scale
    );
}

template<typename T>
struct Vector4 {
    
    Vector4()
    :   x( 0 ),
        y( 0 ),
        z( 0 ),
        w( 0 )
        {}
    
    Vector4( const Vector3<T>& v, T w )
    :   r( v.x ),
        g( v.y ),
        b( v.z ),
        a( w )
        {}
        
    Vector4( T x, T y, T z, T w )
    :   r( x ),
        g( y ),
        b( z ),
        a( w )
        {}
    
    operator Vector3<T>() const {
        return Vector3<T> ( data[0], data[1], data[2] );
    }
    
    T dot( const Vector4<T>& rhs ) const {
        return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
    }
    
    union {
        T data[4];
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
    };
};

template<typename T>
Vector4<T> operator*( T scale, const Vector4<T>& rhs ) {
    return Vector4<T>(
        rhs.data[0] * scale,
        rhs.data[1] * scale,
        rhs.data[2] * scale,
        rhs.data[3] * scale
    );
}

typedef Vector2<float> Vector2f;
typedef Vector3<float> Vector3f;
typedef Vector4<float> Vector4f;

#endif
