[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/NTXJsmia)
# ⚡ :ice_hockey: Micro-Hockeys Semi-Auto :ice_hockey: ⚡

- [🎈 Introdução](#-introdução)
- [📂 Arquivos do projeto](#-arquivos-do-projeto)
- [📝 O Projeto](#-o-projeto)
  - [💡 **LED**](#-led)
  - [⚙️ **Motores**](#️-motores)
  - [🚗​ **Locomotion**](#-locomotion)
  - [🧠 **Controller and Strategy**](#-controller)
  - [✅ **Testes**](#-testes)
- [🔍 Observações finais](#-observações-finais)
- [📎 APÊNDICE A - Exemplo de máquina de estados](#-apêndice-a---exemplo-de-máquina-de-estados)
- [📎 APÊNDICE B - Configuração do STM32CubeMX](#-apêndice-b---configuração-do-stm32cubemx)
    - [⚙️ Motores](#️-motores-1)
    - [💡 LED](#-led-1)

# 🎈 Introdução

Olá e bem vindos à 2ª ~~e ultima~~ fase do PS!

Nesta fase, vocês irão projetar o primeiro robô de vocês!  Vocês deverão implementar o firmware de um robô micro hockey semi-autonomo, ou seja, **deverá ser capaz de executar estratégias pré-definidas**, além de ser controlado via controle remoto

As ferramentas a serem utilizadas já foram passadas nas últimas tarefinhas, então não será necessário instalar mais nada.



# 📂 Arquivos do projeto

- **Micro-Hockey/**
  - **inc/**
    - **utils.hpp** - Arquivo com funções uteis
    - **target.hpp** - Arquivo com as definições dos targets
    - **Class headers**
  - **src/**
    - **led.cpp** - Arquivo que contém a lógica do led
    - **rc_receiver.cpp** - Arquivo que contém a lógica de funcionamento do sistema de rádio controle
    - **motor.cpp** - Arquivo que contém a lógica dos motores
    - **locomotion.cpp** - Arquivo que contém a lógica da locomoção
    - **controller.cpp** - Arquivo que contém a FSM para controle do robô
  - **tests/** - Pasta que contém a implementação dos testes

# 📝 O Projeto

Nosso micro-hockey possui um led, 2 motores DC e um receptor de sinal de rádio controle.

**O MicroHockey deve possuir o seguinte funcionamento ao final do projeto: ele deve ligar e esperar um comando que executará uma estratégia específica. Após a execução, ele deve entrar em um modo de controle direto: ele deve seguir o movimento dos joysticks.**

Nesse projeto vocês deverão fazer a configuração do microcontrolador no STM32CubeMx e implementar o firmware do robô. Para isso, vocês desenvolverão as seguintes funcionalidades e testes (lembrando que vocês podem implementar mais funções além das fornecidas):

## 💡 **LED**

No arquivo `led.cpp` vocês deverão implementar a lógica de funcionamento do led, também parecido com o que foi feito na primeira tarefinha de embarcados.

```c
#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_4
```

Na função `void Led::on()` `void Led::off()` `void Led::toggle()` vocês deverão implementar a lógica de acender, apagar e inverter o estado do led, respectivamente. Para isso, vocês deverão escrever no pino PA04.

## ⚙️ **Motores**

É no `motors.cpp` em que será necessário fazer a implementação do código referente ao funcionamento dos motores. Nela há 1 timer, 4 canais e quatro pinos

```c
#define MOTORS_TIM_HANDLER (htim2)

#define RIGHT_MOTOR_FORWARD_TIM_CH TIM_CHANNEL_1
#define RIGHT_MOTOR_BACKWARD_TIM_CH TIM_CHANNEL_2

#define LEFT_MOTOR_FORWARD_TIM_CH TIM_CHANNEL_3
#define LEFT_MOTOR_BACKWARD_TIM_CH TIM_CHANNEL_4
```

**Para a configuração da PWM no CubeMX, é recomendado um Counter Period de 1000 e 1 de Prescaler.**

No construtor vocês devem iniciar o timer e todos os canais de PWM. Além disso vocês devem setar o valor do duty cycle de todos os canais para 0%. Os pinos utilizados para a geração das PWMs são os pinos PA00 e PA01 para o motor direito (frente e ré, respectivamente) e os pinos PA02 e PA03 para o motor esquerdo (também frente e ré, respectivamente).

```c
Motor::Motor(
    void (*tim_init)(), TIM_HandleTypeDef* forward_tim_handle, uint8_t forward_tim_ch, TIM_HandleTypeDef* backward_tim_handle, uint8_t backward_tim_ch, int8_t min_speed, int8_t max_speed)
```

Vocês deverão implementar a função `void Motor::set_speed(int8_t speed)` que recebe como parâmetro a velocidade de -100 a 100.

De maneira geral, cada motor tem duas entradas principais (in1 e in2), ambas recebendo uma PWM. Uma entrada corresponde à velocidade frontal e a outra à velocidade traseira (ré) (única diferença é o sentido de rotação).

Dessa forma, se o valor de velocidade que a funçao `void set_speed` recebe for maior que zero, o motor deve girar no sentido horário e se o valor for menor que zero, o motor deve girar no sentido anti-horário.

Por conta dessas propridades do driver, os valores de entrada, que estarão entre **-100** e **100**, devem ter um tratamento para serem tranformados em porcentagens do duty cycle da onda. Não basta passar o valor cru para o _COMPARE_ da PWM.

*Obs.: é possível "freiar" completamente colocando o duty cicle tanto do PWM dianteiro quanto do traseiro em seu valor máximo ao mesmo tempo, ou seja, 1000. Isso é útil caso queira garantir que seu robô pare completamente caso a entrada de velocidade recebida for mto baixa.*

Por fim, o método `void Motors::stop()` deverá setar o valor do duty cycle da PWM dos motores para 0%.

Para isso, é utilizado um circuito específico denominado Ponte H, que permite, com um pequeno consumo energético, a rotação dos motores tanto no sentido horário quanto no anti-horário. Não iremos nos estender na definição do circuito, mas quem tiver interesse pode saber mais [aqui](https://www.manualdaeletronica.com.br/ponte-h-o-que-e-como-funciona/)

## 🚗​ **Locomotion**

Na `locomotion.cpp` que efetivamente trabalharemos com dois motores. O intuito aqui é basicamente implementar o que funciona pra um motor mas pra dois.

Aqui a classe receberá dois motores, já declarados antes.

## 🧠 **Controller**

A lógica principal do robô deve ser implementada nos arquivos controller.cpp. A função do controller é ser o "cérebro" do robô, ou seja, nele estará contida a lógica relacionada à quando o robô deve inicializar, a seleção de estratégias e quando parar.

### Funcionamento do Controller

A implementação da lógica do controller se dá por meio da confecção de uma FSM (Finite State Machine). Um exemplo de FSM pode ser encontrado no [Apêndice A](#apêndice-a---exemplo-de-máquina-de-estados).

 O arquivo possuirá, então, 2 métodos:

- `void Controller::init()` -> Responsável por inicializar a máquina de estados.
- `void Controller::run()` -> Responsável por conter e alternar os estados durante a execução do Sumo.

Ao todo, sugere-se que vocês utilizem 2 estados definidos no `enum State` da classe:

- **_STRATEGY_CHOOSER_**:  Nesse estado, ele deve esperar um movimento de alguma manopla e assim alterar o current state. Ou seja, 3 estados pro movimento da manopla e um movimento pra mudar a estratégia pra run

- **_RUN_**: Nesse estado é rodado a estratégia selecionada. Deve-se também checar a leitura de algum movimento específico, como os dois em -100 para ele realizar um "drible".

![Drible](/media/Drible.gif)

Nós encorajamos que vocês coloquem uma forma de ligar o led diferente para cada um dos estados mencionados, pois irá ajudá-los a debuggar possíveis problemas dos seus controllers.

## 📜 Estratégias

Deverão ser implementadas 3 estratégias.

### 🌱 1° Estratégia

A primeira fase, o micro hockey  será posicionado em uma ambiente plano e livre de obstáculos. Seu objetivo será movimentar o robo para frente por um determinado período de tempo

![Fase01](/media/Fase01.gif)

### 🌿 2° Estratégia

Na segunda fase, ele deve descrever uma trajetória circular

![Fase02](/media/Fase02.gif)

### 🌳 3° Estratégia

Na última fase, temos como objetivo que vocês criem uma estratégia que aparenta ser boa, **usem a criatividade**. Vocês terão total liberdade de implementar o que quiser, **contanto que não estraguem nada**.

#### Lembrando que após cada estratégia, ele deve ser capaz de ser controlado pelo controle.

## ✅ **Testes**

Uma prática muito comum na equipe e no desenvolvimento de projetos embarcados no geral é a criação e utilização de testes.

Na pasta `tests/bin` vocês devem implementar testes para os leds e motores serem usados em bancada para validar o código de vocês. Vocês devem implementar testes para o led, motores e locomotion.

# 🔍 **Observações finais**

Na pasta inc, está os headers com as definições das classes. Vocês não precisam alterá-los, mas devem olhar as definições feitas, como as declarações das funções, que vocês irão implementar, e as variáveis declaradas, que vocês utilizarão nos metodos. O arquivo utils.hpp também possui funções que podem ser utilizadas em suas implementações.

## **IMPORTANTE**
Caso a sua versão do STM32CubeMX seja a versão 6.14.X ou superior, o cubemx acaba gerando o arquivo de forma diferente. Para resolver esse problema, por favor, instale a versão 6.13.X do cube.

# 📎 APÊNDICE A - Exemplo de máquina de estados

 ```c
    #include <stdio.h>

    typedef enum estado {
        INICIO,
        MEIO,
        FIM,
    } estado_t;

    static estado_t estado_atual;

    int main() {
        fsm_init();

        for(;;) {
            fsm_troca_estado();
        }
    }

    void fsm_init(void) {
        estado_atual = INICIO;
    }


    void fsm_troca_estado() {
        switch (estado_atual) {
            case INICIO:
                printf("Olá você está no inicio. Aperte o botão para ir para o meio");

                if (botao_esta_apertado()) {
                    estado_atual = MEIO;
                }

                break;

            case MEIO:
                printf("Olá você está no meio. Aperte o botão para ir para o fim");

                if (botao_esta_apertado()) {
                    estado_atual = FIM;
                }

                break;

            case FIM:
                printf("Olá você está no fim. Aperte o botão para voltar para o inicio");

                if (botao_esta_apertado()) {
                    estado_atual = INICIO;
                }

                break;
        }
    }
```

## 📎 APÊNDICE B - Configuração do STM32CubeMX ALTERAR

### ⚙️ Motores

- Motor direito:
	- PWM (forward):
		- **Timer**: tim 2
		- **Pino**: PA00
		- **Canal**: channel 1
		- **Prescaler**: 1 (recomendado)
		- **Counter Period**: 1000 (recomendado)
	- PWM (backward):
		- **Timer**: tim 2
		- **Pino**: PA01
		- **Canal**: channel 2
		- **Prescaler**: 1 (recomendado)
		- **Counter Period**: 1000 (recomendado)

- Motor Esquerdo:
	- PWM (forward):
		- **Timer**: tim 2
		- **Pino**: PA02
		- **Canal**: channel 3
		- **Prescaler**: 1 (recomendado)
		- **Counter Period**: 1000 (recomendado)
	- PWM (backward):
		- **Timer**: tim 2
		- **Pino**: PA03
		- **Canal**: channel 4
		- **Prescaler**: 1 (recomendado)
		- **Counter Period**: 1000 (recomendado)

### 💡 LED

  - LED:
    - **Pino**: PA04 - Gpio output
