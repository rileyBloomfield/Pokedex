/*
 * PokemonList.h
 *
 *  Created on: 2013-11-02
 *      Author: Jagath
 */

#ifndef POKEMONLIST_H_
#define POKEMONLIST_H_

#include <bb/cascades/DataModel>
#include "pokemon.h"
#include <vector>

class PokemonList: public bb::cascades::DataModel {
	Q_OBJECT
private:
	int m_type_id;
	bool m_list_init;
	QString m_language;
	unsigned int m_number_pokemon;

public:
	PokemonList(QObject *parent = 0);

	// Required interface implementation
	virtual int childCount(const QVariantList& indexPath);
	virtual bool hasChildren(const QVariantList& indexPath);
	virtual QVariant data(const QVariantList& indexPath);

	virtual ~PokemonList();

	//set member methods
	int assignPokemonNumber();
	void assignNamesEng();
	void assignNames();
	void assignStats();
	void assignStatNamesEng();
	void assignStatNames();
	void assignAttributes();
	void assignDescription();
	void assignTypeId();
	void assignTypeEng(unsigned int index);
	void assignTypes(unsigned int);
	void assignPokedexLanguages();
	void assignPokedexTypes();
	void assignAbilityId();
	void assignAbilities(int index);
	int initTempList();
	void setType(int type);
	void setLanguage(QString language);
	void setTypeId(int type);
	void setListInit(bool init);
	void setNumberPokemon(unsigned int number);

	//get member methods
	QString getLanguage()const;
	int getTypeId()const;
	bool getListInit()const;
	unsigned int getNumberPokemon();

	//public lists
	Pokemon* all_pokemon;
	std::vector<Pokemon> m_temp_list;
	QStringList m_stats; //used to display stat identifiers in multiple languages
	QStringList m_pokedex_languages; //Used to populate the language selection in either english or japenese depending on m_language
	QStringList m_pokedex_types; //used to populate the types dropdown with multiple languages
};
#endif /* POKEMONLIST_H_ */
