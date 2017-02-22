/*
 * file:                Color.h
 * description:         Color handling.
 * author:              (©) Julien Tierny <tierny@telecom-paristech.fr>
 * date:                February 2011.
 */

#ifndef                 _COLOR_H
#define                 _COLOR_H

#include                <Debug.h>

namespace baseCode{

  class Color : virtual public Debug{

    public:
      
      inline Color(){
        // default
        rgba_[0] = 1;
        rgba_[1] = 1;
        rgba_[2] = 1;
        rgba_[3] = 1;
      };

      inline Color(const float &r, const float &g, const float &b,
        const float &a){
        
        rgba_[0] = r;
        rgba_[1] = g;
        rgba_[2] = b;
        rgba_[3] = a;
      };
     
      ~Color(){};

      inline Color& operator=(const Color &other) {
       
        if(&other != this){
          rgba_[0] = other.rgba_[0];
          rgba_[1] = other.rgba_[1];
          rgba_[2] = other.rgba_[2];
          rgba_[3] = other.rgba_[3];
        }
      
        return *this;
      };

      inline void exportToVRML(ostream &f) const{
        for(int i = 0; i < 3; i++)
          f << rgba_[i] << " ";
      };

      inline double getAlpha() const{ return rgba_[3]; };

      inline int setAlpha(const double &alpha) { 
        rgba_[3] = (float)alpha; return 0;
      };

      inline int setColor(const float &r, const float &g, const float &b,
        const float &a){
        
        rgba_[0] = r;
        rgba_[1] = g;
        rgba_[2] = b;
        rgba_[3] = a;

        return 0;
      };

      inline operator const float *() const{ return rgba_; };

    protected:
      
      float                rgba_[4];
  };
}

#endif
