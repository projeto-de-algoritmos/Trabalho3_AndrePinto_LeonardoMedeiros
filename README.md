# Aplicação de algoritmo de algoritmo guloso

3º Exercício Prático - Projeto de análise de algoritmos - 2019.2 - UnB - Gama
=========================
André Lucas de Sousa Pinto - 17/0068251
Leonardo de Araujo Medeiros - 17/0038891

## Instalação
1. Faça o clone deste projeto com o comando ```$ git clone https://github.com/projeto-de-algoritmos/Trabalho3_AndrePinto_LeonardoMedeiros.git ```;
2. Altere para a o diretório do projeto com o comando ```$ cd Trabalho3_AndrePinto_LeonardoMedeiros/```;
3. Use o comando ```$ make``` para compilar o projeto;
4. Use a o comando ```$ make run coins=NUMERO``` para executar a aplicação. NUMERO deve ser um valor numérico de 8 a 14 e ser par.

OBS: caso não seja passada coins, ou nao seja um valor numérico de 8 a 14 o mesmo irá ter o valor padrao de 8.

## História
Idiosmar e Idioscreia eram um casal muito feliz, certo dia eles brigaram feio porque Idiosmar comeu a sobremesa de Idioscreia e a bela moca resolveu terminar. Nesse jogo voce joga com Idiosmar e seu objetivo e conseguir um lucro maior que o de Idioscreia na divisao de bens, por possuir um advogado melhor Idioscreia comeca primeiro e conseguiu tambem escolher uma regra de apenas pegar os bens das pontas.

## Ideia proposta
A ideia e exercitar sobre algoritmos gulosos. Nesse caso possuimos um vetor de N elementos, sendo N um numero par, e so podemos pegar os elementos da ponta. Caso a gente tente pegar sempre o maior elemento, isso nao garantiria que teriamos o melhor resultado pois poderia abrir abrir a possibilidade de pegar outro elemento ainda maior. A ideia entao e olhar pela soma entre as paridades, pegando a soma dos elementos das posicoes pares e comparando com a das posicoes impares e pegando a maior soma. Como o tamanho do vetor e par, garantimos que quem escolher primeiro ganha, pois ao escolher um valor da posicao par, nas pontas teriam dois valores impares, ou vice e versa, fazendo com que seja possivel pegar todos os valores pares ou todos os valores impares.

## Dependências
- g++ compiler

 Nota: Para desenvolvimento deste projeto também é feito uso da biblioteca [SFML](https://www.sfml-dev.org/index.php), todavia esta já se encontra inclusa no repositório a fim de faciltiar a instalação da aplicação. Respeitando devidamente a [licença](https://www.sfml-dev.org/license.php) sobre o código da biblioteca utilizada.
