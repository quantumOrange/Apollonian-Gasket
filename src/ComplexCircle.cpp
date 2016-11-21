//
//  ComplexCircle.cpp
//  Apollonian
//
//  Created by David Crooks on 21/11/2016.
//
//

#include "ComplexCircle.hpp"

ComplexCircle::ComplexCircle(std::complex<double> _z,  double _k){
    z =_z;
    k =_k;
    radius = 1.0/abs(_k);
    std::complex<double> c = z/_k;
    center = ofVec2f(c.real(),c.imag());
}

ComplexCircle::ComplexCircle(double x, double y, double _radius, bool inside){
    radius = _radius;
    k = 1.0/_radius;
    if(inside) k = -k;
    center = ofVec2f(x,y);
    z = std::complex<double>(x,y);
    z *= k;
}

ComplexCircle::ComplexCircle(ofVec2f _center,  double _radius, bool inside){
    radius = _radius;
    k = 1.0/_radius;
    if(inside) k = -k;
    center = _center;
    z = std::complex<double>(center.x,center.y);
    z *= k;
}

void ComplexCircle::draw(){
    if(k>0.0){
        ofSetColor(ofColor(255));
    }
    else {
        ofSetColor(ofColor(0));
    }
  //  cout << "draw a circle at "<< center <<  "with radius" << radius << endl;
    
    ofDrawCircle(center, radius);
}


vector<ComplexCircle> tangentCircles;