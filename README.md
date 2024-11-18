# GS-Computing-Edge-Simulador-Painel-Solar
Um dos principais problemas da energia limpa é o seu alto custo de compra e manutenção, desencorajando grande parte da população. Por isso, nosso grupo desenvolveu um simulador de painel solar no Arduíno com o objetivo de testar e identificar com precisão as medidas com melhor custo benefício.
<h2>Sobre o projeto</h2>
Este projeto tem o principal objetivo de simular um painel solar usando parâmetros definidos pelo usuário. O circuito:
<ul>
  <li>Mostra a porcentagem da bateria através do display(LCD).</li>
  <li>Pode ativar e desativar o modo consumo através de um botão.</li>
  <li>Possui um sistema de threshold de bateria, desativa a obtenção de energia da bateria e reativa quando estiver abaixo do limite colocado pelo usuário.</li>
  <li>Consegue converter valores da área da superfície do painel de milimetros e centímetros para metros quadrados.</li>
  <li>Consegue fazer a simulação tanto em tempo real como por hora.</li>
</ul>
<h2>Componentes</h2>
<ul>
  <li>1 x Arduino UNO R3.</li>
  <li>1 x LDR(Sensor de luz).</li>
  <li>1 x Botão.</li>
  <li>1 x LiquidCrystal I2C (Display)</li>
  <li>2 x Resistores</li>
</ul>
<h2>Esquema do circuito</h2>

![image](https://github.com/user-attachments/assets/044d84e2-2184-437f-a22c-cf928b420bc7)

<h2>Pré-requisitos</h2>
<ul>
  <li>IDE do Arduino</li>
  <li>Biblioteca LiquidCrystal I2C</li>
</ul>

<h2>Instalação</h2>
<ol>
  <li>Conecte o arduino ao computador.</li>
  <li>Coloque o código .ino ao IDE do arduíno.</li>
  <li>Instale a Biblioteca LiquidCrystal I2C.</li>
  <li>Carregue o código.</li>
</ol>

<h2>Como usar</h2>
Você pode mexer nas configurações para colocar os parâmetros desejados.

![image](https://github.com/user-attachments/assets/f7a8ed30-1260-4bd1-8110-25c52e4a1cf1)

Use o botão para ativar e desativar o consumo de energia.
<h2>Link da simulação</h2>

https://wokwi.com/projects/414479088758888449


