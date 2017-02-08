#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

template <class dataType> class Matrix{

	public:
	
		int load(const string &path){

			ifstream f(path.data(), ios::in | ios::binary);

			for(int i = 0; i < (int) matrix_.size(); i++){
			    for(int j = 0; j < (int) matrix_[i].size(); j++){
					for(int k = 0; k < (int) matrix_[i][j].size(); k++){
			      		f.read((char *) &(matrix_[i][j][k]), sizeof(dataType));
						//cout << matrix_[i][j][k] << "\t";
					}
				
			    }
				//cout <<endl;
			}

			f.close();

			return 0;
		};
		int display(){
			for(int i = 0; i < (int) matrix_.size(); i++){
			    for(int j = 0; j < (int) matrix_[i].size(); j++){
					for(int k = 0; k < (int) matrix_[i][j].size(); k++){
						cout << matrix_[i][j][k] << "\t";
					}
				
			    }
				cout <<endl;
			}
			return 0;
		};

		int setDimensions(const int sizeX, const int sizeY, const int sizeZ){

			size_.resize(3);
			size_[0] = sizeX;
			size_[1] = sizeY;
			size_[2] = sizeZ;
			
			matrix_.resize(sizeX);
			for(int i = 0; i < sizeX; i++){
				matrix_[i].resize(sizeY);
				for(int j  = 0; j < sizeY; j++){
					matrix_[i][j].resize(sizeZ);
				}
			}

			return 0;
		};

		int save(const string &path){

			ofstream f(path.data(), ios::out | ios::binary);

			for(int i = 0; i < (int) matrix_.size(); i++){
			    for(int j = 0; j < (int) matrix_[i].size(); j++){
					for(int k = 0; k < (int) matrix_[i][j].size(); k++){
			      		f.write((char *) &(matrix_[i][j][k]), sizeof(dataType));
					}
			    }
			}

			f.close();

			return 0;
		};

		void set(const int &x, const int &y, const int &z, 
			const dataType &value){
			matrix_[x][y][z] = value;
		}
		

	protected:

		vector<int>					size_;
		vector<vector<vector<dataType> > >	matrix_;

};

int main(int argc, char **argv){

	Matrix<double> m;
	m.setDimensions(3, 3, 1);  

  	m.set(0, 0, 0, -6.66);
 	m.set(0, 1, 0, 1);
  	m.set(0, 2, 0, 2);

	m.set(1, 0, 0, -1);
 	m.set(1, 1, 0, -6.66);
  	m.set(1, 2, 0, 1);

	m.set(2, 0, 0, -2);
 	m.set(2, 1, 0, -1);
  	m.set(2, 2, 0, -6.66);
/*
  matrix[1][0][0] = -1;
  matrix[1][1][0] = -6.66;
  matrix[1][2][0] = 1;

  matrix[2][0][0] = -2;
  matrix[2][1][0] = -1;
  matrix[2][2][0] = -6.66;
*/
	m.save("matrix.raw");
	m.load("matrix.raw");
	m.display();

  return 0;
}
