 /*
 Sistema HSB
 H = Hue (Tonalidade)
 S = Saturation (Saturação)
 V = Brightness (Brilho)
 */


#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat imagem;
int histograma[256];
int normalizado[256];

void validarValores(double h,double s, double b){
	if(h<0 || h>360){
		cout << "H nao esta entre [0,360]" << endl;
		exit(0);
	}else if(s<0 || s>1){
		cout << "S nao esta entre [0,1]" << endl;
		exit(0);
	}else if(b<0 || b>1){
		cout << "B nao esta entre [0,1]" << endl;
		exit(0);
	}
}

double getMax(double a, double b, double c){
	if (a>=b && a>=c) return a;
	else if (b >=a && b>= c) return b;
	else return c;
}

double getMin(double a, double b, double c){
	if (a<=b && a<=c) return a;
	else if (b <=a && b<= c) return b;
	else return c;
}

Mat abrirImagem(){
	string img = "/home/vitor/Pictures/OutrasPessoas/ruivo/ruivo.jpg";
	Mat imagem = imread(img,IMREAD_COLOR);

	return imagem;
}

Mat converter(){
	double r,g,b,h,s,v;
	double min,max;
	Vec3b pixel;

	//Variaveis para calculo
	double hi,f,p,q,t;

	Mat hsv = imagem.clone();
	for(int z=0; z<imagem.rows;z++){
		for(int j=0; j<imagem.cols;j++){

			pixel = imagem.at<Vec3b>(z,j);

			b = (pixel.val[0])/255.0;
			g = (pixel.val[1])/255.0;
			r = (pixel.val[2])/255.0;

			//Converter para HSV
			min = getMin(r,g,b);
			max = getMax(r,g,b);

			if(max==r && g>=b) h = 60*(g-b)/(max-min);
			else if(max==r && g<b) h = (60*(g-b)/(max-min)) + 360;
			else if(max==g) h = (60*(b-r)/(max-min)) + 120;
			else if(max==b) h = (60*(r-g)/(max-min)) + 240;

			s = (max-min)/max;
			v = max;

			r=g=b=0;

			validarValores(h,s,v);

			//Converter para RGB
			if(s==0){
				r = v;
				g = v;
				b = v;
			}else{
				hi = (int) (floor(h/60))%6;
				f = (h/60)-hi;
				p = v*(1-s);
				q = v*(1-f*s);
				t = v*(1-((1-f)*s));

				if(hi==0){
					r = v;
					g = t;
					b = p;
				}else if(hi==1){
					r = q;
					g = v;
					b = p;
				}else if(hi==2){
					r = p;
					g = v;
					b = t;
				}else if(hi==3){
					r = p;
					g = q;
					b = v;
				}else if(hi==4){
					r = t;
					g = p;
					b = v;
				}else if(hi==5){
					r = v;
					g = p;
					b = q;
				}else{
					cout << "Calculos Errados" << endl;
					exit(0);
				}

				r = r*255;
				g = g*255;
				b = b*255;

				hsv.at<Vec3b>(z,j).val[0] = b;
				hsv.at<Vec3b>(z,j).val[1] = g;
				hsv.at<Vec3b>(z,j).val[2] = r;
			}
		}
	}
	return hsv;
}


//inicia os histograma com valor 0
void iniciarHistograma(){
	 for(int i=0;i<256;i++) histograma[i] = 0;
}

// Preenche o histograma coletando dados da imagem.
void atualizarHistograma(){

	int r,g,b,aux;
	double v;

	Vec3b pixel;

	for(int z=0; z<imagem.rows;z++){
		for(int j=0; j<imagem.cols;j++){

			pixel = imagem.at<Vec3b>(z,j);

			b = (pixel.val[0]);
			g = (pixel.val[1]);
			r = (pixel.val[2]);

			v = getMax(r,g,b);

			aux = (int) v;
			histograma[aux]++;
		}
	}
}

// Normalizado é um vetor que faz a conversao necessária para equalizar a imagem
// normalizado[intensidade] = intensidadeNormalizada.
void equalizarHistograma(){

	double somatorio;
	double probabilidade;
	double div = imagem.rows*imagem.cols;

	for(int k=0;k<256;k++){
		somatorio = 0;
		for(int k2=0;k2<=k;k2++){
			probabilidade =  histograma[k2]/div;
		    somatorio = somatorio + probabilidade;
		}
		normalizado[k] = (int) (somatorio*255);
	}
}

void printarHistogramas(){

	for(int k=0;k<256;k++){
		cout << "QntPiels: " << histograma[k] << " - Intensidade(i): " << k << " - f(i) = " << normalizado[k] << endl;
	}
}

Mat equalizarImagem(){

	double canal,r,g,b;
	double h,s,v;

	double max,min;

	//Variaveis para calculo
	double hi,f,p,q,t;

	Mat equalizado = imagem.clone();
	for(int z = 0; z < equalizado.rows; z++){
		for(int j = 0; j < equalizado.cols; j++){

			b = equalizado.at<Vec3b>(z, j).val[0];
			g = equalizado.at<Vec3b>(z, j).val[1];
			r = equalizado.at<Vec3b>(z, j).val[2];


			//Acha o Y a partir dos valores RGB
			v = getMax(r,g,b);
			canal = (int) v;
			//Dado o Y acha o Y do histograma equalizado
			v = normalizado[(int) canal]/255.0;

			//O histograma nao deveria ser equalizado para o intervalo [0,1], mas sim para [0.1,0.9]


			r = r/255.0;
			g = g/255.0;
			b = b/255.0;

			max = getMax(r,g,b)/255.0;
			min = getMin(r,g,b)/255.0;


			if(max==r && g>=b) h = 60*(g-b)/(max-min);
			else if(max==r && g<b) h = (60*(g-b)/(max-min)) + 360;
			else if(max==g) h = (60*(b-r)/(max-min)) + 120;
			else if(max==b) h = (60*(r-g)/(max-min)) + 240;

			s = (max-min)/max;

			validarValores(h,s,v);

			//Converter para RGB
						if(s==0){
							r = v;
							g = v;
							b = v;
						}else{
							hi = (int) (floor(h/60))%6;
							f = (h/60)-hi;
							p = v*(1-s);
							q = v*(1-f*s);
							t = v*(1-((1-f)*s));

							if(hi==0){
								r = v;
								g = t;
								b = p;
							}else if(hi==1){
								r = q;
								g = v;
								b = p;
							}else if(hi==2){
								r = p;
								g = v;
								b = t;
							}else if(hi==3){
								r = p;
								g = q;
								b = v;
							}else if(hi==4){
								r = t;
								g = p;
								b = v;
							}else if(hi==5){
								r = v;
								g = p;
								b = q;
							}else{
								cout << "Calculos Errados" << endl;
								exit(0);
							}

							r = r*255;
							g = g*255;
							b = b*255;

							equalizado.at<Vec3b>(z,j).val[0] = b;
							equalizado.at<Vec3b>(z,j).val[1] = g;
							equalizado.at<Vec3b>(z,j).val[2] = r;
						}
	    }
	}

	return equalizado;

}



int main(){

	imagem = abrirImagem();
	if(imagem.empty()){
			cout << "Imagem nao encontrada" << endl;
			return 1;
	}

	iniciarHistograma();
	atualizarHistograma();
	equalizarHistograma();
	printarHistogramas();
	Mat hsv = equalizarImagem();





	namedWindow("EqualizadoHSV",WINDOW_AUTOSIZE);
	namedWindow("Original",WINDOW_AUTOSIZE);
	imshow("EqualizadoHSV",hsv);
	imshow("Original",imagem);
	waitKey(0);

	return 0;
}

