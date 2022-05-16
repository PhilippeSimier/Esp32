# Préferences 

## Introduction
Ici nous allons voir comment stocker des données dans la mémoire flash de l'ESP32 à l'aide de la librairie Preferences.h. Nous pouvons utiliser cette bibliothèque pour lire et écrire des données sur la mémoire flash de l'ESP32 en permanence. L'ESP32 se compose d'une mémoire flash non volatile qui peut conserver les données après une réinitialisation ou une panne de courant. En utilisant preferences.h, cette fonctionnalité de stockage permanent est particulièrement utile pour les applications où nous devons nous souvenir du dernier état d'une variable, stocker certaines valeurs pour l'exécution ou enregistrer des données pour une utilisation future telles que les informations d'identification réseau, les clés API, etc.

## Principe

La bibliothèque **Preferences** stocke les différentes données sous la forme de paires **clé:valeur** où une clé est un identifiant unique d'un élément de données et la valeur est la donnée elle-même. Ces paires clé:valeur font partie d'un espace de noms. L'espace de noms est restreint à un maximum de 15 caractères.
```
namespace {
key1:value1
key2:value2
}
```
Avec l'aide de la bibliothèque  **Preferences**, les types de données suivants peuvent être enregistrés de manière permanente dans la mémoire flash de l'ESP32. 
-   Char
-   UChar
-   Short
-   UShort
-   Uint
-   Long
-   ULong
-   Long64
-   ULong64
-   Float
-   Double
-   Bool
-   String
-   Bytes

## Le code

```cpp
#include <Preferences.h>
Preferences preferences;
```
## Les méthodes
```cpp
preferences.begin(“namespace”, false);
```
La méthode **begin()** est utilisée pour démarrer une préférence en créant un espace de stockage pour un espace de noms particulier. Elle est composé de deux arguments. Le premier sera le nom de l'espace de noms qui est **namespace** dans notre cas. Le deuxième argument sera soit vrai/faux. Dans notre exemple, nous avons passé false, ce qui signifie que les modes lecture et écriture sont activés.

```cpp
preferences.clear();
```
Avec à la méthode clear(), toutes les préférences d'un espace de noms ouvert seront effacées.

```cpp
preferences.remove(key);
```
La méthode remove supprime la "clé" associée à l'espace de noms ouvert.

```cpp
preferences.end();
```
Pour l'espace de noms ouvert, la méthode end() est utilisée pour fermer la préférence

### Enregistrer une clé:valeur

La méthode put() prendra deux arguments où le premier sera la clé et le second sa valeur. En utilisant cette méthode, vous pourrez enregistrer tous types de variable.

|Data Type  | Method |
|--|--|
|Char   | putChar(const char* key, int8_t value) |
| Unsigned Char |putUChar(const char* key, int8_t value)|
| Short |putShort(const char* key, int16_t value)|
| Unsigned Short  | putUShort(const char* key, uint16_t value) |
| Int | putInt(const char* key, int32_t value) |
| Unsigned Int | putUInt(const char* key, uint32_t value) |
| Long | putLong(const char* key, int32_t value) |
| Unsigned Long | putULong(const char* key, uint32_t value) |
| Long64 | putLong64(const char* key, int64_t value) |
| Unsigned Long64 | putULong64(const char* key, uint64_t value)|
| Float | putFloat(const char* key, const float_t value)|
| Double | putDouble(const char* key, const double_t value) |
| Bool | putBool(const char* key, const bool value) |
| String | putString(const char* key, const String value) |
| Bytes | putBytes(const char* key, const void* value, size_t len)|

