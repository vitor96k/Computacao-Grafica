/*
 * Código: Zoom Linear.
 * Novos pixel são criado por interpolação, desse modo é possivel dar um zoom "mais suave"
 *
 * Complexidade: 3n² =>  Θ(n²)
 * Pode ser feito percorrendo uma vez a matriz (n²), porém é mais didatico percorrer 3 vezes.
 *
 *
 * Vitor P. Aderaldo - UEL 2017
 */


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

	Vec3b pixel,epixel,dpixel,cpixel,bpixel;

	//Valor de Zoom
	int zoom = 2;

	//Carrega a foto
	Mat foto = imread("/home/vitor/Pictures/OutrasPessoas/ruivo/ruivo.jpg",IMREAD_COLOR);
	if(foto.empty()){
		cout << "Imagem nao encontrada" << endl;
		return 1;
	}

	//Cria a novo foto com tamanho maior;
	int x = (foto.rows)+(foto.rows-1);
	int y = (foto.cols)+(foto.cols-1);

	Mat imagem;
	imagem.create(x,y,CV_8UC3);

	cout << "Imagem criada. " << "Width: " << x << " Height: " << y << endl;

	//Percorre a imagem original e aumenta a quantidade de pixels.
	//Salva esses pixels em outra matriz.

	int s = 0; // Variavel para percorrer a linha da nova matriz
	int m = 0; // Variavel para percorrer a coluna da nova matriz



	//Distribuir os pixels uniformemente
	for(int i=0;i<foto.rows;i++){
		for(int j=0; j<foto.cols;j++){

			//Pega o pixel da imagem original;
			pixel = foto.at<Vec3b>(i, j);

			//Distruibui o pixel
			imagem.at<Vec3b>(zoom*i,zoom*j) = pixel;
			//cout << "x: " << zoom*i << " y: " << zoom*j << endl;
		}
	}

	//Interpolacao só das linhas
	for(int i=0;i<imagem.rows;i=i+2){
		for(int j=1;j<imagem.cols;j=j+2){

			//Pega o pixel da esquerda e da direita
			epixel = imagem.at<Vec3b>(i,j-1);
			dpixel = imagem.at<Vec3b>(i,j+1);

			//Faz a media entre os pixels.
			pixel = (epixel + dpixel)/2;

			imagem.at<Vec3b>(i,j) = pixel;

			//cout << "x: " << i << " y: " << j << endl;
		}
	}

	for(int i=1;i<imagem.rows;i=i+2){
		for(int j=0;j<imagem.cols;j++){

			//Pega o pixel que esta acima e abaixo.
			cpixel = imagem.at<Vec3b>(i+1,j);
			bpixel = imagem.at<Vec3b>(i-1,j);

			//Faz a media entre os pixels.
			pixel = (epixel + dpixel)/2;

			imagem.at<Vec3b>(i,j) = pixel;

			//cout << "x: " << i << " y: " << j << endl;
			}
		}


	namedWindow("Zoom",WINDOW_AUTOSIZE);
	namedWindow("Normal",WINDOW_AUTOSIZE);
	imshow("Zoom",imagem);
	imshow("Normal",foto);
	waitKey(0);

	return 0;
}


