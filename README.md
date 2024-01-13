## Especificação:

<p>
Desenvolver uma aplicação multi-thread para processar uma matriz bidimensional contendo valores inteiros numa escala de 0 a 9. A ordem da matriz deve ser fornecida pelo usuário, podendo ser quadrada ou retangular. A matriz deverá ser gerada aleatoriamente e mostrada na tela. Pode-se determinar um tamanho máximo para a matriz na ordem de 1000x1000 elementos.
</p>

<p>
A matriz deverá ser percorrida, da esquerda para a direita, de cima para baixo, e cada elemento deverá ser substituído pela média aritmética simples de seus 8 vizinhos (truncada - parte inteira). Use uma thread para processar cada linha da matriz, mas observe a seguinte restrição: a thread que processa uma linha abaixo deve esperar os vizinhos da linha acima estarem prontos (processados) para então usá-los em seu processamento, mas poderá utilizar os prontos a direita, abaixo, a esquerda já processados por ela mesma e aguardar, se necessários, os pontos acima.
</p>


<p>
Ao final do processamento, a matriz resultante deverá ser mostrada na tela.
</p>


<p>
Equipe de no máximo 3 participantes.
</p>


<p>
Cada equipe deverá entregar o arquivo fonte (.c) e um relatório técnico contendo as seguintes informações: identificação dos participantes, descrição dos principais módulos desenvolvidos e auto-avaliação do funcionamento (elencar as partes que funcionam corretamente, as partes que não funcionam corretamente e sob quais circunstancias, bem como as partes que não foram implementadas.
</p>


<p>
Data de entrega: 04/02/2023, 23h55min.
</p>


<p>
<strong>OBS 1!</strong> Serão aceitas apenas entregas pelo Moodle, não sendo avaliadas as entregas feitas por email, whatsapp ou de qualquer outra forma.
</p>


<p>
<strong>OBS 2!</strong> Trabalhos com codificação similar, parecida, sofrerão descontos na nota e poderão até serem anulados, de acordo com o grau de similaridade.
</p>


<p>
<strong>OBS 3!</strong> Os trabalhos serão apresentados em data a ser determinada, após a entrega. Além disso, haverá uma avaliação escrita presencial sobre o trabalho, de caráter individual, na qual cada aluno deverá explicar a implementação do seu trabalho. A nota final do trabalho será uma composição das notas da implementação entregue, da apresentação e das avaliações individuais dos membros da equipe.</p>

