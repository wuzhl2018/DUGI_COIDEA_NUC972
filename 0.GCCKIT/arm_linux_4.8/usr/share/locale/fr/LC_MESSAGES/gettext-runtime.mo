??    '      T  5   ?      `  B   a  !  ?  ?  ?  9   ?  M   ?     ?  ,   [  ,   ?  '   ?  -   ?      	  (   ,	  (   U	     ~	     ?	     ?	  ?   ?	  e   ?
  :   )    d  ?  ~          &  *   7  1   b     ?     ?  "   ?  9   ?  I     ?   _     ?          &     7     I     X     k  ?  w  G     %  ]  ?  ?  6   e  T   ?      ?  3     3   F  +   z  4   ?  '   ?  ,     (   0  *   Y  *   ?     ?    ?  l   ?  >   :    y  ?  ?     )     ?  C   T  6   ?     ?     ?  #   ?  9   "  G   \  ?   ?     R  %   b     ?     ?     ?     ?     ?     
              	                           '                #                     "                               %                       $         &              !                   -V, --version               output version information and exit
   -d, --domain=TEXTDOMAIN   retrieve translated message from TEXTDOMAIN
  -e                        enable expansion of some escape sequences
  -E                        (ignored for compatibility)
  -h, --help                display this help and exit
  -V, --version             display version information and exit
  [TEXTDOMAIN]              retrieve translated message from TEXTDOMAIN
  MSGID MSGID-PLURAL        translate MSGID (singular) / MSGID-PLURAL (plural)
  COUNT                     choose singular/plural form based on this value
   -d, --domain=TEXTDOMAIN   retrieve translated messages from TEXTDOMAIN
  -e                        enable expansion of some escape sequences
  -E                        (ignored for compatibility)
  -h, --help                display this help and exit
  -n                        suppress trailing newline
  -V, --version             display version information and exit
  [TEXTDOMAIN] MSGID        retrieve translated message corresponding
                            to MSGID from TEXTDOMAIN
   -h, --help                  display this help and exit
   -v, --variables             output the variables occurring in SHELL-FORMAT
 %s: invalid option -- '%c'
 %s: option '%c%s' doesn't allow an argument
 %s: option '--%s' doesn't allow an argument
 %s: option '--%s' requires an argument
 %s: option '-W %s' doesn't allow an argument
 %s: option '-W %s' is ambiguous
 %s: option '-W %s' requires an argument
 %s: option requires an argument -- '%c'
 %s: unrecognized option '%c%s'
 %s: unrecognized option '--%s'
 Bruno Haible Copyright (C) %s Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 Display native language translation of a textual message whose grammatical
form depends on a number.
 Display native language translation of a textual message.
 If the TEXTDOMAIN parameter is not given, the domain is determined from the
environment variable TEXTDOMAIN.  If the message catalog is not found in the
regular directory, another location can be specified with the environment
variable TEXTDOMAINDIR.
Standard search directory: %s
 In normal operation mode, standard input is copied to standard output,
with references to environment variables of the form $VARIABLE or ${VARIABLE}
being replaced with the corresponding values.  If a SHELL-FORMAT is given,
only those environment variables that are referenced in SHELL-FORMAT are
substituted; otherwise all environment variables references occurring in
standard input are substituted.
 Informative output:
 Operation mode:
 Report bugs to <bug-gnu-gettext@gnu.org>.
 Substitutes the values of environment variables.
 Ulrich Drepper Unknown system error Usage: %s [OPTION] [SHELL-FORMAT]
 Usage: %s [OPTION] [TEXTDOMAIN] MSGID MSGID-PLURAL COUNT
 Usage: %s [OPTION] [[TEXTDOMAIN] MSGID]
or:    %s [OPTION] -s [MSGID]...
 When --variables is used, standard input is ignored, and the output consists
of the environment variables that are referenced in SHELL-FORMAT, one per line.
 Written by %s.
 error while reading "%s" memory exhausted missing arguments standard input too many arguments write error Project-Id-Version: GNU gettext-runtime 0.18
Report-Msgid-Bugs-To: bug-gnu-gettext@gnu.org
POT-Creation-Date: 2014-12-24 16:27+0900
PO-Revision-Date: 2010-07-23 01:20+0100
Last-Translator: Christophe Combelles <ccomb@free.fr>
Language-Team: French <traduc@traduc.org>
Language: fr
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n > 1);
   -V, --version               affiche le nom et la version du logiciel
   -d, --domain=DOMAINE   récupère la traduction dans le DOMAINE donné
  -e                     remplace certaines séquences d'échappement
  -E                     (ignoré, gardé pour des questions de compatibilité)
  -h, --help             affiche ce message d'aide
  -V, --version          affiche la version du programme
  [DOMAINE]           récupère la traduction dans le DOMAINE
  MSGID MSGID-PLURAL     traduit le MSGID (singulier) / MSGID-PLURAL (pluriel)
  VALEUR                 choisit la forme singulier/pluriel selon la VALEUR
   -d, --domain=DOMAINE   récupère les traductions depuis le DOMAINE
  -e                     remplace certaines séquences d'échappement
  -E                     (ignoré, gardé pour des questions de compatibilité)
  -h, --help             affiche ce message d'aide
  -n                     supprime le caractère de fin de ligne
  -V, --version          affiche le numéro de version du programme
  [DOMAINE] MSGID        récupère la traduction de MSGID, depuis le DOMAINE
   -h, --help                  affiche l'aide-mémoire
   -v, --variables             afficher les variables apparaissant dans FORMAT-SHELL
 %s : option non valable -- '%c'
 %s : l'option « %c%s » ne tolère pas d'argument
 %s : l'option « --%s » ne tolère pas d'argument
 %s : l'option « --%s » exige un argument
 %s : l'option « -W %s » ne tolère pas d'argument
 %s : l'option « -W %s » est ambiguë
 %s : l'option « -W %s » exige un argument
 %s : l'option exige un argument -- '%c'
 %s : l'option « %c%s » n'est pas connue
 %s : l'option « --%s » n'est pas connue
 Bruno Haible Copyright (C) %s Free Software Foundation, Inc.
Licence GPLv3+ : GNU GPL version 3 ou ultérieure <http://gnu.org/licenses/gpl.html>
Ceci est un logiciel libre : vous pouvez le modifier et le redistribuer.
Il n'y a PAS DE GARANTIE, dans la mesure de ce que permet la loi.
 Afficher la traduction en langue native d'un message textuel dont
la forme grammaticale dépend d'un nombre
 Afficher la traduction en langage natif d'un message textuel.
 Si le DOMAINE n'est pas founi, il est obtenu depuis la variable d'environnement
TEXTDOMAIN.  En l'absence du catalogue de messages à l'endroit
habituel, la variable d'environnement TEXTDOMAINDIR peut indiquer un autre
dossier.
Répertoire standard de recherche : %s
 Dans le mode d'exécution normal, l'entrée standard est copiée vers la sortie standard,
en remplaçant les variables d'environnement de la forme $VARIABLE ou ${VARIABLES}
par les valeurs correspondantes. Si FORMAT-SHELL est spécifié,
seules les variables d'environnement définies dans FORMAT-SHELL sont
remplacées; sinon toutes les variables d'environnement apparaissant dans
l'entrée standard sont remplacées.
 Sortie informative :
 Mode d'exécution :
 Rapportez tout problème fonctionnel à <bug-gnu-gettext@gnu.org>.
 Substituer les valeurs des variables d'environnement.
 Ulrich Drepper Erreur système non identifiée Usage : %s [OPTION] [FORMAT-SHELL]
 Usage : %s [OPTION] [DOMAINE] MSGID MSGID-PLURIEL VALEUR
 Usage : %s [OPTION] [[DOMAINE] MSGID]
ou     %s [OPTION] -s [MSGID]...
 Lorsque « --variables » est utilisé, l'entrée standard est ignorée et la sortie
se résume aux variables d'environnements référées par FORMAT-SHELL (une par ligne).
 Écrit par %s.
 erreur lors de la lecture de « %s » Mémoire épuisée arguments manquants entrée standard trop d'arguments erreur d'écriture 