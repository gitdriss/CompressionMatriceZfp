/*
 * file:                Debug.h
 * description:         Minimalist debug handling.
 * author:              (©) Julien Tierny <tierny@telecom-paristech.fr>.
 * date:                February 2011.
 */

#ifndef                 _DEBUG_H
#define                 _DEBUG_H

#include                <cerrno>
#include                <fstream>
#include                <iostream>
#include                <sstream>
#include                <string>
#include                <vector>

using namespace std;

static bool welcomeMsg_ = false;
static bool goodbyeMsg_ = false;

namespace baseCode{

  class Debug{

    public:

      Debug() { 
        
        debugLevel_ = 2; 
        
        // avoid warnings
        if(goodbyeMsg_) goodbyeMsg_ = true; 
        
        if(welcomeMsg_){
          welcomeMsg_ = false;
          stringstream s;
          s << "[Common] "
"__        _______ _____ ___ _____       __  __    ____   ___  _ _  _ "
            << endl << "[Common] "
"\\ \\      / /_   _|  ___|_ _|_   _|     / /__\\ \\  |___ \\ / _ \\/ | || |"
            << endl << "[Common] "
" \\ \\ /\\ / /  | | | |_   | |  | |      | |/ __| |   __) | | | | | || |_"
            << endl << "[Common] "
"  \\ V  V /   | | |  _|  | |  | |      | | (__| |  / __/| |_| | |__   _|"
            << endl << "[Common] "
"   \\_/\\_/    |_| |_|   |___| |_|      | |\\___| | |_____|\\___/|_|  |_|"
            << endl << "[Common] "
"                                       \\_\\  /_/" << endl;

          s << "[Common] Welcome!" << endl;
          dMsg(cout, s.str(), 1);
        }
      };
      virtual ~Debug(){};

      virtual inline const int dMsg(ostream &stream, string msg, 
        const int &debugLevel) const{
        if(debugLevel_ >= debugLevel)
          stream << msg.data();
        return 0;
      }

      inline const int err(const string msg) const{
        return dMsg(cerr, msg, 0);
      }

      inline const int msg(const char* _msg, const int debugLevel = 0) const{
        return dMsg(cout, string(_msg), debugLevel);
      }

      virtual inline const int setDebugLevel(const int &debugLevel){
        debugLevel_ = debugLevel;
        return 0;
      };

    protected:

      int                     debugLevel_;
  };
}

using namespace baseCode;

#include                <Os.h>

// backward compatibility
class DebugTimer : public Timer{};
class DebugMemory : public Memory{};

#endif
