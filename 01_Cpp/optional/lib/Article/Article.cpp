/* 
 * File:   Article.cpp
 * Author: philippe
 * 
 * Created on 12 août 2022, 15:14
 */

#include "Article.h"

Article::Article(const std::string& _libelle) :
libelle(_libelle)
 {
}

Article::Article(const std::string& _libelle, const  std::optional<float> _prix) :
libelle(_libelle),
prix(_prix)
 {
}

Article::Article(const Article& orig) {
}

Article::~Article() {
}

std::string Article::getLibelle() const {
    return libelle;
}

 std::optional<float> Article::getPrix() const {
    
    if (prix.has_value())
        return prix;
    else
        return {};
}
 
void Article::setPrix(float _prix){
    prix = _prix;
}
 
 