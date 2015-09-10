#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

template<typename T>
struct Matrix2 {
    
    T data[4];
    
    Matrix2( T v1, T v2, T v3, T v4 ) {
        data[0] = v1; data[1] = v2;
        data[2] = v3; data[3] = v3;
    }
    
    T trace() const {
        return data[0] + data[3];
    }
    
    Vector2<T> operator*( const Vector2<T>& v ) {
        return Vector2<T> (
            data[0]*v.x + data[1]*v.y,
            data[2]*v.y + data[3]*v.y
        );
    }
    
    Matrix2<T> operator*( const Matrix2<T>& m ) {
        return Matrix2<T> (
            data[0]*m.data[0] + data[1]*m.data[2],
            data[0]*m.data[1] + data[1]*m.data[3],
            data[2]*m.data[0] + data[3]*m.data[2],
            data[2]*m.data[1] + data[3]*m.data[3]
        );
    }
    
    Matrix2<T> operator*( T val ) const {
        return Matrix2<T> (
            val*data[0], val*data[1],
            val*data[2], val*data[3]
        );
    }
    
    Matrix2<T> operator-( const Matrix2<T>& m ) const {
        return Matrix2<T> (
            data[0] - m.data[0], data[1] - m.data[1],
            data[2] - m.data[2], data[3] - m.data[3]
        );
    }
    
    Matrix2<T> operator+( const Matrix2<T>& m ) const {
        return Matrix2<T> (
            data[0] + m.data[0], data[1] + m.data[1],
            data[2] + m.data[2], data[3] + m.data[3]
        );
    }
    
    Matrix2<T> transpose() const {
        return Matrix2<T> (
            data[0], data[2],
            data[1], data[3]
        );
    }
    
    T determinant() const {
        return data[0]*data[3] - data[2]*data[1];
    }
    
    Matrix2<T> inverse() const {
        // obtained using the Cayley-Hamilton method
        T factor = 1.0 / determinant();
        return factor * ( trace()*Matrix2<T>() - *this );
    }
};

template<typename T>
Matrix2<T> operator*( T val, const Matrix2<T>&  m ) {
    return Matrix2<T> (
        val*m.data[0], val*m.data[1],
        val*m.data[2], val*m.data[3]
    );
}
    
template<typename T>
struct Matrix3 {
    
        T data[9];
        
        Matrix3( T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9 ) {
            data[0] = v1; data[1] = v2; data[2] = v3;
            data[3] = v4; data[4] = v5; data[5] = v6;
            data[6] = v7; data[7] = v8; data[8] = v9;
        }
            
        T trace() const {
            return data[0] + data[4] + data[8];
        }
    
        Vector3<T> operator*( const Vector3<T>& v ) const {
            return Vector3<T> (
                data[0]*v.x + data[1]*v.y + data[2]*v.z,
                data[3]*v.x + data[4]*v.y + data[5]*v.z,
                data[6]*v.x + data[7]*v.y + data[8]*v.z
            );
        }
        
        Matrix3<T> operator*( const Matrix3<T>& m ) const {
            return Matrix3<T> (
                data[0]*m.data[0] + data[1]*m.data[3] + data[2]*m.data[6],
                data[0]*m.data[1] + data[1]*m.data[4] + data[2]*m.data[7],
                data[0]*m.data[2] + data[1]*m.data[5] + data[2]*m.data[8],
                data[3]*m.data[0] + data[4]*m.data[3] + data[5]*m.data[6],
                data[3]*m.data[1] + data[4]*m.data[4] + data[5]*m.data[7],
                data[3]*m.data[2] + data[4]*m.data[5] + data[5]*m.data[8],
                data[6]*m.data[0] + data[7]*m.data[3] + data[8]*m.data[6],
                data[6]*m.data[1] + data[7]*m.data[4] + data[8]*m.data[7],
                data[6]*m.data[2] + data[7]*m.data[5] + data[8]*m.data[8]
            );
        }
        
        Matrix3<T> operator*( T val ) const {
            return Matrix3<T> (
                val*data[0], val*data[1], val*data[2],
                val*data[3], val*data[4], val*data[5],
                val*data[6], val*data[7], val*data[8]
            );
        }
        
        Matrix3<T> operator+( const Matrix3<T>& m ) const {
            return Matrix3<T> (
                data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2], 
                data[3] + m.data[3], data[4] + m.data[4], data[5] + m.data[5], 
                data[6] + m.data[6], data[7] + m.data[7], data[8] + m.data[8]
            );
        }
        
        Matrix3<T> operator-( const Matrix3<T>& m ) const {
            return Matrix3<T> (
                data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2], 
                data[3] - m.data[3], data[4] - m.data[4], data[5] - m.data[5], 
                data[6] - m.data[6], data[7] - m.data[7], data[8] - m.data[8]
            );
        }
        
        Matrix3<T> transpose() const {
            return Matrix3<T> (
                data[0], data[3], data[6], 
                data[1], data[4], data[7], 
                data[2], data[5], data[8]
            );
        }
        
        T determinant() const {
            return 
                  data[0]*Matrix2<T>( data[4], data[5], data[7], data[8] ).determinant() 
                - data[1]*Matrix2<T>( data[3], data[5], data[6], data[8] ).determinant() 
                + data[2]*Matrix2<T>( data[3], data[4], data[6], data[7] ).determinant();
        }
        
        Matrix3<T> inverse() const {
            // obtained using the Cayley-Hamilton method
            T factor = 1.0 / determinant();
            const Matrix3<T>& A = *this;
            Matrix3<T> AA = A*A;
            T trA = A.trace();
            return factor * ( Matrix3<T>()*0.5*(trA*trA - AA.trace()) - A*trA + AA );
        }
};

template<typename T>
Matrix3<T> operator*( T val, const Matrix3<T>& m ) {
    return Matrix3<T> (
        val*m.data[0], val*m.data[1], val*m.data[2],
        val*m.data[3], val*m.data[4], val*m.data[5],
        val*m.data[6], val*m.data[7], val*m.data[8]
    );
}

template<typename T>
struct Matrix4 {
    
    T data[16];
    
    Matrix4() {
        data[0] = 1; data[1] = 0; data[2] = 0; data[3] = 0;
        data[4] = 0; data[5] = 1; data[6] = 0; data[7] = 0;
        data[8] = 0; data[9] = 0; data[10] = 1; data[11] = 0;
        data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
    }
        
    Matrix4( T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9, T v10, T v11, T v12,T v13, T v14, T v15, T v16 ) {
        data[0] = v1; data[1] = v2; data[2] = v3; data[3] = v4;
        data[4] = v5; data[5] = v6; data[6] = v7; data[7] = v8;
        data[8] = v9; data[9] = v10; data[10] = v11; data[11] = v12;
        data[12] = v13; data[13] = v14; data[14] = v15; data[15] = v16;
    }
    
    T trace() const {
        return data[0] + data[5] + data[10] + data[15];
    }
    
    Vector4<T> operator*( const Vector4<T>& v ) const {
        return Vector4<T>(
            data[0]*v.x + data[1]*v.y + data[2]*v.z + data[3]*v.w,
            data[4]*v.x + data[5]*v.y + data[6]*v.z + data[7]*v.w,
            data[8]*v.x + data[9]*v.y + data[10]*v.z + data[11]*v.w,
            data[12]*v.x + data[13]*v.y + data[14]*v.z + data[15]*v.w
        );
    }
    
    Matrix4<T> operator*( const Matrix4<T>& m ) const {      
        return Matrix4<T> (
            data[0]*m.data[0] + data[1]*m.data[4] + data[2]*m.data[8] + data[3]*m.data[12],
            data[0]*m.data[1] + data[1]*m.data[5] + data[2]*m.data[9] + data[3]*m.data[13],
            data[0]*m.data[2] + data[1]*m.data[6] + data[2]*m.data[10] + data[3]*m.data[14],
            data[0]*m.data[3] + data[1]*m.data[7] + data[2]*m.data[11] + data[3]*m.data[15],
            data[4]*m.data[0] + data[5]*m.data[4] + data[6]*m.data[8] + data[7]*m.data[12],
            data[4]*m.data[1] + data[5]*m.data[5] + data[6]*m.data[9] + data[7]*m.data[13],
            data[4]*m.data[2] + data[5]*m.data[6] + data[6]*m.data[10] + data[7]*m.data[14],
            data[4]*m.data[3] + data[5]*m.data[7] + data[6]*m.data[11] + data[7]*m.data[15],
            data[8]*m.data[0] + data[9]*m.data[4] + data[10]*m.data[8] + data[11]*m.data[12],
            data[8]*m.data[1] + data[9]*m.data[5] + data[10]*m.data[9] + data[11]*m.data[13],
            data[8]*m.data[2] + data[9]*m.data[6] + data[10]*m.data[10] + data[11]*m.data[14],
            data[8]*m.data[3] + data[9]*m.data[7] + data[10]*m.data[11] + data[11]*m.data[15],
            data[12]*m.data[0] + data[13]*m.data[4] + data[14]*m.data[8] + data[15]*m.data[12],
            data[12]*m.data[1] + data[13]*m.data[5] + data[14]*m.data[9] + data[15]*m.data[13],
            data[12]*m.data[2] + data[13]*m.data[6] + data[14]*m.data[10] + data[15]*m.data[14],
            data[12]*m.data[3] + data[13]*m.data[7] + data[14]*m.data[11] + data[15]*m.data[15]
        );
    }
    
    Matrix4<T> operator+( const Matrix4<T>& m ) const {
        return Matrix4<T> (
            data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2], data[3] + m.data[3], 
            data[4] + m.data[4], data[5] + m.data[5], data[6] + m.data[6], data[7] + m.data[7], 
            data[8] + m.data[8], data[9] + m.data[9], data[10] + m.data[10], data[11] + m.data[11], 
            data[12] + m.data[12], data[13] + m.data[13], data[14] + m.data[14], data[15] + m.data[15]
        );
    }
    
    Matrix4<T> operator-( const Matrix4<T>& m ) const {
        return Matrix4<T> (
            data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2], data[3] - m.data[3], 
            data[4] - m.data[4], data[5] - m.data[5], data[6] - m.data[6], data[7] - m.data[7], 
            data[8] - m.data[8], data[9] - m.data[9], data[10] - m.data[10], data[11] - m.data[11], 
            data[12] - m.data[12], data[13] - m.data[13], data[14] - m.data[14], data[15] - m.data[15]
        );
    }
    
    Matrix4<T> operator*( T val ) const {
        return Matrix4<T> (
            val*data[0], val*data[1], val*data[2], val*data[3],
            val*data[4], val*data[5], val*data[6], val*data[7],
            val*data[8], val*data[9], val*data[10], val*data[11],
            val*data[12], val*data[13], val*data[14], val*data[15]
        );
    }
    
    Matrix4<T> transpose() const {
        return Matrix4<T> (
            data[0], data[4], data[8], data[12],
            data[1], data[5], data[9], data[13],
            data[2], data[6], data[10], data[14],
            data[3], data[7], data[11], data[15]
        );
    }
    
    T determinant() const {
        return
              data[0]*Matrix3<T>( data[5], data[6], data[7], data[9], data[10], data[11], data[13], data[14], data[15] ).determinant()
            - data[1]*Matrix3<T>( data[4], data[6], data[7], data[8], data[10], data[11], data[12], data[14], data[15] ).determinant()
            + data[2]*Matrix3<T>( data[4], data[5], data[7], data[8], data[9], data[11], data[12], data[13], data[15] ).determinant()
            - data[3]*Matrix3<T>( data[4], data[5], data[6], data[8], data[9], data[10], data[12], data[13], data[14] ).determinant();
    }
    
    Matrix4<T> inverse() const {
        // obtained using the Cayley-Hamilton method
        T factor = 1.0 / determinant();
        const Matrix4<T>& A = *this;
        Matrix4<T> AA = A*A;
        Matrix4<T> AAA = AA*A;
        T trA = trace();
        T trAA = AA.trace();
        T trAAA = AAA.trace();
        return factor * ( Matrix4<T>()*0.1666666667*(trA*trA*trA - 3.0*trA*trAA + 2.0*trAAA) - A*0.5*(trA*trA - trAA) + AA*trA - AAA );
    }
};

template<typename T>
Matrix4<T> operator*( T val, const Matrix4<T>& m ) {
    return Matrix4<T>(
        val*m.data[0], val*m.data[1], val*m.data[2], val*m.data[3],
        val*m.data[4], val*m.data[5], val*m.data[6], val*m.data[7],
        val*m.data[8], val*m.data[9], val*m.data[10], val*m.data[11],
        val*m.data[12], val*m.data[13], val*m.data[14], val*m.data[15]
    );
}

typedef Matrix2<float> Matrix2f;
typedef Matrix3<float> Matrix3f;
typedef Matrix4<float> Matrix4f;

#endif