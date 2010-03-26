mentira(leao, domingo).
mentira(leao, segunda).
mentira(leao, terca).
mentira(leao, quarta).

mentira(unicornio, quinta).
mentira(unicornio, sexta).
mentira(unicornio, sabado).

verdade(leao, quinta).
verdade(leao, sexta).
verdade(leao, sabado).
%verdade(leao, domingo).

verdade(unicornio, domingo).
verdade(unicornio, segunda).
verdade(unicornio, terca).
verdade(unicornio, quarta).

ontem(segunda, domingo).
ontem(terca, segunda).
ontem(quarta, terca).
ontem(quinta, quarta).
ontem(sexta, quinta).
ontem(sabado, sexta).
ontem(domingo, sabado).

% Para valer esta afirmação, no dia em que ela é dita o personagem precisa
% estar falando a verdade e ainda ter mentido no dia anterior.
menti_ontem(X, Y) :- verdade(X, Y), ontem(Y, Z), mentira(X, Z).

% 1) Ou ambos falam a verdade e mentiram ontem.
hoje(X) :- verdade(leao,X), menti_ontem(leao, X), verdade(unicornio,X),
    menti_ontem(unicornio, X).

% 2) Ou somente o unicórnio mente e portanto sua afirmação é falsa.
hoje(X) :- verdade(leao,X), menti_ontem(leao, X), mentira(unicornio,X),
    not(menti_ontem(unicornio, X)).

% 3) Ou somente o leão mente e portanto sua afirmação é falsa.
hoje(X) :- mentira(leao,X), not(menti_ontem(leao, X)), verdade(unicornio,X),
    menti_ontem(unicornio, X).

% 4) Ou ambos mentem e portanto as duas afirmações são falsas.
hoje(X) :- mentira(leao,X), not(menti_ontem(leao, X)), mentira(unicornio,X),
    not(menti_ontem(unicornio, X)).

% Analisando as quatro equações finais:
%
% 1) Se ambos falam a verdade e dizem no mesmo dia que mentiram ontem, há uma
% contradição, pois, o leão só pode falar a verdade ao afirmar que mentiu no
% dia anterior quando for uma quinta. Já o unicórnio só falará a verdade ao
% afirmar que mentiu no dia anterior quando for um domingo. Portanto ambos
% jamais podem estar falando a verdade simultaneamente quando afirmam que
% mentiram no dia anterior.
%
% 2) Se o leão diz a verdade, ele só pode afirmar que mentiu no dia anterior
% se hoje for uma quinta. Da mesma forma, o unicórnio só mente ao afirmar que
% mentiu no dia anterior, quando for uma quinta. Então quinta é um dia
% dedutível.
%
% 3) Se o unicórnio diz a verdade, ele só pode afirmar que mentiu no dia
% anterior se hoje for um domingo. Já o leão, para mentir afirmando que mentiu
% no dia anterior, precisa fazer isso num domingo, pois ele não mente no
% sábado e estaria falando a verdade se fosse segunda, terça ou quarta, dias
% em que ele mente. Portanto, domingo é mais um dia dedutível.
%
% 4) Se ambos mentem, há uma nova contradição pois, enquanto o leão só pode
% mentir ao afirmar que mentiu no dia anterior se hoje for um domingo, o
% unicório só mente ao afirmar isso, quando hoje for quinta.
%
% Portanto hoje pode ser domingo ou quinta.
