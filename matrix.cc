#include <fstream>
#include <vector>
#include <iostream>
#include <vtkXMLImageDataReader.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkVersion.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include "param.h"

using namespace std;
int const taille = NX * NY * NZ;

class Matrix{

	public:
	
		Matrix(){
			imageDataReader_ = vtkSmartPointer<vtkImageData>::New();
		}
	
		int loadVTI(const string &path, const int &fieldId = 0){
			
			imageDataReader_->SetFileName(path.data());
			imageDataReader_->Update();
			vtkImageData *imageData = imageDataReader_->GetOuput();
			
			imageData->GetDimensions(size_.data());
			
			vtkDataArray *array = imageData->GetPointData()->GetArray(fieldId);
			switch(array->GetDataType()){
				case VTK_DOUBLE:
					// WARNING: dims[2] == 0?
					matrix_.resize(size_[0]*size_[1]*size_[2]);
					for(int i = 0; i < array->GetNumberOfTuples(); i++){
						//array->GetTuple1(i, &(matrix_[i]));
						array->GetTuple(i, &(matrix_[i]));
					}
					
					break;
				default:
					cerr << "Unsupported data type" << endl;
					break;
			}
			
			return 0;
		}
		
		int saveVTI(const string &path){
		
			vtkSmartPointer<vtkImageData> imageData = 
				vtkSmartPointer<vtkImageData>::New();
				
			// WARNING on size_[2]
			imageData->SetDimensions(size_[0], size_[1], size_[2]);
			
			vtkSmartPointer<vtkDoubleArray> array = 
				vtkSmartPointer<vtkDoubleArray>::New();
		
			array->SetNumberOfTuples(size_[0] * size_[1] * size_[2]);
			for(int i = 0; i < array->GetNumberOfTuples(); i++){
				array->SetTuple1(i, (matrix_[i]));
			}
			
			array->SetName("OutputValues");
			imageData->GetPointData()->AddArray(array);
			
			vtkSmartPointer<vtkXMLImageDataWriter> writer = 
				vtkSmartPointer<vtkXMLImageDataWriter>::New();
			writer->SetFileName(path.data());
			writer->SetInputData(imageData);
			writer->Write();
		
			return 0;
		}
	
/*		int load(const string &path){

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
		};*/
		
		/*
		void displaymat(){
			for(int i = 0; i < (int) matrix_.size(); i++){
			    for(int j = 0; j < (int) matrix_[i].size(); j++){
					for(int k = 0; k < (int) matrix_[i][j].size(); k++){
						cout << matrix_[i][j][k] << "\t";
					}
				
			    }
				cout <<endl;
			}
		};
		
		void displayarray(){
			for(int i = 0; i < (int) matrix_.size(); i++){
			    for(int j = 0; j < (int) matrix_[i].size(); j++){
					for(int k = 0; k < (int) matrix_[i][j].size(); k++){
						cout << array_[i + matrix_.size() * (j + matrix_[i].size() * k)] << "\t";
					}
				
			    }
				cout <<endl;
			}
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
		};

		void convert(){
			for(int i = 0; i < (int) matrix_.size(); i++){
			    for(int j = 0; j < (int) matrix_[i].size(); j++){
					for(int k = 0; k < (int) matrix_[i][j].size(); k++){
						array_[i + matrix_.size() * (j + matrix_[i].size() * k)] = matrix_[i][j][k];
					}
				}
			}
			

		};*/

		double* getData() { return matrix_.data(); };

	protected:

		vector<int>	size_;
		vector<double>	matrix_;
		vtkSmartPointer<vtkImageData> imageDataReader_;

};


int main(int argc, char **argv){
	
	Matrix m;
	
	m.loadVTI("testMatrix.vti");
	m.getData();
	
	
	
	/*
	m.setDimensions(3, 3, 1);  

  	m.set(0, 0, 0, (char)2);
 	m.set(0, 1, 0, (char)1);
  	m.set(0, 2, 0, (char)2);

	m.set(1, 0, 0, (char)-1);
 	m.set(1, 1, 0, (char)2);
  	m.set(1, 2, 0, (char)1);

	m.set(2, 0, 0, (char)-2);
 	m.set(2, 1, 0, (char)-1);
  	m.set(2, 2, 0, (char)2);

	m.save("matrix.raw");
	m.load("matrix.raw");
	m.convert();
	m.displaymat();
	m.displayarray();*/

  return 0;
}
