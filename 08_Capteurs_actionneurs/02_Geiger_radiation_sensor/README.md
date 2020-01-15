# Mesurer la radioactivité

## Introduction
La radioactivité est présente partout sur la planète. Elle forme un bruit de fond radiologique ambiant constitué principalement de radionucléides naturellement présents dans les sols ou dans les matériaux qui nous entourent et de rayonnements d'origine cosmique, mais également produits artificiellement.

### Les rayonnements d’origine tellurique
L'écorce terrestre contient des atomes radioactifs qui sont la source d'une radioactivité naturelle (thorium-232, uranium-235, uranium-238 et leurs descendants). Dotés de très longues durées de vie, pouvant atteindre plusieurs milliards d'années, ils sont encore loin d'avoir disparu et font donc partie intégrante de notre environnement.

Selon la nature des roches composant le sous-sol, nous sommes donc plus ou moins exposés aux rayonnements telluriques. Dans certaines régions granitiques, par exemple en France le Limousin ou la Bretagne, le rayonnement tellurique peut être 4 fois plus important qu’en région parisienne. 

### Le rayonnement cosmique
Il est constitué principalement de noyaux d’hydrogène (protons) et de noyaux légers (He par exemple) de très haute énergie. Ce rayonnement a deux composantes, l’une est d’origine galactique ou extragalactique et provient de la désintégration d’étoiles et l’autre vient du soleil qui a une activité continue, avec un cycle d’environ 11 ans, à laquelle viennent s’ajouter des éruptions sporadiques.
L’interaction du rayonnement cosmique avec les constituants de l’atmosphère produit une « pluie » continue de particules secondaires (neutrons, muons, électrons...) qui sont en grande partie absorbées avant d'arriver au niveau du sol.
De ce fait, l’intensité du rayonnement cosmique varie très fortement en fonction de l’altitude. Au niveau du sol, la dose reçue est environ 100 fois plus faible qu’aux altitudes de vol des avions long-courriers.
A noter que des radionucléides, dits cosmogéniques, sont également produits en permanence par l’interaction, dans la haute atmosphère, du rayonnement cosmique avec les atomes constituant notre atmosphère. Le plus connu est le carbone-14.

![Particules cosmiques](/08_Capteurs_actionneurs/02_Geiger_radiation_sensor/particule_cosmique.jpg)

![Variation débit](/08_Capteurs_actionneurs/02_Geiger_radiation_sensor/Variation-debit.jpg)

### Mesurer la radioactivité

Le **Becquerel (Bq)** est l’unité de mesure de la radioactivité d’un corps. Elle caractérise le nombre de désintégrations spontanées de noyaux d’atomes instables qui s’y produit par seconde. Dans le corps humain, la radioactivité est naturellement de 120 Bq/kg.
Le **Gray (Gy)** est l’unité qui permet de mesurer la quantité de rayonnement absorbé par un corps exposé à de la radioactivité. 1 Gy = 1 J / kg
Le **Sievert (Sv)** est une variante du Gray qui tient compte des effets spécifiques des rayonnements sur l’être humain et sa santé.
 Une dose de 1 Gy sur la main n’a pas les mêmes effets que 1 Gy sur le cerveau. Le sievert tient compte de tout ça. De plus, 1 Gy diluée tout au long d’une vie et une dose de 1 Gy reçu en quelques instants n’ont pas non plus les mêmes effets. Pour être plus précis, on parlera le plus souvent du nombre de sievert par unité de temps (sievert par an [Sv/an] ou sievert par seconde [Sv/s] ou microsievert par heure [uSv/h]).

## Module de détection à diode PIN
Les compteurs de rayonnement nucléaire basés sur l'absorption directe dans le silicium constituent une alternative fiable et peu coûteuse par rapport au système à tube Geiger-Muller.
La détection des rayons gamma repose sur un capteur semi-conducteur, plus précisément sur un type particulier de diode, les **diodes PIN**. PIN pour Positive Intrisic Negative fait référence directement à la manière dont est constitué le composant. Une diode ordinaire est une jonction de deux demi-conducteurs, l'un dopé négativement (N) par ajout d'impuretés apportant un excès d'électrons et l'autre dopé positivement (P) par ajout d’impureté provoquant une carence en électrons. Dans le cas de la diode PIN on trouve entre les zones P et N une zone non dopée dite intrinsèque.  
La structure PIN permet la détection de photons, un peu à la manière d'un tube Geiger-Muller avec un effet cascade et une brève conductivité. elles sont aussi capable de détecter les rayons gamma ainsi que les rayon X (qui ne sont rien d'autre qu'une onde électromagnétique, comme l'est la lumière visible.

[Capteur gamma ray detection](https://www.first-sensor.com/en/products/radiation-sensors/series-x-detectors-for-ionizing-radiation/index.html)

## Le module radiation watch
Le module est construit autour d'une photodiode PIN d'une taille relativement importante (1cm * 1cm).
La détection et l’électronique qui l'entoure est là pour amplifier le signal et le transmettre avec des niveaux adaptés. 

![schema_type](/08_Capteurs_actionneurs/02_Geiger_radiation_sensor/schema_type.jpg)

# Changelog

**07/01/2020 : ** Ajout Sémaphore de comptage. 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


