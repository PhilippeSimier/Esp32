/* 
 * File:   Article.h
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 12 août 2022, 15:14
 */

#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include <string>
#include <optional>

class Article {

public:
    Article(const std::string& _libelle);
    Article(const std::string& _libelle, const  std::optional<float> _prix);
    Article(const Article& orig);
    virtual ~Article();
    
    std::string getLibelle() const ;
    std::optional<float> getPrix() const;
    void setPrix(float _prix);

private:
    std::string libelle;
    std::optional<float> prix;

};

#endif /* ARTICLE_H */

