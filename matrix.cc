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

using namespace std;

class Matrix{

	public:
	
		Matrix(){
			imageDataReader_ = vtkSmartPointer<vtkXMLImageDataReader>::New();
		}
	
		int loadVTI(const string &path, const int &fieldId = 0){
			path.data();
			imageDataReader_->SetFileName(path.data());
			imageDataReader_->Update();
			vtkImageData *imageData = imageDataReader_->GetOutput();
				
			int* dims = imageData->GetDimensions();
  			// int dims[3]; // can't do this

			size_.push_back(dims[0]);
			size_.push_back(dims[1]);
			size_.push_back(dims[2]);

			std::cout << "Dims: " << " x: " << size_[0] << " y: " << size_[1] << " z: " << size_[2] << std::endl;
			
			vtkDataArray *arrayU = imageData->GetPointData()->GetArray("U");
			vtkDataArray *arrayV = imageData->GetPointData()->GetArray("V");
			vtkDataArray *arrayW = imageData->GetPointData()->GetArray("W");
			vtkDataArray *arrayP = imageData->GetPointData()->GetArray("P");
			if (!arrayU)
				printf("Erreur U pas reconu\n");
			if (!arrayV)
				printf("Erreur V pas reconu\n");
			if (!arrayW)
				printf("[Warning] W pas reconu : Cas 2D\n");
			if (!arrayP)
				printf("Erreur P pas reconu\n");
			
			switch(arrayU->GetDataType()){
				case VTK_DOUBLE:
					// WARNING: dims[2] == 0?
					matrixU_.resize(size_[0]*size_[1]*size_[2]);
					for(int i = 0; i < arrayU->GetNumberOfTuples(); i++){
						//array->GetTuple1(i, &(matrix_[i]));
						arrayU->GetTuple(i, &(matrixU_[i]));
					}
					
					break;
				default:
					cerr << "Unsupported data type" << endl;
					break;
			}
			
			
			switch(arrayV->GetDataType()){
				case VTK_DOUBLE:
					// WARNING: dims[2] == 0?
					matrixV_.resize(size_[0]*size_[1]*size_[2]);
					for(int i = 0; i < arrayV->GetNumberOfTuples(); i++){
						//array->GetTuple1(i, &(matrix_[i]));
						arrayV->GetTuple(i, &(matrixV_[i]));
					}
					
					break;
				default:
					cerr << "Unsupported data type" << endl;
					break;
			}
			
			if(size_[2]>1){ // cas en 3D
				switch(arrayW->GetDataType()){
					case VTK_DOUBLE:
						// WARNING: dims[2] == 0?
						matrixW_.resize(size_[0]*size_[1]*size_[2]);
						for(int i = 0; i < arrayW->GetNumberOfTuples(); i++){
							//array->GetTuple1(i, &(matrix_[i]));
							arrayW->GetTuple(i, &(matrixW_[i]));
						}
					
						break;
					default:
						cerr << "Unsupported data type" << endl;
						break;
				}
			}
			
				
			
			switch(arrayP->GetDataType()){
				case VTK_DOUBLE:
					// WARNING: dims[2] == 0?
					matrixP_.resize(size_[0]*size_[1]*size_[2]);
					for(int i = 0; i < arrayP->GetNumberOfTuples(); i++){
						//array->GetTuple1(i, &(matrix_[i]));
						arrayP->GetTuple(i, &(matrixP_[i]));
					}
					
					break;
				default:
					cerr << "Unsupported data type" << endl;
					break;
			}
			

			ofstream f("matrixU.raw", ios::out | ios::binary);
			for(int i = 0; i<(int)matrixU_.size();i++)
				f.write((char *) &(matrixU_[i]), sizeof(double));
			f.close();

			FILE * fichier = fopen("tmp.txt", "w");
			fprintf(fichier,"%d %d %d %d",(int)matrixU_.size(),size_[0],size_[1],size_[2]);
			fclose(fichier);
			
			ofstream f2("matrixV.raw", ios::out | ios::binary);
			for(int i = 0; i<(int)matrixV_.size();i++)
				f2.write((char *) &(matrixV_[i]), sizeof(double));
			f2.close();
			
			ofstream f3("matrixW.raw", ios::out | ios::binary);
			for(int i = 0; i<(int)matrixW_.size();i++)
				f3.write((char *) &(matrixW_[i]), sizeof(double));
			f3.close();
			
			ofstream f4("matrixP.raw", ios::out | ios::binary);
			for(int i = 0; i<(int)matrixP_.size();i++)
				f4.write((char *) &(matrixP_[i]), sizeof(double));
			f4.close();
			
			return 0;
		}
		
		int saveVTI(const string &path,int mod){
			int taille,a,b,c;
			FILE * fichier = fopen("tmp.txt", "r");
			fscanf(fichier,"%d %d %d %d",&taille,&a,&b,&c);
			fclose(fichier);
			if(mod==0){
				ifstream f2("matrix2U.raw", ios::in | ios::binary);
				for(int i = 0; i<(int)taille;i++){
					double a;
					f2.read((char *) &(a), sizeof(double));
					matrixU_.insert(matrixU_.begin()+i, a);
				}f2.close();
			}
			else{
				ifstream f2("matrix3U.raw", ios::in | ios::binary);
				for(int i = 0; i<(int)taille;i++){
					double a;
					f2.read((char *) &(a), sizeof(double));
					matrixU_.insert(matrixU_.begin()+i, a);
				}f2.close();
			}
			
			if(mod==0){
				ifstream f3("matrix2V.raw", ios::in | ios::binary);
				for(int i = 0; i<(int)taille;i++){
					double a;
					f3.read((char *) &(a), sizeof(double));
					matrixV_.insert(matrixV_.begin()+i, a);
				}f3.close();
			}
			else{
				ifstream f3("matrix3V.raw", ios::in | ios::binary);
				for(int i = 0; i<(int)taille;i++){
					double a;
					f3.read((char *) &(a), sizeof(double));
					matrixV_.insert(matrixV_.begin()+i, a);
				}f3.close();
			}
			
			if(mod==0){
				ifstream f3("matrix2W.raw", ios::in | ios::binary);
				for(int i = 0; i<(int)taille;i++){
					double a;
					f3.read((char *) &(a), sizeof(double));
					matrixW_.insert(matrixW_.begin()+i, a);
				}f3.close();
			}
			else{
				ifstream f3("matrix3W.raw", ios::in | ios::binary);
				for(int i = 0; i<(int)taille;i++){
					double a;
					f3.read((char *) &(a), sizeof(double));
					matrixW_.insert(matrixW_.begin()+i, a);
				}f3.close();
			}
			
			if(mod==0){
				ifstream f4("matrix2P.raw", ios::in | ios::binary);
				for(int i = 0; i<(int)taille;i++){
					double a;
					f4.read((char *) &(a), sizeof(double));
					matrixP_.insert(matrixP_.begin()+i, a);
				}f4.close();
			}
			else{
				ifstream f4("matrix3P.raw", ios::in | ios::binary);
				for(int i = 0; i<(int)taille;i++){
					double a;
					f4.read((char *) &(a), sizeof(double));
					matrixP_.insert(matrixP_.begin()+i, a);
				}f4.close();
			}
			vtkSmartPointer<vtkImageData> imageData = 
				vtkSmartPointer<vtkImageData>::New();
			
			// WARNING on size_[2]
			size_.insert(size_.begin()+0, a);
			size_.insert(size_.begin()+1, b);
			size_.insert(size_.begin()+2, c);
			imageData->SetDimensions(size_[0], size_[1], size_[2]);
			
			vtkSmartPointer<vtkDoubleArray> array = 
				vtkSmartPointer<vtkDoubleArray>::New();

			vtkSmartPointer<vtkDoubleArray> array2 = 
				vtkSmartPointer<vtkDoubleArray>::New();
				
			vtkSmartPointer<vtkDoubleArray> array3 = 
				vtkSmartPointer<vtkDoubleArray>::New();
				
			vtkSmartPointer<vtkDoubleArray> array4 = 
				vtkSmartPointer<vtkDoubleArray>::New();
				
			array->SetNumberOfTuples(size_[0] * size_[1] * size_[2]);
			for(int i = 0; i < array->GetNumberOfTuples(); i++){
				array->SetTuple1(i, (matrixU_[i])); //matrixU au lieu de matrix
			}

			array2->SetNumberOfTuples(size_[0] * size_[1] * size_[2]);
			for(int i = 0; i < array2->GetNumberOfTuples(); i++){
				array2->SetTuple1(i, (matrixP_[i])); //matrixP au lieu de matrix
			}

			array3->SetNumberOfTuples(size_[0] * size_[1] * size_[2]);
			for(int i = 0; i < array3->GetNumberOfTuples(); i++){
				array3->SetTuple1(i, (matrixV_[i])); //matrixW au lieu de matrix
			}

			array4->SetNumberOfTuples(size_[0] * size_[1] * size_[2]);
			for(int i = 0; i < array4->GetNumberOfTuples(); i++){
				array4->SetTuple1(i, (matrixW_[i])); //matrixW au lieu de matrix
			}

			array->SetName("U");
			array2->SetName("P");
			array3->SetName("V");
			array4->SetName("W");

			imageData->GetPointData()->AddArray(array);
			imageData->GetPointData()->AddArray(array2);
			imageData->GetPointData()->AddArray(array3);
			imageData->GetPointData()->AddArray(array4);
			
			vtkSmartPointer<vtkXMLImageDataWriter> writer = 
				vtkSmartPointer<vtkXMLImageDataWriter>::New();
			writer->SetFileName(path.data());
			writer->SetInputData(imageData);
			writer->Write();
		
			return 0;
		}
	
		double* getDataU() { return matrixU_.data(); };
		double* getDataV() { return matrixV_.data(); };
		double* getDataW() { return matrixW_.data(); };
		double* getDataP() { return matrixP_.data(); };

	protected:

		vector<int>	size_;
		vector<double>	matrixU_, matrixV_,matrixW_ ,matrixP_;
		vtkSmartPointer<vtkXMLImageDataReader> imageDataReader_;

};


int main(int argc, char **argv){
	
	Matrix m;
	if( atoi(argv[1])==0){
		m.loadVTI(argv[2]);
	}
	else{
		if( atoi(argv[1])==1){
			m.saveVTI(argv[2],0);
		}else{
			m.saveVTI(argv[2],1);
		}
	}
  return 0;
}
