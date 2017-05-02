/*
 * Código: Zoom Quadriculado.
 * Os pixel são "expandidos", desse modo é possivel criar uma imagem maior do que a original.
 * O valor de Zoom deve ser maior que 1.
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

	/* Define o zoom, se for 2 iremos quadriplicar o numero de pixels, um pixel sera transformado em 4
	 * Se o zoom for 3, iremos multiplicar o numero de pixels por 9, um pixel sera transofrmado em 9.
	 */


	Vec3b pixel;

	//Entrar com o valor de Zoom
	int zoom;
	cout << "Entre com um valor de Zoom: " << endl;
	cin >> zoom;

	//Carrega a foto
	Mat foto = imread("/home/vitor/Pictures/OutrasPessoas/ruivo/ruivo.jpg",IMREAD_COLOR);
	if(foto.empty()){
		cout << "Imagem nao encontrada" << endl;
		return 1;
	}

	//Cria a novo foto com tamanho maior;
	int x = (foto.rows)*zoom;
	int y = (foto.cols)*zoom;

	Mat imagem;
	imagem.create(x,y,CV_8UC3);

	cout << "Imagem criada. " << "Width: " << x << " Height: " << y << endl;

	//Percorre a imagem original e aumenta a quantidade de pixels.
	//Salva esses pixels em outra matriz.

	int s = 0; // Variavel para percorrer a linha da nova matriz
	int m = 0; // Variavel para percorrer a coluna da nova matriz

	for(int i=0;i<foto.rows;i++){
		m = 0;
		for(int j=0; j<foto.cols;j++){

			//Pega o pixel da imagem original;
			pixel = foto.at<Vec3b>(i, j);

			for(int z1=0;z1<zoom;z1++){
				for(int z2 = 0; z2<zoom;z2++){
					//cout << s+z1 << "," << m+z2 << endl;
					imagem.at<Vec3b>(s+z1,m+z2) = pixel;
				}
			}
			s = s++;
			m = m + zoom;
		}
		s = s + 2;
	}


	namedWindow("Zoom",WINDOW_AUTOSIZE);
	imshow("Zoom",imagem);
	waitKey(0);

	return 0;
}



