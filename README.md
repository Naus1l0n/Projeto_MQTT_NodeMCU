# Projeto_MQTT_NodeMCU

 1. Visão Geral
Ese é um projeto onde desenvolvemos um projeto de "automação" para a casa utilizando o nodeMCU, PlatformIO e o arduino


### 2. Estrutura de Pastas
Local onde ira criar o projeto no PlatformIO dentro do vscode onde ira ter em sua base as seguintes pastas:
.pio - arquivos do nodeMCU
.vscode - arquivos do platformIO
include - arquivo README da pasta src
lib - arquivo README do seu projeto do platformIO
src - onde esta localizado seu codigo main.cpp
test - diretório destinado ao PlatformIO Test Runner e aos testes de projeto.


### 3. Pré-requisitos de Hardware
Internet
Arduino
ESP32
VScode com todas as configurações instaladas


### 4. Configurações
instalando os drivers do node mcu, depois ja com a extensão do platformIO instalada no visual code, criamos um projeto com a board nodeMCU. Apos isso instalamos o Mosquitto e configuramos o arquivo mosquito.conf. Após isso liberamos a porta 1883 TCP. Depois o instalamos o MQTT e nele no arquivo main.cpp colocamos a dependencia dele PubSubClient

### 5. Codigo Fonte
No inicio do codigo, no arquivo maic.cpp, fizemos o login doo ESP8266 no wifi colocando a rede e a senha e depois o server do MQTT com sua porta liberada 1883.
Apos isso fizemos a inscrição dos topicos onde a função callback é ligada, ela vai ler a mensagem, verificar em qual topico chegou e vai agir de acordo com o que mandarmos, por exemplo ligar e desligar ON e OFF, e depois disso o quando o led e acionado publica a mensagem do status do led o que corresponde a sua mudança.

### 6. Compilando e Carregando seu Projeto
Dentro do Vs code com o PlatformIO instalado colocamos o login de wifi e o ip do MQTT no local ...src/main.cpp
Com o NodeMCU ligado via usb no computador, no vs code começamos a compilar e carregar o firmware na placa

### 7. Testes e Exemplos
Fizemos toda a parte da ligação e compilação do projeto, no MQTT colocamos a onde queriamos ligar o led por expemplo o led do quarto1 - casa/quarto1/led/status apos isso na parte inferior digitamos o ON e fizemos o publish


### 8. Estrutura de Tópicos

  "casa/sala/led/status",
  "casa/cozinha/led/status",
  "casa/quarto1/led/status",
  "casa/quarto2/led/status",
  "casa/varanda/led/status"

aqui fizemos a inscrição dos comodos da casa nos quais ligamos os pinos dos led de acordo com a sua ordem 

### 9. Quer Contribuir?
Para contribuir com um projeto de código aberto, escolha uma tarefa, leia as regras, desenvolva a solução em uma nova branch, submeta-a como um Pull Request e, por fim, colabore com o feedback recebido.

![Imagem do WhatsApp de 2025-06-10 à(s) 19 30 37_dd062cac](https://github.com/user-attachments/assets/891d8ca2-1ac7-4e56-ad0a-04c881b02b86)

![Imagem do WhatsApp de 2025-06-10 à(s) 19 30 37_713bc59e](https://github.com/user-attachments/assets/7a507e69-e1de-4df5-82cc-c1bd20d78b7a)

![Imagem do WhatsApp de 2025-06-10 à(s) 19 30 38_fd667b15](https://github.com/user-attachments/assets/322e38c1-9491-4346-9650-36bcea8bbe6a)

![Imagem do WhatsApp de 2025-06-10 à(s) 19 30 38_881b1c41](https://github.com/user-attachments/assets/656b43ed-3966-41c2-aba8-2d9e73eb8d0f)

![Imagem do WhatsApp de 2025-06-10 à(s) 19 30 38_3dbb4791](https://github.com/user-attachments/assets/5504853c-4def-4076-ba9d-722f5286b05c)

![Imagem do WhatsApp de 2025-06-10 à(s) 19 30 38_a92b4605](https://github.com/user-attachments/assets/8b8b9647-f93e-42b0-ab81-29384b588c94)

![Imagem do WhatsApp de 2025-06-10 à(s) 19 30 39_21636311](https://github.com/user-attachments/assets/53f9c421-8ca6-4060-84b1-1d3902ece750)






