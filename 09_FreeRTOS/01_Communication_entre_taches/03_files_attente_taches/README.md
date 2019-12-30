# Communication entre deux tâches
## Files d'attente

Les files d'attente (queues) sont très utiles pour la communication inter-tâches, permettant d'envoyer des messages d'une tâche à une autre en toute sécurité en termes de concurrence. Elles sont  utilisées comme FIFO (First In First Out), ce qui signifie que les nouvelles données sont insérées à l'arrière de la file d'attente et consommées à partir du front.
Les données insérées dans la file d'attente sont copiées plutôt que référencées. Cela signifie que si nous envoyons un entier à la file d'attente, sa valeur sera réellement copiée et si nous changeons la valeur d'origine après cela, aucun problème ne devrait se produire.
Un aspect de comportement important est que l'insertion dans une file d'attente pleine ou la consommation d'une file d'attente vide peut bloquer les appels pendant une durée donnée (cette durée est un paramètre de l'API).

## Création d'une file d'attente
**xQueueCreate** : Crée une nouvelle file d'attente et renvoie un descripteur par lequel la file d'attente peut être référencée. Chaque file d'attente requiert de la RAM utilisée pour conserver l'état de la file d'attente et pour contenir les éléments.
Les éléments sont mis en file d'attente par copie, et non par référence, c'est donc le nombre d'octets qui seront copiés pour chaque élément en file d'attente. Chaque élément de la file d'attente doit être de la même taille.

**Premier argument** : Le nombre maximal d'éléments que la file d'attente peut contenir à tout moment.
**Deuxième argument** :  La taille, en octets, requise pour contenir chaque élément dans la file d'attente.

Exemple  de création :
```c
queue = xQueueCreate( queueSize, sizeof( typeMesure ));
```
## Insertion un élément dans une file

**xQueueSend** Publie un élément dans une file d'attente. L'élément est mis en file d'attente par copie et non par référence.

Paramètres:

 - **xQueue** 	Handle de la file d'attente sur laquelle l'élément doit être publié.
 - **pvItemToQueue** 	Un pointeur vers l'élément à placer dans la file d'attente. La taille des éléments que la file d'attente contiendra a  été définie lors de la création de la file d'attente, donc ce nombre  d'octets sera copié de pvItemToQueue dans la zone de stockage de la  file d'attente.
 - **xTicksToWait** 	Durée maximale pendant laquelle la tâche doit bloquer l'attente de la disponibilité d'espace dans la file  d'attente, si elle est déjà pleine.
la spécification du temps de blocage comme **portMAX_DELAY** entraînera le blocage indéfini de la tâche.

Exemple de code :
```c
xQueueSend(queue, &mesureSend, portMAX_DELAY);
```
## Recevoir un élément 
**xQueueReceive** reçois un élément d'une file d'attente. 

 - **xQueue** 	Handle de la file d'attente à partir de laquelle l'élément doit être reçu.
 - **pvBuffer** 	Pointeur vers la variable dans lequel l'élément reçu sera copié.
 - **xTicksToWait** 	Durée maximale pendant laquelle la tâche doit bloquer
   l'attente d'un élément à recevoir si la file d'attente est vide au moment de l'appel.

```c
xQueueReceive(queue, &mesureReceive, portMAX_DELAY);
```

# Changelog

**27/12/2019 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


