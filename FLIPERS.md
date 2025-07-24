# Sistema de Flipers de Pinball

## Descrição
O jogo agora possui um sistema de flipers de pinball que permite ao jogador controlar duas alavancas para bater na bola e ejetá-la.

## Controles
- **Q**: Aciona o fliper esquerdo
- **E**: Aciona o fliper direito

## Funcionalidades
- Os flipers são posicionados na parte inferior da tela (30% e 70% da largura)
- Cada fliper tem 80 pixels de comprimento
- **Fliper esquerdo**: Rotaciona de -30° para +45° quando acionado (movimento anti-horário)
- **Fliper direito**: Rotaciona de +30° para -45° quando acionado (movimento horário)
- Quando acionados, os flipers aplicam força extra à bola
- Os flipers mudam de cor (branco → amarelo) quando acionados
- Som de colisão é tocado quando a bola toca nos flipers

## Implementação Técnica
- Variáveis adicionadas à classe `Game` para controlar estado dos flipers
- Detecção de colisão usando `CheckCollisionCircleLine`
- Força adicional aplicada quando o fliper está sendo acionado
- Renderização visual com `DrawLineEx` e pontos de rotação
