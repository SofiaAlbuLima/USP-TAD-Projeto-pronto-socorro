# TRABALHO 1 DA DISCIPLINA DE ALGORITMOS E ESTRUTURAS DE DADOS I
# USP-TAD-Projeto-pronto-socorro
Projeto desenvolvido para a disciplina Algoritmos e Estruturas de Dados I do segundo semestre de graduação.

# Alunos:
- João Pedro Boaretto, nUSP: 16876293
- Lorena Moreira Borges, nUSP: 16883652
- Sofia Albuquerque Lima, nUSP: 16900810

# Projeto: Pronto Socorro
O serviço de Atendimento Médico Emergencial envolve várias etapas: 
- Fila de Atendimento ao chegar no Pronto Socorro
- Cadastro de Paciente: cada um tem seu "histórico de tratamento", o registro deve permanecer mesmo após a alta
- Tratamento de Paciente: medicamentos, cujo o último medicamento prescrito será o primeiro a ser suspenso

# Planejamento do Código
## Especificações Importantes
- *Persistência de Dados:* Os dados armazenados devem ser guardados em Disco. Ao sair do sistema, armazene tudo de uma unica vez. Ao entrar no sistema, recarregue tudo (será feito no TAD IO)

# Funcionamento:
O nosso código possui 5 TADs para auxiliar o código principal (main.c):
- Histórico (historico.c e historico.h);
- Paciente (paciente.c e paciente.h);
- Fila (fila.c e fila.h);
- Lista (lista.c e lista.h);
- TAD IO (IO.c e IO.h);

## TAD PACIENTE
O TAD paciente é um tipo estruturado de dado que define o "paciente" e as operações que podem ser utilizadas com ele, as quais foram:

- paciente_criar; -> cria também um histórico pro paciente, chamando a função do TAD histórico específica
- paciente_apagar; -> deletam também o histórico do paciente, chamando a função do TAD histórico específica
- paciente_imprimir_fila; -> imprime o nome do paciente no formato específico adequado para a fila (fila de espera)
- paciente_imprimir_lista; -> imprime o nome do paciente no formato específico adequado para a lista (registro)
- paciente_obter_ID; -> devolve uma cópia do ID
- paciente_imprimir_nome; -> imprime o nome do paciente
- paciente_obter_copia_nome; -> entrega um ponteiro para uma copia do nome alocada dinamicamente na memória
- paciente_deletar_copia_nome; -> deleta a cópia da memória

As informações de um paciente são armazenadas numa struct que possui um campo para nome (char nome[]), um campo para ID (int id), e um ponteiro para o histórico desse paciente.
A struct foi escolhida por ser uma estrutura que centraliza as informações a respeito de um mesmo tema, no caso, o paciente.

# TAD HISTÓRICO
(...)

# TAD FILA
O TAD fila é uma estrutura em que os elementos são inseridos numa extremidade final e retiradas na inicial. Utilizamos ela para construir a fila de espera
dos pacientes para o atendimento no pronto socorro. Os pacientes são inclusos na fila de espera pela função da main de registrar o paciente.

- fila_criar; -> devolve um ponteiro para o espaço alocado na memória para a filal, com o conteúdo inicializado
- fila_inserir; -> insere um paciente na fila de espera
- fila_atender; -> equivalente ao genérico "fila_remover", remove o paciente que está na posição inicial da fila
- fila_apagar; -> libera o espaço de memória da fila
- fila_buscar; -> retorna true se o paciente estiver na lista, false caso contrário
- fila_proximo_atender; -> equivalente ao genérico "fila_frente", foi criada para ser usada depois do "fila_atender" para mostrar quem será o próximo paciente a ser atendido
                           (mostra o paciente da posição início)
- fila_tamanho; -> devolve uma cópia do tamanho da fila, caso ela exista. Senão, devolve -1
- fila_vazia; -> se tamanho ==0
- fila_cheia; -> se tamanho == TAM_FILA
- fila_imprimir; -> imprime a fila de espera

As informações da fila são guardadas numa struct que possui um array de ponteiros para paciente de tamanho máximo TAM_FILA, definido por um define, que atualmente é 15, um contador
para o ínicio, outro para o fim e um inteiro que guarda o tamanho.

Implementação: a implementação da fila foi feita de maneira sequencial, pois é mais intuitivo de controlar o tamanho máximo, e porque, no caso do problema, há apenas uma fila de
espera, então não consome tanta memória constantemente. Além disso, escolhemos uma implementação circular para melhorar a sua eficiência ao evitar a necessidade do deslocamento
do vetor inteiro toda vez que alguém saísse da fila.

# TAD LISTA
(...)

# TAD IO
O TAD IO realiza a função de persistência de dados. Foram feitas modificações em relação ao TAD IO oferecido como base com o intuito de garantir maior segurança e robustez no tratamento dos dados. As funções desenvolvidas, SAVE e LOAD, possuem, em diversas partes de sua composição, verificações de erros para assegurar a integridade das informações. Dessa forma, o TAD apresenta as seguintes vantagens em relação ao sugerido:
- Melhor tratamento dos dados
- Dados estruturados, melhor representação da informação
- Unificação dos dados em um único arquivo para segurança
- Não destrutivo (se necessário, pode ser usado em execução, sem ter que encerrar o programa)

Das funções desenvolvidas no TAD IO, temos:
- SAVE; -> escreve os dados no arquivo .bin para a persistência. Possui diversas validações/verificações para garantir que os dados sejam inseridos da forma correta
  - salvar_string; -> realiza a gravação no arquivo
- LOAD; -> carrega os dados do arquivo .bin para as devidas estruturas de dados utilizadas no programa, como a lista, a pilha e a fila
  - carregar_string; -> realiza a leitura do arquivo

# CÓDIGO PRINCIPAL:
A nossa main cumpre a função de construir as funções mais complexas, com multiplas camadas de TAD, pedidas pelas operações desejadas para o sistema, ao chamar funções dos TADs.
Ao longo do código, buscamos deixá-lo o mais seguro que podíamos, colocando diversas verificações e mensagens possíveis de erro. Decidimos por deixá-lo modularizado a partir das funções do menu.
