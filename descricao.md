# Arena — torneio de combate por turnos

Um jogo de terminal em que você cria um lutador e enfrenta uma sequência de adversários. Entre combates, administra os recursos que sobraram e decide como se preparar para a próxima luta. O objetivo é vencer o torneio antes de ficar sem vida.

O projeto deve ser realizável com os conteúdos até o capítulo 12 do LearnCpp, sem exigir structs, classes próprias ou arrays.

## Experiência do jogador

Ao iniciar, o jogador pode consultar as regras, começar um torneio ou sair.

Para começar, informa seu nome e escolhe uma dificuldade. Cada torneio tem três combates de dificuldade crescente, terminando em um chefe. A vida e os consumíveis restantes passam de uma luta para a próxima.

Durante cada turno, o jogador vê a situação dos dois lutadores e escolhe uma ação:

| Ação | Efeito |
|---|---|
| Ataque comum | Causa dano moderado com boa precisão. |
| Ataque pesado | Pode causar mais dano, mas tem maior chance de errar e consome energia. |
| Defender | Reduz o dano do próximo ataque recebido. |
| Recuperar fôlego | Recupera energia, deixando o jogador exposto ao ataque inimigo. |
| Usar poção | Recupera parte da vida e consome uma poção. |
| Inspecionar | Mostra detalhes de um lutador sem gastar o turno. |
| Desistir | Encerra o torneio após confirmação. |

O inimigo também age por turnos. Suas decisões devem variar conforme sua situação, e os resultados dos ataques devem ter um componente aleatório.

Entre as lutas, o jogador escolhe uma recompensa: recuperar vida, receber uma poção ou melhorar seu ataque. Só pode escolher uma por intervalo.

Ao terminar, o jogo apresenta o resultado do torneio, os combates vencidos, os turnos jogados, o dano causado e as poções consumidas. Depois, permite começar outro torneio ou voltar ao menu.

## Regras que precisam estar bem definidas

Antes de escrever o programa, estabeleça:

- Os atributos iniciais e o efeito de cada dificuldade.
- Os custos, chances e limites de cada ação.
- A ordem das ações e o que acontece quando um lutador é derrotado.
- Quais escolhas consomem um turno.
- Como as recompensas e a pontuação funcionam.

Vida e energia devem permanecer dentro dos limites. Recursos insuficientes impedem a ação e permitem outra escolha. Uma entrada inválida não pode consumir recursos nem dar uma vantagem ao inimigo.

## Requisitos de aplicação dos conteúdos

Estes são critérios do projeto, sem determinar sua implementação.

| Conteúdo | O que o projeto deve demonstrar |
|---|---|
| Arquivos e headers | O programa está dividido em arquivos com responsabilidades claras, declarações compartilhadas e proteção contra inclusões repetidas. |
| Funções e escopo | As partes do jogo têm responsabilidades delimitadas; o estado de uma partida não depende de variáveis globais mutáveis. |
| Namespaces | Os nomes próprios do projeto estão organizados para evitar colisões. |
| `const` | Informações que não devem mudar durante determinada operação são tratadas como somente leitura. |
| `constexpr` | Há regras ou cálculos que podem ser avaliados em compilação e verificados com exemplos conhecidos. |
| `consteval` | Existe uma pequena validação ou cálculo da configuração fixa do torneio que obrigatoriamente acontece em compilação. |
| `static_assert` | Configurações incompatíveis com as regras do jogo são detectadas antes de executar o programa. |
| Referências | Algumas operações alteram explicitamente dados existentes; outras consultam dados sem copiá-los nem permitir alterações. |
| Ponteiros e `nullptr` | A inspeção permite selecionar um dos lutadores existentes ou ficar sem seleção; selecionar um lutador não cria uma cópia dele. |
| `std::optional` | Há uma informação numérica legitimamente ausente, como o recorde da sessão antes da primeira vitória. Ausência e valor zero são situações distintas. |
| Templates de função | Ao menos uma operação realmente compartilhada atende a mais de um tipo numérico usado no projeto. |
| Sobrecarga | Uma operação oferece duas formas de uso com significados coerentes. |
| Strings e `string_view` | O programa trabalha com nomes informados pelo jogador e textos consultados sem necessidade de possuir uma cópia. |
| Conversões e tipos | Contagens, valores numéricos e percentuais são tratados com conversões deliberadas. |
| Condicionais e loops | Menus, turnos, decisões dos inimigos e repetição de partidas funcionam de forma consistente. |
| Números aleatórios | O combate apresenta variação dentro de limites definidos. |
| Tratamento de entrada | Letras, números fora do intervalo e entradas inesperadas são tratados sem travar o programa. |
| Depuração e `assert` | Estados impossíveis do jogo podem ser identificados durante o desenvolvimento. |

**Não é necessário usar cada recurso em toda parte.** Cada requisito precisa aparecer em um uso justificável. Os cálculos de compilação pertencem às regras fixas; a interação e o combate acontecem durante a execução.

## Etapas de entrega

1. **Duelo completo:** uma luta jogável, com vitória, derrota e entradas validadas.
2. **Combate completo:** todas as ações, energia, poções e decisões variadas do inimigo.
3. **Torneio completo:** três lutas, recompensas e continuidade dos recursos.
4. **Sessão completa:** menus, dificuldade, relatório final e recorde entre torneios.
5. **Revisão:** conferir os requisitos de linguagem, os limites numéricos e a organização dos arquivos.

Cada etapa deve terminar com uma versão que você consiga jogar.

## Critérios para considerar o projeto concluído

- É possível vencer, perder, desistir e começar novamente.
- Uma nova partida começa sem carregar acidentalmente dados da anterior.
- O recorde da sessão permanece disponível entre partidas.
- Inspecionar um lutador não altera seu estado nem avança o combate.
- Poções e energia nunca ficam negativas.
- Lutadores derrotados não continuam agindo.
- Entradas inválidas não provocam loops sem saída.
- O programa compila sem avisos com os avisos recomendados pelo curso habilitados.
- Você consegue explicar o papel de cada arquivo e por que cada ponteiro ou referência é válido durante seu uso.

Para esta primeira versão, o escopo termina no terminal: sem interface gráfica, salvamento em arquivo, inventário de itens ou múltiplos inimigos simultâneos. O resultado esperado é um torneio pequeno, completo e confiável.