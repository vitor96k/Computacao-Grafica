//Caso a imagem seja colorida ela sera convertida para niveis de cinza.

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


	//Dados para carregar a imagem
	string imageName = "/home/vitor/Pictures/OutrasPessoas/ruivo/ruivo.jpg";
    Mat image = imread(imageName, IMREAD_COLOR);

    //Histograma
    int cores[256];
    for(int i=0;i<256;i++) cores[i] = 0;

    //Histograma Equalizado
    int normalizado[256];

    //Verificar se a imagem existe.
    if(image.empty())    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

    //Transformando a imagem para niveis de cinza
    Mat gray_image = image.clone();
    float soma;
    //Percorre a imagem
    for(int i = 0; i < gray_image.rows; i++){
        for(int j = 0; j < gray_image.cols; j++){

        	//Pega o pixel
            Vec3b bgrPixel = gray_image.at<Vec3b>(i, j);

            //Calcula a media dos niveis RGB
            soma =   bgrPixel.val[0] +   bgrPixel.val[1] +   bgrPixel.val[2];
            soma = soma/3;

            //Atribui essa media aos canais
            gray_image.at<Vec3b>(i,j).val[0] = (int) soma;
            gray_image.at<Vec3b>(i,j).val[1] = (int) soma;
            gray_image.at<Vec3b>(i,j).val[2] = (int) soma;

            //Atualiza o histograma
            cores[(int) soma]++;
        }
    }

    //Quantidade de pixels
    double div = gray_image.rows * gray_image.cols;


    double somatorio;
    double probabilidade;

    //Equalizando histograma
    for(int k=0;k<256;k++){
    		somatorio = 0;
    	for(int k2=0;k2<=k;k2++){
    		probabilidade =  cores[k2]/div;
    		somatorio = somatorio + probabilidade;
    	}
    	normalizado[k] = (int) (somatorio*255);
    }

    //Printar histograma Equalizado
    for(int k=0;k<256;k++) cout << normalizado[k] << endl;

    //Utilizando o histograma equalizado para alterar a imagem
    int canal;
    Mat equalizado = gray_image.clone();
    for(int i = 0; i < equalizado.rows; i++){
        for(int j = 0; j < equalizado.cols; j++){

        	//Acessa a intensidade do canal
        	//Como a imagem é cinza os canais RGB tem o mesmo valor
            canal = equalizado.at<Vec3b>(i, j).val[0];

            //Procura essa intensidade no histograma equalizado e atribui o novo valor
            equalizado.at<Vec3b>(i,j).val[0] = normalizado[canal];
            equalizado.at<Vec3b>(i,j).val[1] = normalizado[canal];
            equalizado.at<Vec3b>(i,j).val[2] = normalizado[canal];

            cores[(int) soma]++;
        }
    }

    //Criar Janela para mostrar imagem
    namedWindow("Cinza", WINDOW_AUTOSIZE );
    namedWindow("Equalizado", WINDOW_AUTOSIZE );

    // Mostrar a imagem
    imshow( "Cinza", gray_image);
    imshow( "Equalizado", equalizado);

    // Espera ate q uma tecla seja pressionada.
    waitKey(0);

    return 0;
}
