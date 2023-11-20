# Fast String Kernel
Fast string kernel é o String Kernel que possui complexidade temporal O(n), baseado na utilização de árvores de sufixos de Ukkonens e um algoritmo de busca denominado Matching Statistics [1]. O desenvolvimento desse kernel foi realizado como projeto de iniciação científica do curso de Engenharia de Computação na Universidade Tecnológica Federal do Paraná (UTFPR), tendo a mesma instituição financiado o desenvolvimento do mesmo.

## Árvore de Sufixos de Ukkonen
O modelo de árvore de sufixos utilizado é a árvore de sufixos de Ukkonen, que dispõe de uma construção da estrutura em tempo O(n) [2]. A árvore de sufixos utilizada foi implementada por Matt Porrit, encontrando-se sob a licença GNU 3.0, dispónivel no repositório: https://github.com/mattporritt/suffix_tree
Onde foram obtidos os arquivos suffix_tree.c e o header suffix_tree.h. Agradeço profundamente ao Matt Porrit por ter realizado e disponibilizado a implementação dessa estrutra.

## Matching Statistics
O algortimo de busca e corrêspondência matching statistics foi implementado pelos autores desse projeto possuindo empiricamente o tempo de busca O(n) [3].

## Dados biologicós
Os dados utilizados presentes na pasta data pertencem a ferramenta CoDan [4], dispónivel no repositório: https://github.com/pedronachtigall/CodAn

##Utilização:
Para utilizar o FSK é necessário baixar o repositório e gerar a matriz K por meio do kernel.py sendo necessário descompactar os arquivos da pasta data e selecionar a base necessária, há um exemplo dentro do arquivo kernel.py que demonstra como deve ser realizada a leitura dos dados. Após isso é necessário inserir o peso requerido para o Kernel.

## LICENÇA
[GNU 3.0]

## Referências:
[1] VISHWANATHAN, S. V. N; SMOLA, Alexander J. Fast kernels for string and tree matching. Proceedings of the 15th International Conference on Neural Information Processing Systems, p. 585–592, 2002.

[2] UKKONEN, E. On-line construction of suffix trees. Algorithmica, v. 14, n. 3, p. 249–260, 1995.

[3] CHANG, W. I.; LAWLER, E. L. Sublinear approximate string matching and biological applications. Algorithmica, v. 12, n. 4, p. 327–344, 1994.

[4] NACHTIGALL, Pedro G; KASHIWABARA, Andre Y; DURHAM, Alan M. CodAn: predictive models for precise identification of coding regions in eukaryotic transcripts. Briefings in Bioinformatics, v. 22, n. 3, 2021.
