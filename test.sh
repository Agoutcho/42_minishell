#! /bin/bash

# "
# '
# echo lol |
# echo lol | '
# echo lol > | ' # PAS tout a fait pareil a cause du '> |' 
# echo lol > '
# echo lol > 
# echo lol >> |
# echo lol > | ' '
# echo lol | ' '
# <>> lol
# echo lol "> |" ' '
# > | # syntax error near unexpected token `|'
# < | # syntax error near unexpected token `|'
> |
>
<
>>
<<
<> # F syntax error near unexpected token
>< # F
>>> # F
>>< # F
>>> # F
<<< # F 
<<> # F

# comptage commande / pipes :
# Ces deux tests a la suite affichent tous les deux 3 commandes :
test '|' mpm | lol "|||lol" mdr | lol 
test |"rezkofekozokergokf"

BIZZZZZZZZARE :

les signaux dans la part execution sont naze

SEGFAULT :

"echo" lol > fichier1.txt >> fichier2.txt << "HEREDOC" xD| cat '  ving' "$SHELL" < '$entre' << "$SHELL" > $"" | pipe lol | pipo
"echo" lol > fichier1.txt >> fichier2.txt << "HEREDOC" xD|pipe lol | pipo

"echo"" """"
"echo" """"
"$;l"
"$"
$""
"$''"
$~
$: $? $- $a
export yo=ho
ec"$yo"
export yo+=to => hoto

"echo" cat lol '$mdr''$SHELL'"$SHELL" > fichier.txt | echo lol | cat | lol | tr < infile > outfile >> outappend | ls -l

echo mdr > f1
cat>f2<f1>f3>>f5>f4|echo lol|cat


// TODO check $- $$ $?  $"" $
// TODO check ~/ ~+ ~-
// TODO ~ et ~/ et ~:    https://abs.traduc.org/abs-5.3-fr/ch03.html#tilde
// ~ = $HOME
// ~+ = $PWD
// ~- = $OLDPWD
// TODO peut etre ajouter '$_' => la derniere variable connue  https://abs.traduc.org/abs-5.3-fr/ch09.html

// TODO globale

[ ] - revoir init_env_creation.c 
[ ] - revoir dans le parsing du $ ce que je mets dans temp 
[ ] - revoir init_env_creation.c 
[ ] - dans l'init env ajouter OLDPWD et SHLVL s'il n'existe pas et verifier si la key est nulle 
[ ] - gerer le _


// TODO IMPORTANT

[ ] 1. GERER LES BUILTINS, export quand ya plus d'env, pwd quand le dossier n'existe plus et cd aussi, enlever PWD de l'env et tester 
[ ] 1. normer
[ ] 1. secure les malloc
[ ] 1. Finir les codes erreurs
[ ] 1. les signaux ctrl + \ dans un heredoc marche mal

[ ] 2. creer une variable PWD au cs ou on enleve le dossier actuel et qu'on tape PWD !!! 
[ ] 2. checker les fd avec ls -l /proc/PID/fd/ ou avec le system monitor clique droit open files
[ ] 2. gerer le segfault unset tous l'env

[ ] 3. ajouter les erreurs lorsque le path est change et qu'on essaie un ls qui n'a pas de droit
[ ] 3. dans search_key si la variable est set mais n'a pas de value ca marche moyen
[ ] 3. dans echo gerer -nnnnnnnnnnn
[ ] 3. OLDPWD doit prendre la valeur de PWD
[ ] 3. lorsque le dossier n'existe plus les builtin PWD et CD ne marchent plus

// TODO TEST

[ ] 2. tester les signaux
[x] 2. TEST : tester la priorite des infiles et des HEREDOC melange les deux

// TODO HEREDOC

[ ] 1. Faire les heredoc avant tout et si on fait un ctrl + c on fait rien du tout => renvoi 130
[ ] 1. le test cat << here si on ecrit des trucs puis on ctrl+D sa affiche ce quon a ecrit avant

// TODO LEAKS

[ ] 1. leaks bizarre avec seulement des espaces

// TEST

1
exit + non numeric arguments mauvais ordre d'affichage :
Rachele {
	Rachele ═> exit dwjehgdwe
	Rachele: exit: dwjehgdwe: numeric argument required
	exit
}
Bash {
	exit fjewgfw
	exit
	bash: exit: fjewgfw: numeric argument required
}

2
heredoc avec les variables d'environnement
Rachele {
	Rachele ═> cat << $USER > tmp1
	> bonjour
	> je
	> suis
	> '$USER'
	> "$USER"
	> $USER 		// (on exit pas du heredoc)
	> noahrd0 		// (pour pouvoir exit)
	cat tmp1
	bonjour
	je
	suis
	'$USER'
	"$USER"
	$USER
}
Bash {
	cat << $USER > tmp1
	> bonjour
	> je
	> suis
	> '$USER'
	> "$USER"
	> $USER
	cat tmp1 
	bonjour
	je
	suis
	'noahrd0'
	"noahrd0"
}

3
< tmp1 | > tmp1
Rachele {
	Rachele ═> < tmp1 | > tmp1
	Rachele: no such file or directory: tmp1
	Rachele ═> ls
	includes  libft  Makefile  minishell  objs  srcs  test.sh  text.txt  valgrind_ignore_leaks.txt
	Rachele ═> 
}
Bash {
	noahrd0@DESKTOP-60NBG8D:~/goinfre/WORKING$ < tmp1 | > tmp1
	noahrd0@DESKTOP-60NBG8D:~/goinfre/WORKING$ ls
	includes  libft  Makefile  minishell  objs  srcs  test.sh  text.txt  tmp1  valgrind_ignore_leaks.txt
	noahrd0@DESKTOP-60NBG8D:~/goinfre/WORKING$
}
