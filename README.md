# Detective Quest - Desafios em C

Série de três trabalhos educacionais em C que implementam um jogo de investigação em uma mansão, progredindo em complexidade com estruturas de dados.

## Arquivos

- `detective_novato.c` - Nível Novato: Exploração com árvore binária
- `detective_aventureiro.c` - Nível Aventureiro: Exploração + Coleta de pistas (BST)
- `detective_mestre.c` - Nível Mestre: Exploração + Pistas (BST) + Suspeitos (Hash) + Julgamento

## Compilação

```bash
gcc -o detective_novato detective_novato.c
gcc -o detective_aventureiro detective_aventureiro.c
gcc -o detective_mestre detective_mestre.c
```

## Execução

```bash
./detective_novato
./detective_aventureiro
./detective_mestre
```

## Nível Novato

Explore a mansão representada como árvore binária.

Operações:
- (E) Ir para esquerda
- (D) Ir para direita
- (S) Sair da mansão

## Nível Aventureiro

Explore e colecione pistas em uma BST ordenada alfabeticamente.

Operações:
- (E) Ir para esquerda
- (D) Ir para direita
- (S) Sair e ver pistas coletadas

Saída mostra todas as pistas encontradas em ordem alfabética.

## Nível Mestre

Complete a investigação: explore, colecione pistas e acuse o culpado.

Operações:
- (E) Ir para esquerda
- (D) Ir para direita
- (S) Sair e acusar suspeito

Sistema de julgamento:
- Requer mínimo 2 pistas contra o suspeito
- Hash table associa pistas a suspeitos
- Resultado: Culpado identificado ou evidências insuficientes

## Estruturas de Dados

- **Árvore Binária**: Mapa da mansão (Novato)
- **BST**: Armazena pistas em ordem (Aventureiro e Mestre)
- **Tabela Hash**: Pista → Suspeito (Mestre)

## Mapa da Mansão

```
                    Hall de Entrada
                   /              \
            Sala de Estar      Cozinha
            /          \        /      \
       Biblioteca   Escritório  Despensa  Sala de Jantar
       /     \      /    \      /   \      /    \
   Arquivo  Sala  Cofre  Reunião Adega Dispensa Salão  Jardim
   Secreto  Leitura Oculto           Fria     Baile  Inverno
```

## Pistas e Suspeitos

| Pista | Suspeito |
|-------|----------|
| Recibo de transferencia bancaria | Primo Rico |
| Frasco de veneno vazio | Chef Moreno |
| Livro com pagina marcada | Bibliotecario Silva |
| Carta manuscrita suspeita | Secretaria Paula |
| Copo com marcas de laboratorio | Doutor Alvaro |
| Documento confidencial | Primo Rico |
| Chave dourada antiga | Primo Rico |
| Agenda com encontros marcados | Secretaria Paula |
| Garrafa com etiqueta falsa | Chef Moreno |
| Alimento vencido | Chef Moreno |
| Luva descartada | Doutor Alvaro |