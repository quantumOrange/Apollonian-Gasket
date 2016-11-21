//
//  ComplexCircle.hpp
//  Apollonian
//
//  Created by David Crooks on 21/11/2016.
//
//

#ifndef ComplexCircle_hpp
#define ComplexCircle_hpp

#include <stdio.h>
#include "ofMain.h"
#include <complex>
#include <cmath>

class ComplexCircle {
public:
    ComplexCircle(double x, double y,  double _radius, bool inside = false);
    ComplexCircle(std::complex<double> _z,  double _k);
    ComplexCircle(ofVec2f _center,  double _radius, bool inside = false);
    double radius;
    ofVec2f center;
    double k; //curvature
    std::complex<double> z;
    void draw();
    vector<ComplexCircle > tangentCircles;
    
    bool operator==( const ComplexCircle& vec ) const;
    bool match( const ComplexCircle& vec, float tolerance ) const;
    
};

inline bool ComplexCircle::operator==( const ComplexCircle& c ) const {
    return (radius == c.radius && center==c.center);
}


inline bool ComplexCircle::match( const ComplexCircle& c, float tolerance ) const {
    return (fabs(radius - c.radius) < tolerance)
    && center.match(c.center,tolerance);
}



#endif /* ComplexCircle_hpp */
