/*
 * Código feito para converter uma imagem em Preto e Branco
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

	//Contar cores para fazer um histograma de escalas de cinza caso queira.
	int cores[256];

	//Inicia em zero todas escalas de cinza.
	for(int i=0;i<256;i++) cores[i] = 0;

	//Pegar o diretoria da imagem
    string imageName = "/home/vitor/Pictures/OutrasPessoas/ruivo/ruivo.jpg";

    //Ler a imagem e armazenar na matriz
    Mat image = imread(imageName, IMREAD_COLOR);

    //Verificar se foi lida
    if(image.empty())    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

	//Trabalhar com uma copia da imagem
    Mat gray_image = image.clone();    
    int soma;
    
    //Percorrer a Imagem(matriz)
    for(int i = 0; i < gray_image.rows; i++){
        for(int j = 0; j < gray_image.cols; j++){
			
			//Pega o Pixel
            Vec3b bgrPixel = gray_image.at<Vec3b>(i, j);
			
			//Soma os valores RGB do pixel e divide por 3.
            soma =   bgrPixel.val[0] +   bgrPixel.val[1] +   bgrPixel.val[2];
            soma = soma/3;
			
			//Atribui essa media a cada canal, assim todos canais desse pixel imitirao a mesma intensidade de cores RGB.
            gray_image.at<Vec3b>(i,j).val[0] = soma;
            gray_image.at<Vec3b>(i,j).val[1] = soma;
            gray_image.at<Vec3b>(i,j).val[2] = soma;
			
			//Coloca no histograma qual escala de cinza foi utilizada.
            cores[soma] = cores[soma] + 1;
        }
    }

    //Criar Janela para mostrar imagem
    namedWindow("Normal", WINDOW_AUTOSIZE );
    namedWindow( "Cinza", WINDOW_AUTOSIZE );

    // Mostrar a imagem
    imshow( "Normal", image );
    imshow( "Cinza", gray_image );

    // Espera ate q uma tecla seja pressionada.
    waitKey(0);
	
	//Mostrar histograma
    for(int i=0;i<256;i++) cout << i << ": " << cores[i] << endl;

    return 0;
}
