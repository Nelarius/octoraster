#ifndef VECTOR_H
#define VECTOR_H

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
Vector2<T> operator/( T divisor, const Vector2<T>& rhs ) {
    T scale = 1 / divisor;
    return Vector2<T>(
        rhs.data[0] * scale,
        rhs.data[1] * scale
    );
}

template<typename T>
struct Vector3  {
    Vector3( T x, T y, T z ) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
    Vector3()
    :   x( 0 ), y( 0 ), z( 0 ) {}
    
    Vector3 cross( const Vector3<T>& rhs ) const {
        return Vector3 (
            y*rhs.z - z*rhs.y,
            z*rhs.x - x*rhs.z,
            x*rhs.y - y*rhs.x
        );
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
Vector3<T> operator/( T divisor, const Vector3<T>& rhs ) {
    T scale = 1 / divisor;
    return Vector3<T>(
        rhs.data[0] * scale,
        rhs.data[1] * scale,
        rhs.data[2] * scale
    );
}

typedef Vector2<float> Vector2f;
typedef Vector3<float> Vector3f;

#endif