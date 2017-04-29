/*
 * Código feito para converter uma imagem RGB para YIQ e logo em seguida converter para RGB novamente
 * Ao alterar para YIQ é possível alterar o brilho da imagem
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


	//Abrir imagem
	string img = "/home/vitor/Pictures/OutrasPessoas/ruivo/ruivo.jpg";
	Mat imagem = imread(img,IMREAD_COLOR);

	if(imagem.empty()){
		cout << "Imagem nao encontrada" << endl;
		return 1;
	}

	Mat yib = imagem.clone();

	//Conifiguraces para converter para YIQ:
	double brilho; //Quanto maior o brilho, maior a intensidade que vai aumentar ou diminur. Brilho = [0,1]

	//O canal Y deve estar entre [0,1], porém para se ter uma qualidade boa é melhor deixar entre [0.3,0.7]
	double miny = 0.3;
	double maxy = 0.7;

	int opcao;

	//Variaveis para operar os pixel na matriz
	double r,g,b;
	double y,i,q;
	Vec3b pixel;

	cout << "Entre com uma das opcoes:" << endl << "1 - Diminuir Brilho" << endl << "2 - Aumentar Brilho" << endl << "-> " ;
	cin >> opcao;
	cout << "Entre com um valor entre [0,1] para intensificar a opção que foi escolhida" << endl << "-> ";
	cin >> brilho;

	//Varrer a Imagem(Matriz)
	for(int z=0; z<yib.rows;z++){
		for(int j=0; j<yib.cols;j++){

			//Pega o pixel
			pixel = yib.at<Vec3b>(z,j);

			//Pega os valores RGB do pixel e divide por 255 para realizar a conversao para YIQ
			r = double (pixel.val[0])/255;
			g = double (pixel.val[1])/255;
			b = double (pixel.val[2])/255;

			//Converter para YIQ
			y = (0.299*r) + (0.587*g) + (0.114*b);
			i = (0.74*(r-y)) - (0.27*(b-y));
			q = (0.48*(r-y)) + (0.41*(b-y));

			if(opcao==1) y = y - ((y-miny)*brilho); //Caso a opcao seja diminuir o brilho
			else y = y + (maxy-y)*brilho; //Caso a opcao seja aumentar o brilho

			//Verifica se os canais estao no intervalo correto.
			if(y<0 || y>1){
				cout << "Y nao esta entre [0,1]" << endl;
				return 1;
			}else if(i<-0.5957 || i>0.5957){
				cout << "I nao esta entre [-0.5957,0.5957]" << endl;
				return 1;
			}else if(q<-0.5226 || q>0.5226){
				cout << "Q nao esta entre [-0.5226,5.226]" << endl;
				return 1;
			}

			//YIB para RGB:
			r = y + (0.956*i) + (0.621*q);
			g = y - (0.272*i) - (0.647*q);
			b = y - (1.106*i) + (1.703*q);

			//Salva na imagem os novos pixels RGB
			yib.at<Vec3b>(z,j).val[0] = r*255;
			yib.at<Vec3b>(z,j).val[1] = g*255;
			yib.at<Vec3b>(z,j).val[2] = b*255;
		}
	}

	namedWindow("alterado2",WINDOW_AUTOSIZE);
	namedWindow("normal",WINDOW_AUTOSIZE);
	imshow("alterado2",yib);
	imshow("normal",imagem);
	waitKey(0);

	return 0;
}

