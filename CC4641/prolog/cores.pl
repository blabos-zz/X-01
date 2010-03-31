% Pessoas
pessoa(alexandra).
pessoa(barbara).
pessoa(rosa).

% Cores
cor(azul).
cor(verde).
cor(lilas).
cor(vermelho).
cor(amarelo).

valida(X, Y, Z) :-
    pessoa(X), cor(Y), cor(Z),
    Y \= Z,
    not((Y = amarelo, Z = vermelho)),
    not((Y = vermelho, Z = amarelo)).

% Nenhuma delas veste amarelo com vermelho.
% veste(X, Y, Z) :- valida(X, Y, Z), not((Y = amarelo, Z = vermelho)), not((Y = vermelho, Z = amarelo)).

% Cada uma delas veste roupas com duas cores, isto é, roupas tipo blusa e saia.

% Alexandra está vestindo o azul.
veste(alexandra, Y, Z) :- valida(alexandra, Y, Z), (Y = azul; Z = azul).

% Barbara está vestindo o amarelo mas não o verde.
veste(barbara, Y, Z) :- valida(barbara, Y, Z), ((Y = amarelo, Z \= verde); (Z = amarelo, Y \= verde)).

% Rosa veste o verde mas não se veste nem de azul e nem lilás.
veste(rosa, Y, Z) :- valida(rosa, Y, Z), ((Y = verde, Z \= azul, Z \= lilas); (Z = verde, Y \= azul, Y \= lilas)).

% Uma delas está de vermelho.
veste(X, Y, Z) :- pessoa(X), ((Y = vermelho, Z \= vermelho); (Y \= vermelho, Z = vermelho)).

% Uma das cores é usada tanto por Barbara como por Rosa.
    
% Alexandra e Barbara tem 04 cores entre elas.
veste(alexandra, X, Y) :- veste(barbara, Z, W), X \= Z, X \= W, Y \= Z, Y \= W.
