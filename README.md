# Computacao-Grafica

Esse repositório contem os principais códigos feitos para a disciplina de Computacao Grafica. Segue abaixo os programas feitos e explicados.
<br /> As explicações apenas mostram uma ideia geral sobre a lógica, outros detalhes estao comentados no código fonte.

<h2> Preto e Branco </h2>
Código para converter uma imagem colorida em preto e branco.
<br />Arquivo: pretobranco.cpp


<br />
<br />1) Acessar cada pixel
<br />2) Acessar os canais RGB de cada pixel
<br />3) Somar os valores desse canais e dividir por 3 (média)
<br />4) Atribuir essa média aos canais RGB.

<h2> RGB e YIQ - Alterar Brilho</h2>
Código para alterar o brilho da imagem ao converter RGB em YIQ e YIQ em RGB.
<br />Arquivo: yiq.cpp
<br />
<br />1) Acessar cada pixel
<br />2) Acessar os canais RGB de cada pixel
<br />3) Converter o RGB para YIQ usando multiplicação de matrizes <br />

<br />
	
![Alt text](/images/rgbyiq.png?raw=true "Modelo")
<br />

<br />4) Alterar o canal Y que é responsavel pelo brilho, aumentando ou diminuindo o valor.
<br />5) Converter o YIQ para RGB usando multiplicação de matrizes e atribuir essa conversao ao pixel. <br />

<br />
	
![Alt text](/images/yiqrgb.png?raw=true "Modelo")
<br />

<h2> Zoom Quadriculado </h2>
Código para dar zoom em uma imagem, o tamanho do zoom é definido pelo usuario.
<br />Arquivo: ZoomQuad.cpp
<br />
<br />1) Criar uma matriz maior para salvar a imagem com zoom.
<br />2) Acessar cada pixel
<br />3) Inserir esse pixel em varias posicoes na matriz recentemente criada.
<br />
	
![Alt text](/images/zoomQuad.png?raw=true "Modelo")
<br />

<h2> Imagem Negativa </h2>
Código para dar deixar a imagem negativa, invertendo os valores RGB.
<br />Arquivo: negativo.cpp
<br />
<br />1) Acessar cada pixel
<br />2) Acessar os canais RGB de cada pixel
<br />3) Calcula o inverso de cada canal. Inverso = 255 - Canal.
<br />4) Atribuir esse novo valor a imagem(pixel).

<h2> Zoom In (Linear) </h2>
Código para dar zoom em uma imagem utilizando interpolação.
<br />Arquivo: ZoomLinear.cpp
<br />
<br />1) Criar uma matriz maior para salvar a imagem com zoom.
<br />2) Acessar cada pixel
<br />3) Distribuir os pixels uniformemente na nova matriz.
<br />4) Para cada espaço vazio na nova matriz atribuir um pixel apartir de um calculo entre os vizinhos.
<br />
	
![Alt text](/images/zoomIn.png?raw=true "Modelo")
<br />

<h2> Zoom Out - Diminuir</h2>
Código para diminuir o tamanho da imagem utilizando interpolação, o tamanho do zoom é definido pelo usuario.
<br />Arquivo: ZoomOut.cpp
<br />
<br />1) Criar uma matriz menor para salvar a imagem com zoom.
<br />2) Acessar um conjunto de pixels.
<br />3) Calcula a media desse conjunto de pixels
<br />4) Atribuir essa média a nova matriz.
<br />
	
![Alt text](/images/zoomOu.png?raw=true "Modelo")
<br />

<h2> Equalizar Histograma</h2>
Código para diminuir o tamanho da imagem utilizando interpolação, o tamanho do zoom é definido pelo usuario.
<br />Arquivo: ZoomOut.cpp
<br />
<br />1) Criar uma matriz menor para salvar a imagem com zoom.
<br />2) Acessar um conjunto de pixels.
<br />3) Calcula a media desse conjunto de pixels
<br />4) Atribuir essa média a nova matriz.
<br />
	
![Alt text](/images/zoomOu.png?raw=true "Modelo")
<br />

<h2> Equalizar Histograma HSV (canal V)</h2>
Código para diminuir o tamanho da imagem utilizando interpolação, o tamanho do zoom é definido pelo usuario.
<br />Arquivo: ZoomOut.cpp
<br />
<br />1) Criar uma matriz menor para salvar a imagem com zoom.
<br />2) Acessar um conjunto de pixels.
<br />3) Calcula a media desse conjunto de pixels
<br />4) Atribuir essa média a nova matriz.
<br />
	
![Alt text](/images/zoomOu.png?raw=true "Modelo")
<br />





