# ConnectionProtocol StateMachine

Um Projeto que implementa uma máquina de estados representando um protocolo de conexão entre dois dispositivos.
Através de testes unitários é possível validar 2 cenários:
 - 1: Conexão happy path onde todos os estados e eventos seguem um fluxo sem falhas até o estado final
 - 2: Conexão com falahas durante a trasição de alguns estados, porém chegando ao estado final

#Como Executar?

#Pré-requisitos:

    gtest
    cmake

Após reposítorio clonado, apenas execute os scripts de build e run_tests:

$ ./scripts/build.sh

$ ./scripts/run_tests.sh
