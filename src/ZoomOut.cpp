/*
 * Código: Zoom Out
 * Diminui o tamanho de pixels, um conjunto de pixels é transformado em apenas 1.
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

	Vec3b pixel;

	//Valor de Zoom. Quanto maior o zoom, mais a imagem sera diminuida
	int zoom;
	cout << "Entre com um valor de Zoom: " << endl;
	cin >> zoom;

	//Carrega a foto
	Mat foto = imread("/home/vitor/Pictures/OutrasPessoas/ruivo/ruivo.jpg",IMREAD_COLOR);
	if(foto.empty()){
		cout << "Imagem nao encontrada" << endl;
		return 1;
	}

	//Cria a novo foto com tamanho menor;
	//Vamos criar uma imagem zoom vezes menor
	int x = ceil((foto.rows)/zoom);
	int y = ceil((foto.cols)/zoom);

	Mat imagem;
	imagem.create(x,y,CV_8UC3);

	cout << "Imagem criada. " << "Width: " << x << " Height: " << y << endl;


	int s = 0; // Variavel para percorrer a linha da nova matriz
	int m = 0; // Variavel para percorrer a coluna da nova matriz

	int r=0,g=0,b=0;

	//Percorre a imagem
	for(int i=0;i<foto.rows;i=i+zoom){

		m = 0;
		for(int j=0; j<foto.cols;j=j+zoom){

			//acesssa zoom*zoom pixels a cada iteracao.
			for(int z1=0;z1<zoom;z1++){
				for(int z2 = 0; z2<zoom;z2++){
					pixel = foto.at<Vec3b>(i+z1, j+z2);

					r = r + pixel.val[0];
					g = g + pixel.val[1];
					b = b + pixel.val[2];
				}
			}

			//Faz a media dos (zoom*zoom) pixel capturados
			r = r/(zoom*zoom);
			g = g/(zoom*zoom);
			b = b/(zoom*zoom);

			//Atribui essa media a uma entrada da matriz.
			imagem.at<Vec3b>(s,m).val[0] = r;
			imagem.at<Vec3b>(s,m).val[1] = g;
			imagem.at<Vec3b>(s,m).val[2] = b;

			//Reinicia os valores de rgb.
			r = 0;
			g = 0;
			b = 0;

			m++;
		}
		s++;
	}

	namedWindow("ZoomOut",WINDOW_AUTOSIZE);
	imshow("ZoomOut",imagem);
	waitKey(0);
	return 0;
}
