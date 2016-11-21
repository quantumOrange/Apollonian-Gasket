//
//  Apollonian.hpp
//  Apollonian
//
//  Created by David Crooks on 21/11/2016.
//
//

#ifndef Apollonian_hpp
#define Apollonian_hpp

#include <stdio.h>
#include "ComplexCircle.hpp"

class Apollonian {
public:
    void setup();
    void update();
    void draw();
    
    vector<ComplexCircle> circles;
    vector<ComplexCircle> newcircles;
    
private:
    
    vector<ComplexCircle> apollonian(ComplexCircle c);
    vector<ComplexCircle> decartes(ComplexCircle c1, ComplexCircle c2, ComplexCircle c3);
    
    ComplexCircle thirdCircle(ComplexCircle c1,ComplexCircle c2, double angle);
    ofVec2f find_c3(ofVec2f center2, double r2, double r3,double angle);
    double find_r3(ofVec2f center3,ofVec2f center1,double r1);
};


#endif /* Apollonian_hpp */
