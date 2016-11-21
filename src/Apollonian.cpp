//
//  Apollonian.cpp
//  Apollonian
//
//  Created by David Crooks on 21/11/2016.
//
//

#include "Apollonian.hpp"

ofVec2f center;
ofVec2f touchpoint;


void Apollonian::setup(){
    double r1 = ofGetWidth()*0.48;
    double r2 = r1*(2.0/3.0);
    center = ofVec2f(ofGetWidth()*0.5,ofGetHeight()*0.5);
    touchpoint = center - ofVec2f(r1,0.0);
    auto c1 = ComplexCircle(center,r1,true);
    auto c2 = ComplexCircle(touchpoint.x + r2,touchpoint.y,r2);
    
    double angle = 1.23;
    auto c3 = thirdCircle(c1,c2,angle);
    c1.tangentCircles = {c3,c2};
    c2.tangentCircles = {c3,c1};
    c3.tangentCircles = {c1,c2};

   circles = {c1,c2,c3};
    
    
    cout << "cicles" << circles.size();
    cout << "num tan 1:" <<c1.tangentCircles.size() << endl;
    
    ofSetCircleResolution(100);
    ofBackground(255);
    
    //for_each(circles.begin(),circles.end(),[](ComplexCircle &c){c.draw();});
    //circles.reserve(newcircles.size());
    //circles.insert(circles.end(),newcircles.begin(),newcircles.end() );
}

void Apollonian::update(){
    circles.reserve(newcircles.size());
    circles.insert(circles.end(),newcircles.begin(),newcircles.end() );
    newcircles.clear();
    
    if(circles.size() < 10000){
        for (const auto c : circles)
        {
          ////out << "radius :" <<c.radius << endl;
           //cout << "loop num tan :" <<c.tangentCircles.size() << endl;
            auto   v = apollonian(c);
            newcircles.reserve(newcircles.size() + v.size());
            newcircles.insert(newcircles.end(), v.begin(),v.end());
        }
    }
    cout << circles.size() << ", new cirles: " << newcircles.size() << endl;
}

void Apollonian::draw(){
     for_each(circles.begin(),circles.end(),[](ComplexCircle &c){c.draw();});
}

ComplexCircle Apollonian::thirdCircle(ComplexCircle c1,ComplexCircle c2, double angle){
    auto r_a = 0.5*(c1.radius + c2.radius);
    auto c_a = 0.5*( c1.center + c2.center);
    auto dc3 = ofVec2f(r_a*cos(angle),r_a*sin(angle));
    
    auto r3 = c1.radius - c2.radius;
    auto center3 = c_a + dc3;
    
    for(int i =0;i<100;i++){
        r3 = find_r3(center3, c1.center, c1.radius);
        center3 = find_c3(c2.center, c2.radius, r3, angle);
    }
    
    return ComplexCircle(center3,r3);
}

ofVec2f Apollonian::find_c3(ofVec2f center2, double r2, double r3,double angle){
    return center2 + (r2+r3)*ofVec2f(cos(angle),sin(angle));
}

double Apollonian::find_r3(ofVec2f center3,ofVec2f center1,double r1){
    return r1 - center3.distance(center1);
}

vector<ComplexCircle> Apollonian::decartes(ComplexCircle c1, ComplexCircle c2, ComplexCircle c3){
    
    auto k_plus = c1.k + c2.k + c3.k + 2.0*sqrt(c1.k*c2.k + c3.k*c2.k + c1.k*c3.k);
    auto k_minus = c1.k + c2.k + c3.k - 2.0*sqrt(c1.k*c2.k + c3.k*c2.k + c1.k*c3.k);
    
    auto t1 = c1.z + c2.z + c3.z ;
    auto t2 = 2.0*sqrt(c1.z*c2.z + c3.z*c2.z + c1.z*c3.z);
    
    auto z_plus  = t1 + t2;
    auto z_minus = t1 - t2;
    
    auto c_plus = ComplexCircle(z_plus,k_plus);
    auto c_minus = ComplexCircle(z_minus,k_minus);

    c_plus.tangentCircles = {c1,c2,c3};
    c_minus.tangentCircles = {c1,c2,c3};

    c1.tangentCircles.push_back(c_plus);
    c1.tangentCircles.push_back(c_minus);
    c2.tangentCircles.push_back(c_plus);
    c2.tangentCircles.push_back(c_minus);
    c3.tangentCircles.push_back(c_plus);
    c3.tangentCircles.push_back(c_minus);
  
    return {c_plus,c_minus};
}

vector<ComplexCircle> Apollonian::apollonian(ComplexCircle c){
    
    if(c.tangentCircles.size()<2 || c.tangentCircles.size()>4) return {};
    if(c.tangentCircles.size()==2) return decartes(c, c.tangentCircles[0], c.tangentCircles[1]);
    
    auto c1 = c.tangentCircles[0];
    auto c2 = c.tangentCircles[1];
    auto c3 = c.tangentCircles[2];
    
    auto c23 = decartes(c,c2,c3);
    auto c13 = decartes(c,c1,c3);
    auto c12 = decartes(c,c1,c2);
    
    c23.erase(std::remove_if(c23.begin(),
                             c23.end(),
                             [c1](ComplexCircle x){return x.match(c1,1.0) || x.radius<2.0;}));
              
    c13.erase(std::remove_if(c13.begin(),
                           c13.end(),
                           [c2](ComplexCircle x){return x.match(c2,1.0) || x.radius<2.0;}));
            
    c12.erase(std::remove_if(c12.begin(),
                             c12.end(),
                             [c3](ComplexCircle x){return x.match(c3,1.0) || x.radius<2.0;}));
    
    c23.reserve(c23.size() + c13.size() + c12.size());
    c23.insert(c23.end(), c13.begin(),c13.end());
    c23.insert(c23.end(), c12.begin(),c12.end());
    
    return c23;
}


