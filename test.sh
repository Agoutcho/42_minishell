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

// TODO globale
[ ] 2.ajouter les erreurs lorsque le path est change et qu'on essaie un ls qui n'a pas de droit
[x] 1.Regler le segfault lorsque qu'on fait cd - et que OLDPWD n'est pas set
[ ] 1.Regler les syntaxes error ne pas quitter le shell si ca marche pas.
[ ] 1.Faire le heredoc
[ ] 1.Finir les codes erreurs
[ ] 1.finir les signaux
[ ] 3.dans search_key si la variable est set mais n'a pas de value ca marche moyen
[ ] 1. checker les fd avec ls -l /proc/PID/fd/
[ ] 1. normer
[ ] 1. secure les malloc
[ ] 1. gerer les waitpid apres toutes les commandes exemple sleep 10 | echo lol 
ou cat | cat | ls
[ ]