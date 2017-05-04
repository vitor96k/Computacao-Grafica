/*
 * Código: Imagem Negativa
 * Esse código faz a inversao de cores de uma imagem
 *
 * Vitor P. Aderaldo - UEL 2017
 */

//Funcao para inverter a cor
int inverterCor(int cor){
	return (255-cor);
}

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(){

	//Carrega a foto
	Mat imagem = imread("/home/vitor/Pictures/OutrasPessoas/ruivo/ruivo.jpg",IMREAD_COLOR);
	if(imagem.empty()){
		cout << "Imagem nao encontrada" << endl;
		return 1;
	}

	//Mais facil visualisar abrindo os colchetes.
	//Acessa os pixels e faz a inversao
	for(int i=0;i<imagem.rows;i++){
		for(int j=0;j<imagem.cols;j++){
			for(int z=0;z<3;z++){
				imagem.at<Vec3b>(i,j).val[z] = inverterCor(imagem.at<Vec3b>(i,j).val[z]);
			}
		}
	}

	imshow("Imagem",imagem);
	waitKey(0);

	return 1;

}