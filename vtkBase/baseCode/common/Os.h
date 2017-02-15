/*
 * file:                Os.h
 * description:         Os-specifics.
 * author:              (�) Julien Tierny <tierny@telecom-paristech.fr>.
 * date:                June 2013.
 */

#ifndef                 _OS_H
#define                 _OS_H

#include                <stdlib.h>

#include                <sstream>

#include                <Debug.h>

#ifdef _OPENMP
  #include              <omp.h>
#endif

#ifdef _WIN32
  #include              <float.h>
  #include              <iomanip>
  #include              <time.h>
  #include              <windows.h>
  #include              <direct.h>
  #include              <stdint.h>
  #include              <cwchar>
  #include              <math.h>
  #define               isnan(x)      _isnan(x)
  #define               srand48(seed) srand(seed)
  #define               drand48() (double(rand()) / RAND_MAX)
  #define               round(x) OsCall::roundToNearestInt(x)
#endif

#ifdef __unix__
#include                <cfloat>
#include                <climits>
#include                <dirent.h>
#include                <iomanip>
#include                <math.h>
#include                <unistd.h>
#include                <sys/stat.h>
#include                <sys/time.h>
#include                <sys/types.h>
#endif

#ifdef __APPLE__
#include                <cfloat>
#include                <math.h>
#include                <unistd.h>
#include                <sys/stat.h>
#include                <sys/time.h>
#include                <sys/types.h>
#include                <dirent.h>

#include                <climits>
#endif

//#define SIMPLE_PRECISION  

#ifdef SIMPLE_PRECISION
#define REAL_TYPE float
#define REAL_TYPE_STRING "float"
#define REAL_MAX  FLT_MAX
#else
#define REAL_TYPE double
#define REAL_TYPE_STRING "double"
#define REAL_MAX  DBL_MAX
#endif

#define DBL_SIGNIFICANT_DIGITS  14
#define FLT_SIGNIFICANT_DIGITS  7

#ifdef SIMPLE_PRECISION
#define REAL_SIGNIFICANT_DIGITS FLT_SIGNIFICANT_DIGITS
#else 
#define REAL_SIGNIFICANT_DIGITS DBL_SIGNIFICANT_DIGITS
#endif

#define M_PI 3.14159265358979323846

using namespace std;

namespace baseCode{
  
#ifdef SIMPLE_PRECISION
  typedef float real;
#else
  typedef double real;
#endif
 
  class OsCall{

    public:

    int static roundToNearestInt( const double val )
    {
        const double upperBound = ceil( val );
        const double lowerBound = floor( val );
        
        if( upperBound-val <= val-lowerBound )
            return (int)upperBound;
        else
            return (int)lowerBound;
    }

    inline static int getCurrentDirectory(string &directoryPath){
#ifdef _WIN32
      directoryPath = _getcwd(NULL, 0);
#else
      directoryPath = getcwd(NULL, PATH_MAX);
#endif
      directoryPath += "/";
      
      return 0;
    }
      
    inline static int mkDir( const string &directoryName ) { 
       #ifdef _WIN32
        return _mkdir( directoryName.data() ); 
      #else 
        return mkdir( directoryName.data(), 0777 ); 
      #endif
    }

    inline static vector< string > listFilesInDirectory(
      const string &directoryName, const string &extension ) { 
      vector< string > filesInDir;
      #ifdef _WIN32
        WIN32_FIND_DATA FindFileData;
        char* buffer;
        buffer = _getcwd( NULL, 0 );
        if( (buffer = _getcwd( NULL, 0 )) == NULL )
            perror( "_getcwd error" );
         else
         {
            printf( "Directory: %s \nLength: %d\n", buffer, strlen(buffer) );
            free(buffer);
         }

        HANDLE hFind = FindFirstFile(directoryName.data(), &FindFileData);
        if (hFind == INVALID_HANDLE_VALUE) {
          stringstream msg;
          msg << "[Os] Could not open directory `" 
            << directoryName << "'. Error: "<< GetLastError() << endl;
          Debug d;
          d.dMsg(cerr, msg.str(), 0);
        } else {
          string entryExtension(FindFileData.cFileName);
          entryExtension = entryExtension.substr(entryExtension.find_last_of('.') + 1);
          
          if(entryExtension == extension)
            filesInDir.push_back(string(FindFileData.cFileName));

          string dir = directoryName;
          dir.resize(dir.size()-1);
          while (FindNextFile(hFind, &FindFileData)) {
            if(extension.size()){
              string entryExtension(FindFileData.cFileName);
              entryExtension = entryExtension.substr(
                entryExtension.find_last_of('.') + 1);
              if(entryExtension == extension)
                filesInDir.push_back(dir 
                  + string(FindFileData.cFileName));
            }
            else{
              if((string(FindFileData.cFileName) != ".")
                &&(string(FindFileData.cFileName) != "..")){
                filesInDir.push_back(directoryName
                  + "/"
                  + string(FindFileData.cFileName));  
              }
            }
          }
        }
        FindClose( hFind );
      #else 
        DIR *d = opendir((directoryName + "/").data());
        if(!d){
          stringstream msg;
          msg 
            << "[Os] Could not open directory `" 
            << directoryName << "'..." << endl;
          Debug d;
          d.dMsg(cerr, msg.str(), 0);
        } else {
          struct dirent *dirEntry;
          while((dirEntry = readdir(d)) != NULL){
            if(extension.size()){
              string entryExtension(dirEntry->d_name);
              entryExtension = 
                entryExtension.substr(entryExtension.find_last_of('.') + 1);
              if(entryExtension == extension)
                filesInDir.push_back(directoryName 
                  + "/" 
                  + string(dirEntry->d_name));
            }
            else{
              if((string(dirEntry->d_name) != ".")
                &&(string(dirEntry->d_name) != ".."))
                filesInDir.push_back(directoryName 
                  + "/"
                  + string(dirEntry->d_name));
            }
          }
        }
        closedir(d);
      #endif

      return filesInDir;
    }

    inline static int rmDir( const string &directoryName ) { 
      #ifdef _WIN32
        // NOTE:
        // from julien to david: the directory will be deleted with this call
        // only if it's empty...
        return _rmdir( directoryName.data() ); 
      #else 
        stringstream cmd;
        cmd << "rm -R " << directoryName << " 2> /dev/null";
        return system(cmd.str().data()); 
      #endif
    }
    
    inline static int rmFile(const string &fileName){
      
      stringstream cmd;
      
      #ifdef _WIN32
        cmd << "del";
      #else
        cmd << "rm";
      #endif
        
      cmd << " " << fileName;
      
      #ifndef _WIN32
        cmd << " 2> /dev/null";
      #endif
        
      return system(cmd.str().data());
    }
    
    inline static int nearbyint( const double& x ) {
      #ifdef _WIN32
        const double upperBound = ceil( x );
        const double lowerBound = floor( x );
        
        if( upperBound-x <= x-lowerBound )
            return (int)upperBound;
        else
            return (int)lowerBound;
      #else 
        return nearbyint(x);
      #endif
      
    };

    inline static float getMemoryInstantUsage(){
  #ifdef __linux__
        // horrible hack since getrusage() doesn't seem to work well under linux
        stringstream procFileName;
        procFileName << "/proc/" << getpid() << "/statm";
        
        ifstream procFile(procFileName.str().data(), ios::in);
        if(procFile){
          float memoryUsage;
          procFile >> memoryUsage;
          procFile.close();
          return memoryUsage/1024.0;
        }

  #endif
        return 0;
      };


      inline static double getTimeStamp(){
        #ifdef _WIN32
          LARGE_INTEGER frequency;
          QueryPerformanceFrequency(&frequency);

          LARGE_INTEGER temp;
          QueryPerformanceCounter(&temp);

          return (double) temp.QuadPart/frequency.QuadPart;
        #endif

        #ifdef __APPLE__
          struct timeval stamp;
          gettimeofday(&stamp, NULL);
          return (stamp.tv_sec*1000000 + stamp.tv_usec)/1000000.0;
        #endif 

        #ifdef __unix__
          struct timeval stamp;
          gettimeofday(&stamp, NULL);
          return (stamp.tv_sec*1000000 + stamp.tv_usec)/1000000.0;
        #endif
      };

    protected:

    private:

  };

  class Timer {

    public:

      Timer(){ 
        start_ = getTimeStamp();
      };

      Timer(const Timer &other){
        start_ = other.start_;
      }

      inline double getElapsedTime(){
      
        double end = getTimeStamp();
        return end - start_; 
      };

      inline double getStartTime(){ 
        return start_;
      };

      inline void reStart(){ 
        start_ = getTimeStamp();
      };

    protected:

      inline const double getTimeStamp(){
        return OsCall::getTimeStamp();
      };
      
      double          start_;
  };

  class Memory{
    
    public:
      
      Memory(){ initialMemory_ = OsCall::getMemoryInstantUsage();};
      
      inline float getInitialMemoryUsage(){
        return initialMemory_;
      };
      
      inline float getInstantUsage(){
        return OsCall::getMemoryInstantUsage();
      };
      
      inline float getElapsedMemoryUsage(){
        return OsCall::getMemoryInstantUsage() - initialMemory_;
      };
      
    protected:
      
      float           initialMemory_;
  };
}

#endif
