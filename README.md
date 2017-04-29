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
<br />4) Converter o YIQ para RGB usando multiplicação de matrizes e atribuir essa conversao ao pixel. <br />

<br />
	
![Alt text](/images/yiqrgb.png?raw=true "Modelo")
<br />
