# USP-TAD-Projeto-pronto-socorro
Projeto desenvolvido para a disciplina Algoritmos e Estruturas de Dados I do segundo semestre de graduação.

# Projeto: Pronto Socorro
O serviço de Atendimento Médico Emergencial envolve várias etapas: 
- Fila de Atendimento ao chegar no Pronto Socorro
- Cadastro de Paciente: cada um tem seu "histórico de tratamento", o registro deve permanecer mesmo após a alta
- Tratamento de Paciente: medicamentos, cujo o último medicamento prescrito será o primeiro a ser suspenso

# Planejamento do Código
## Especificações Importantes
- *Persistência de Dados:* Os dados armazenados devem ser guardados em Disco. Ao sair do sistema, armazene tudo de uma unica vez. Ao entrar no sistema, recarregue tudo (será feito no TAD IO)

## Pacientes
- Armazenar ID e nome

## TADs
Cada um dos TAds pilha, fila e lista devem ter um par de métodos que escrevem para o disco e ler do disco.

### 1. Lista: Relação de Pacientes
O Hospital deve manter a lista de pacientes atendidos do PS, essa lista deve ter o paciente e seu histórico de tratamento
- Cadastrar paciente (verificar se já existe)
- Apagar paciente (óbito)
- Buscar paciente (utilização de nós enquanto verifica que existe)
- Listar todos os pacientes

### 2. Fila: Triagem dos Pacientes - Sala de Espera
Ao dar entrada na Emergência, um paciente, já registrado ou não no hospital, vai para uma fila de atendimento. A fila tem tamanho finito.
- Inserir paciente na fila
- Remover paciente da fila
- Fila cheia
- Fila vazia

### 3. Pilha: Histórico médico do Paciente
A quantidade de procedimentos para cada paciente é de, no máximo, 10. O histórico é simplesmente um texto de, no máximo 100 caracteres. Reportar caso o paciente não for encontrado ou não houver procedimento a desfazer
- Inserir (Adicionar pelo ID, localizar o registro e inserir se o histórico não estiver cheio)
- Retirar (Desfazer e informar o procedimento desfeito se o histórico não estiver vazio)
- Consultar
- Histórico Cheio
- Histórico Vazio

### 4. A Interface do Sistema - Menu principal
- Registrar paciente
- Registrar óbito de paciente (apagar paciente)
- Adicionar procedimento no histórico médico
- Desfazer procedimento do histórico médico
- Chamar paciente para atendimento (verificar se a lista da triagem não é vazia, aí remover o primeiro da fila)
- Mostrar fila de espera (buscar todos os pacientes)
- Mostrar histórico do paciente (buscar paciente, ver se o histórico não é vazio e consultá-lo)
- Sair (salvar na memória)

### 5. Registrar Paciente
Caso seja a primeira ocorrência de um paciente. Reportar se algum ID repetir
- Registrar paciente
- Inserir paciente na fila de espera

### 6. Registrar óbito de paciente
Em caso de morte de paciente, o paciente deve ser esquecido do sistema hospitalar, seu registro deve ser apagado. Deve ser reportado o sucesso ou insucesso da transação
- Verificar se o paciente está na fila de atendimento
    -   Se sim: não deve ser possível registrar óbito
    -   Se não: Buscar paciente e apagá-lo

### 7. Chamar paciente para o atendimento
Tirar paciente da fila. Reportar se a fila estiver vazia

### 8. Mostrar fila de espera

### 9. Mostrar Histórico do Paciente

### 10. IO (Input/Output): 
- save
- load