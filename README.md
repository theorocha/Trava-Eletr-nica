# Trava-Eletronica
Projeto final do laboratório de Sistemas Microprocessados, professor Daniel Café.


Projeto final implementado em C no microcontrolador MSP430F5529.
Consiste na comunicação do dispositivo bluetooth HA-05 via UART com a placa, onde enviamos uma senha, e caso a senha 
esteja correta, chama a função moveMotor();, que siumula a abertura de uma tranca eletrônica, aguarda 7 segundos e se fecha sozinha, utilizando o servo motor.
A saída PWM do timer está configurado para o pino P4.5.
