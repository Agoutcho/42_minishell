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

[ ] - faire les builtins hors du fork si une seule commande sinon forker 
[ ] - revoir init_env_creation.c 
[ ] - revoir dans le parsing du $ ce que je mets dans temp 
[ ] - revoir init_env_creation.c 
[ ] - dans l'init env ajouter OLDPWD et SHLVL s'il n'existe pas et verifier si la key est nulle 
[ ] - gerer le _

// TODO NOAH

[x] - revoir la gestion des redirections pour toutes les gerees d'un coup et eviter les petites erreuers dans les cas suivants :
	< outfile cat > 1 > 2 >3 > 4 >> infi <<EOF

[] - gerer les pipes avec les builtins, probleme de lecture ou d'ecriture dans les pipes des builtins.


// TODO IMPORTANT

[x] 1. Faire les heredoc en premier, si une redir ne marche pas ne pas faire les autres
[ ] 1. normer
[ ] 1. secure les malloc
[x] 1. gerer les waitpid apres toutes les commandes exemple sleep 10 | echo lol 
ou cat | cat | ls
[x] 1. Faire le heredoc
[ ] 1. Finir les codes erreurs
[x] 1. gerer le cat puis ctrl + C
[x] 1. Regler le segfault lorsque qu'on fait cd - et que OLDPWD n'est pas set
[x] 1. Regler les syntaxes error ne pas quitter le shell si ca marche pas.
[x] 1. finir les signaux

[x] 2. Ajouter le pwd apres un cd - 
[ ] 2. checker les fd avec ls -l /proc/PID/fd/ ou avec le system monitor clique droit open files
[ ] 2. gerer le segfault unset tous l'env

[ ] 3. ajouter les erreurs lorsque le path est change et qu'on essaie un ls qui n'a pas de droit
[ ] 3. dans search_key si la variable est set mais n'a pas de value ca marche moyen

// TODO TEST

[ ] 2. tester les signaux
[x] 2. TEST : tester la priorite des infiles et des HEREDOC melange les deux

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
