#  Serveur Web asynchrone

## Introduction
Le programme Web_Spiffs commande l'allumage et l'extinction d'une led par l'intermédiaire d'une interface web.
Le serveur web,  basé sur la classe  **ESPAsyncWebServer**, est asynchrone cela signifie qu' il peut **gérer plusieurs connexions en même temps**.    Lorsque le programme principal demande l'envoi d'une réponse, il est immédiatement prêt à gérer d'autres connexions pendant que le serveur se charge d'envoyer la réponse en arrière-plan.
Les réponses sont contenues dans des fichiers html et css enregistrés dans la partition data au format SPIFFS de la mémoire flash.


##  Principes de fonctionnement du serveur web serveur

Le serveur  Web asynchrone

-   est à  l'écoute des connexions
-   créer un objet  `Request` pour chaque requête des nouveaux clients 
-   assure le suivi des requête et nettoie la mémoire
-   gère la réécriture d'URL `Rewrites`et applique les règles sur l'url de la demande
-   gère les `Handlers`et les rattache aux requêtes.

### Traitement des modèles (templates)
Le traitement des modèles (templates) prend en charge  le remplacement des champs (espace réservé)  par des valeurs réelles. Les champs sont délimités par des symboles `%`.
exemple :
```<p>GPIO state: <strong> %STATE% </strong></p>```
Le champ %STATE% sera remplacé par sa valeur (On ou Off).

Cela fonctionne en extrayant le nom des champs du texte de la réponse et en le transmettant à une fonction fournie par l'utilisateur qui devrait renvoyer la valeur réelle à utiliser à la place de l'espace réservé.

**Exemple de fonction de traitement des champs du modèle**
```Cpp
// Remplace le champ STATE par l'état de la led On ou Off

String processor(const String& var) {

   String retour = "Off";
   if (var == "STATE") {
      if (digitalRead(LED))
        retour = "On";
   }
   return retour;
} 
```
### Envoie d'une réponse 
Le modèle de la réponse est enregistré dans un fichier situé dans la partition SPIFFS.

Exemple pour une requête GET /on 
```Cpp
// Request GET /on -> allumage led & envoie du fichier /index.html
server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(LED, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
});
```
