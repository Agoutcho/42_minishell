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