/*
 * PokemonList.cpp
 *
 *  Created on: 2013-11-02
 *      Author: Jagath
 */

#include "pokemonlist.h"
//#include "pokemon.h"
#include <iostream>
#include <bb/cascades/DataModelChangeType>

const QString ENG = "9";
const QString JAP = "1";

/*
 * PokemonList is derive from DataModel which provides the base class for the "model"
 * in the model-view-controller pattern used by the ListView UI control
 */

PokemonList::PokemonList(QObject* parent) : bb::cascades::DataModel(parent), m_type_id(-1), m_list_init(true), m_language(ENG), all_pokemon(NULL), m_number_pokemon(0) {
}

// Return the number of child items contained in a given entry
// Since we only implement a flat list, we must return 0 for any sub item.
int PokemonList::childCount(const QVariantList& indexPath) {
	// For indexPath, See http://developer.blackberry.com/native/reference/cascades/bb__cascades__datamodel.html

	// Return the item count if asking for top level count
	if (indexPath.empty())
	{
		return initTempList(); // TODO: Return the correct number of pokemon
	}

	// No sub levels
	return 0;
}

// Used for displaying multi-level lists
bool PokemonList::hasChildren(const QVariantList& indexPath) {
	if (indexPath.empty())
		return true; // The root node always has children
	else
		return false; //
}

// Return the data for the item given by indexPath
QVariant PokemonList::data(const QVariantList& indexPath) {

	/************************PRIMARY POKEMON INITIALIZATION***********************************************************/
	if (m_list_init) //Only initialize all_pokemon on startup or if language changes
	{
		delete [] all_pokemon;
		all_pokemon = new Pokemon[assignPokemonNumber()];
		//Functions to initialize array of pokemon objects
		assignNames();
		assignStatNames();
		assignStats(); //populate all stats
		assignTypeId();  //add type 1 and type 2 IDs
		assignAbilityId();
		for (int j(0); j<m_number_pokemon; j++) //assign types to all pokemon
		{
			assignTypes(j);
			assignAbilities(j); //assign abilities to all pokemon
		}
		assignAttributes();
		assignDescription();
		initTempList();
		m_list_init = false;
	}

	/***************************RETURN DATA***************************************************************************/
	QVariantMap data; //variable to hold returned information
	int i = indexPath[0].toInt(); //which index to return information of
	data["a_name"] = m_temp_list[i].nameDisplay();	// this will be displayed on list view no matter what because of alpha order
	data["b_name"] = m_temp_list[i].nameDisplayItem(); //this will be sent to the titlebar in itemPage (no types)
	data["type1"] = m_temp_list[i].getType1(); //send type1 of selected pokemon

	if (m_temp_list[i].getType2()=="None")
		data["type2"] = " "; //send blank space to be displayed on itempage
	else
		data["type2"] = m_temp_list[i].getType2(); //send type2 of selected pokemon
	//send all stat names
	data["stat1"] = m_stats.at(0)+": ";
	data["stat2"] = m_stats.at(1)+": ";
	data["stat3"] = m_stats.at(2)+": ";
	data["stat4"] = m_stats.at(3)+": ";
	data["stat5"] = m_stats.at(4)+": ";
	data["stat6"] = m_stats.at(5)+": ";

	data["hp"] = m_temp_list[i].getHp(); //send hp of selected pokemon
	data["z_attack"] = m_temp_list[i].getAttack(); //send attack of selected pokemon
	data["defence"] = m_temp_list[i].getDefence(); //send defence of selected pokemon
	data["spAttack"] = m_temp_list[i].getSpAttack(); //send special attack of selected pokemon
	data["spDefence"] = m_temp_list[i].getSpDefence(); //send special defence of selected pokemon
	data["speed"] = m_temp_list[i].getSpeed(); //send speed of selected pokemon
	//Sum of the stats is sent
	data["totStat"] = QString::number(m_temp_list[i].getHp().toInt() + m_temp_list[i].getAttack().toInt() + m_temp_list[i].getDefence().toInt() + m_temp_list[i].getSpAttack().toInt() + m_temp_list[i].getSpDefence().toInt() + m_temp_list[i].getSpeed().toInt());

	if (!m_temp_list[i].getHeight().toFloat()>0) //If height is unknown in the csv file
		m_temp_list[i].setHeight("N/A");
	data["height"] = m_temp_list[i].getHeight(); //send height of selected pokemon

	if (!m_temp_list[i].getWeight().toFloat()>0) //If weight is unknown in the csv file
		m_temp_list[i].setWeight("N/A");
	data["weight"] = m_temp_list[i].getWeight(); //send weight of selected pokemon

	data["description"] = m_temp_list[i].getDescription(); //send description of selected pokemon
	data["version"] = m_temp_list[i].getVersion(); //send version pokemon was introduced in
	data["abilitySlot1"] = m_temp_list[i].getAbilitySlot1();

	if (m_temp_list[i].getAbilitySlot2()=="None") //if there is no secondary ability
		data["abilitySlot2"] = ""; //send a blank string to UI
	else
		data["abilitySlot2"] = m_temp_list[i].getAbilitySlot2(); //send the proper secondary ability

	data["abilitySlot3"] = m_temp_list[i].getAbilitySlot3(); //send the hidden ability

	return data;			// Return the pokemon information as a QVariant object
}

PokemonList::~PokemonList() {
	delete [] all_pokemon; //delete dynamic array
	m_stats.clear(); //clear stat names list
	m_pokedex_languages.clear(); //clear languages list
	m_pokedex_types.clear(); //clear types dropdown list
	m_temp_list.clear(); //clear return list
}

int PokemonList::assignPokemonNumber() {
	QString line; //place holder for a single line of text unparsed text
	static QStringList parsed_text; //QString list to hold a line of parsed text
	unsigned int number(0);
	QFile file_pokemon_types("app/native/assets/data/pokemon_types.csv"); //load POKEMON TYPES
	if (file_pokemon_types.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_pokemon_types); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			if (parsed_text.at(2)==JAP) //used to calculate number of pokemon because every pokemon has a type in slot 1
			{
				number++; //add another pokemon
			}
		}

	}
	else
		std::cerr<<"Failed to open file: pokemon_species_names.csv "<<file_pokemon_types.error()<<endl; //Could not load pokemon types file*/
	file_pokemon_types.close(); //close file
	return number; //return the number of pokemon present in the file
}

void PokemonList::assignNamesEng() {
	/***********************ASSIGN NAME AND ID - WORKING *************************************************/
	static QStringList parsed_text; //QString list to hold a line of parsed text
	unsigned int index(0); //used for accessing pokemon array elements
	QString line; //place holder for a single line of text unparsed text
	QStringList alt_lang;
	QFile file_pokemon_names("app/native/assets/data/pokemon_species_names.csv"); //load Pokemon names file **LANGUAGE SPECIFIC**
	if (file_pokemon_names.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_pokemon_names); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			alt_lang.append(line);
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			if (parsed_text.at(1)==ENG)
			{
				all_pokemon[index].setName(parsed_text.at(2)); //Add name
				all_pokemon[index].setId(parsed_text.at(0)); //add ID
				all_pokemon[index].setEnglish(true); //[English] is needed
				index++; //move to next pokemon
			}
		}
	}
	else
		std::cerr<<"Failed to open file: pokemon_species_names.csv "<<file_pokemon_names.error()<<endl;  //Could not load pokemon names file
	file_pokemon_names.close(); //close file
}

void PokemonList::assignNames() {
	assignNamesEng(); //populate names and ID
	static QStringList parsed_text; //QString list to hold a line of parsed text
	unsigned int index(0); //used for accessing pokemon array elements
	QString line; //place holder for a single line of text unparsed text
	QFile file_pokemon_names("app/native/assets/data/pokemon_species_names.csv"); //load Pokemon names file **LANGUAGE SPECIFIC**
	if (file_pokemon_names.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_pokemon_names); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			if (parsed_text.at(1)==m_language)
			{
				if (m_language=="4" && parsed_text.at(0).toInt()>510) //stops crashing when chinese is selected
					return;
				all_pokemon[index].setName(parsed_text.at(2)); //Add name
				all_pokemon[index].setId(parsed_text.at(0)); //add ID
				all_pokemon[index].setEnglish(false);
				index++; //move to next pokemon

			}
		}
	}
	else
		std::cerr<<"Failed to open file: pokemon_species_names.csv "<<file_pokemon_names.error()<<endl; //Could not load pokemon names file
	file_pokemon_names.close();
}

void PokemonList::assignStats() {
	/***************************************ASSIGN ALL STATS TO POKEMON******************************************/
	static QStringList parsed_text; //QString list to hold a line of parsed text
	unsigned int index(0); //used for accessing pokemon array elements
	QString line; //place holder for a single line of text unparsed text
	unsigned int line_number(0);
	index = 0;
	QFile file_pokemon_stats("app/native/assets/data/pokemon_stats.csv"); //Could not load pokemon stats file **Not language dependent**
	if (file_pokemon_stats.open(QIODevice::ReadOnly | QIODevice::Text))  //if the file is opened successfully
	{
		QTextStream in(&file_pokemon_stats); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			line_number++;
			if(line_number>0&&line_number<4310) //do not read lines with arbitrary information
			{
				if (parsed_text.at(1)=="1") //if line contains hp stat
					all_pokemon[index].setHp(parsed_text.at(2)); //assign hp
				else if(parsed_text.at(1)=="2") //if line contains attack stat
					all_pokemon[index].setAttack(parsed_text.at(2)); //assign attack
				else if(parsed_text.at(1)=="3") //if line contains defence stat
					all_pokemon[index].setDefence(parsed_text.at(2)); //assign defence
				else if(parsed_text.at(1)=="4") //if line contains special attack
					all_pokemon[index].setSpAttack(parsed_text.at(2)); //assign special attack
				else if(parsed_text.at(1)=="5") // if line contains special defence stat
					all_pokemon[index].setSpDefence(parsed_text.at(2)); //assign special defence
				else if(parsed_text.at(1)=="6") //if line contains the last stat, speed
				{
					all_pokemon[index].setSpeed(parsed_text.at(2)); //assign speed
					index++; //move to next pokemon
				}
			}
		}
	}
	else
		std::cerr<<"Failed to open file: pokemon_stats.csv "<<file_pokemon_stats.error()<<endl;  //Could not load pokemon stats file
	file_pokemon_stats.close();
}

void PokemonList::assignStatNamesEng() {
	m_stats.clear();
	QString line; //place holder for a single line of text unparsed text
	static QStringList parsed_text; //QString list to hold a line of parsed text
	QFile file_stat_names("app/native/assets/data/stat_names.csv"); //load stat names file **LANGUAGE SPECIFIC**
	if (file_stat_names.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_stat_names); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			//match each stat id to pokemon stats, add [English] (will be overridden if another language is present
			if (parsed_text.at(1)==ENG && parsed_text.at(0)=="1")
				m_stats.append(parsed_text.at(2)+" [English]");

			if (parsed_text.at(1)==ENG && parsed_text.at(0)=="2")
				m_stats.append(parsed_text.at(2)+" [English]");

			if (parsed_text.at(1)==ENG && parsed_text.at(0)=="3")
				m_stats.append(parsed_text.at(2)+" [English]");

			if (parsed_text.at(1)==ENG && parsed_text.at(0)=="4")
				m_stats.append(parsed_text.at(2)+" [English]");

			if (parsed_text.at(1)==ENG && parsed_text.at(0)=="5")
				m_stats.append(parsed_text.at(2)+" [English]");

			if (parsed_text.at(1)==ENG && parsed_text.at(0)=="6")
				m_stats.append(parsed_text.at(2)+" [English]");
		}
	}
	else
		std::cerr<<"Failed to open file: stat_names.csv "<<file_stat_names.error()<<endl;
	file_stat_names.close(); //close file
}

void PokemonList::assignStatNames() {
	assignStatNamesEng(); //first populate the lit with english
	QString line; //place holder for a single line of text unparsed text
	static QStringList parsed_text; //QString list to hold a line of parsed text
	QFile file_stat_names("app/native/assets/data/stat_names.csv"); //load stat names file **LANGUAGE SPECIFIC**
	if (file_stat_names.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_stat_names); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			//match each stat to the pokemon's stat variable
			if (parsed_text.at(1)==m_language && parsed_text.at(0)=="1")
				m_stats.replace(parsed_text.at(0).toInt()-1, parsed_text.at(2));

			if (parsed_text.at(1)==m_language && parsed_text.at(0)=="2")
				m_stats.replace(parsed_text.at(0).toInt()-1, parsed_text.at(2));

			if (parsed_text.at(1)==m_language && parsed_text.at(0)=="3")
				m_stats.replace(parsed_text.at(0).toInt()-1, parsed_text.at(2));

			if (parsed_text.at(1)==m_language && parsed_text.at(0)=="4")
				m_stats.replace(parsed_text.at(0).toInt()-1, parsed_text.at(2));

			if (parsed_text.at(1)==m_language && parsed_text.at(0)=="5")
				m_stats.replace(parsed_text.at(0).toInt()-1, parsed_text.at(2));

			if (parsed_text.at(1)==m_language && parsed_text.at(0)=="6")
				m_stats.replace(parsed_text.at(0).toInt()-1, parsed_text.at(2));
		}
	}
	else
		std::cerr<<"Failed to open file: stat_names.csv "<<file_stat_names.error()<<endl;
	file_stat_names.close(); //close file
}

void PokemonList::assignAttributes() {
	static QStringList parsed_text; //QString list to hold a line of parsed text
	unsigned int index(0); //used for accessing pokemon array elements
	QString line; //place holder for a single line of text unparsed text
	double a,b;
	QFile file_pokemon("app/native/assets/data/pokemon.csv"); //load Pokemon height and weight
	if (file_pokemon.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_pokemon); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			if (parsed_text.at(0)==all_pokemon[index].getId() && parsed_text.at(0).toInt()<m_number_pokemon)
			{
				all_pokemon[index].setHeight(QString::number(parsed_text.at(3).toFloat()/10)); //assign height string after dividing by 10
				all_pokemon[index].setWeight(QString::number(parsed_text.at(4).toFloat()/10)); //assign weight string after dividing by 10
				index++; //move to next pokemon
			}
		}
	}
	else
		std::cerr<<"Failed to open file: pokemon.csv "<<file_pokemon.error()<<endl; //Could not load pokemon file*/
	file_pokemon.close();
}

void PokemonList::assignDescription() {
	static QStringList parsed_text; //QString list to hold a line of parsed text
	unsigned int index(0); //used for accessing pokemon array elements
	QString holder;
	QString line; //place holder for a single line of text unparsed text
	QFile file_pokemon_flavor("app/native/assets/data/pokemon_species_flavor_text.csv"); //load Pokemon height and weight
	if (file_pokemon_flavor.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_pokemon_flavor); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			if (index<m_number_pokemon && parsed_text.at(2)==ENG)
			{
				if (parsed_text.at(0)==all_pokemon[index].getId())
				{
					holder = parsed_text.at(3)+parsed_text.at(4)+parsed_text.at(5); //descriptions contain commas, this appends the strings together
					if (m_language!=ENG) //assign [English] if not on english (only english descriptions available)
						holder = parsed_text.at(3)+parsed_text.at(4)+parsed_text.at(5)+" [English]";
					all_pokemon[index].setDescription(holder); //set the appended text to its holder variable
					all_pokemon[index].setVersion(parsed_text.at(1)); //set the version from the first description
					index++; //move to next pokemon
				}
			}
		}
	}
	else
		std::cerr<<"Failed to open file: pokemon_species_flavor_text.csv "<<file_pokemon_flavor.error()<<endl; //Could not load flavor file
	file_pokemon_flavor.close(); //close file
}

void PokemonList::assignTypeId() {
	/***************************************ASSIGN TYPE 1 ID AND TYPE 2 ID***************************************/
	QString line; //place holder for a single line of text unparsed text
	static QStringList parsed_text; //QString list to hold a line of parsed text
	unsigned int index(0); //used for accessing pokemon array elements
	unsigned int line_number(1);
	bool first = true; //if reading the first line or not
	QFile file_pokemon_types("app/native/assets/data/pokemon_types.csv"); //load POKEMON TYPES file **LANGUAGE SPECIFIC**
	if (file_pokemon_types.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_pokemon_types); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			if (!first)
			{
				if (line_number<1066) //discount arbitrary list information
				{
					if (all_pokemon[index].getId()!=parsed_text.at(0)) // if pokemon id does not match id given is data chart
					{
						index++; //move to next pokemon
						if (parsed_text.at(2)=="1") //if the line contains slot 1 ID
							all_pokemon[index].setTypeId(parsed_text.at(1)); //set slot 1 ID
						line_number++; //next line
					}
					else
					{
						if (parsed_text.at(2)=="1") //if line contains slot 1 ID of current pokemon
							all_pokemon[index].setTypeId(parsed_text.at(1)); //assign slot 1 ID
						if (parsed_text.at(2)=="2") //if line contains slot 2 ID of current pokemon
							all_pokemon[index].setTypeId2(parsed_text.at(1)); //assign slot 2 ID
						line_number++; //next line
					}
				}
			}
			else
				first = false; //no longer accessing line 1
		}
	}
	else
		std::cerr<<"Failed to open file: pokemon_types.csv "<<file_pokemon_types.error()<<endl; //Could not load pokemon types file*/
	file_pokemon_types.close();
}

void PokemonList::assignTypeEng(unsigned int index) {
	QString line; //place holder for a single line of text unparsed text
	static QStringList parsed_text; //QString list to hold a line of parsed text
	QFile file_type_names("app/native/assets/data/type_names.csv"); //load POKEMON TYPES file **LANGUAGE SPECIFIC**
	if (file_type_names.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_type_names); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			{
				if (all_pokemon[index].getTypeId()==parsed_text.at(0) && parsed_text.at(1)==ENG)
				{
					all_pokemon[index].setType1(parsed_text.at(2));
				}
				else if (all_pokemon[index].getTypeId2()==parsed_text.at(0) && parsed_text.at(1)==ENG)
				{
					all_pokemon[index].setType2(parsed_text.at(2));
				}
			}
		}
	}
	else
		std::cerr<<"Failed to open file: type_names.csv "<<file_type_names.error()<<endl; //Could not load type names file
	file_type_names.close();
}

void PokemonList::assignTypes(unsigned int index) {
	assignTypeEng(index); //assign type names
	QString line; //place holder for a single line of text unparsed text
	static QStringList parsed_text; //QString list to hold a line of parsed text
	QFile file_type_names("app/native/assets/data/type_names.csv"); //load POKEMON TYPES file **LANGUAGE SPECIFIC**
	if (file_type_names.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is successfully opened
	{
		QTextStream in(&file_type_names); //create a text stream from the file
		while(!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			{
				if (all_pokemon[index].getTypeId()==parsed_text.at(0) && parsed_text.at(1)==m_language)
				{
					all_pokemon[index].setType1(parsed_text.at(2));
				}
				else if (all_pokemon[index].getTypeId2()==parsed_text.at(0) && parsed_text.at(1)==m_language)
				{
					all_pokemon[index].setType2(parsed_text.at(2));
				}
			}
		}
	}
	else
		std::cerr<<"Failed to open file: type_names.csv "<<file_type_names.error()<<endl; //Could not load type names file*/
	file_type_names.close();
}

void PokemonList::assignPokedexLanguages() {
	m_pokedex_languages.clear(); //clear list
	QString language = ENG;
	if(m_language==JAP)
		language = m_language;
	static QStringList pokedex_languages_tmp; //declare QStringList to be generated from splitting line
	QString line; //declare list to be generated form file
	int index_id = 0;
	QFile file_languages("app/native/assets/data/language_names.csv");
	if (file_languages.open(QIODevice::ReadOnly | QIODevice::Text)) //File opened sucessfully
	{
		QTextStream in(&file_languages); //create a text from the file
		while (!in.atEnd()) //read to eof
		{
			line = in.readLine(); //Read a line as a QString
			pokedex_languages_tmp = line.split(","); //split line of QString into array
			if (pokedex_languages_tmp.at(1)==language) //if language id is 9 for english
			{
				m_pokedex_languages.insert(index_id, pokedex_languages_tmp.at(2)); //insert string coressponding to name into list
				index_id++;
			}
		}
	}
	else
		std::cerr<<"Failed to load language_names.csv "<<file_languages.error()<<endl;
	file_languages.close();
}

void PokemonList::assignPokedexTypes() {
	m_pokedex_types.clear(); //clear list
	QStringList pokedex_types_tmp; //declare QStringList to be generated from splitting line
	QString insert;
	int index_id(0); //index of list to insert correct value
	QString line; //declare list to be generated form file
	bool assigned = false;
	QFile file_types("app/native/assets/data/type_names.csv");
	if (file_types.open(QIODevice::ReadOnly | QIODevice::Text)) //File opened sucessfully
	{
		QTextStream in(&file_types); //create a text from the file
		while (!in.atEnd()) //read to eof
		{
			line = in.readLine(); //Read a line as a QString
			pokedex_types_tmp = line.split(","); //split line of QString into array
			if (pokedex_types_tmp.at(1)==m_language)
			{
				m_pokedex_types.insert(index_id, pokedex_types_tmp.at(2)); //insert string coressponding to name into list
				index_id++;
				assigned=true; //if name is assigned, do not replace with english translation
			}
			if (pokedex_types_tmp.at(1)==ENG) //if language id is 9 for english
			{
				if (!assigned) //if there is not a translation available, add english translation
				{
					insert = pokedex_types_tmp.at(2)+" [English]"; // if language is not found and english is used
					m_pokedex_types.insert(index_id, insert); //insert string coressponding to name into list
					index_id++;
				}
				assigned = false; //reset
			}
		}
	}
	else
		std::cerr<<"Failed to load type_names.csv: "<<file_types.error()<<endl;
	file_types.close();
}

void PokemonList::assignAbilityId() {
	static QStringList parsed_text; //QString list to hold a line of parsed text
	unsigned int index_id(0); //index of list to insert correct value
	QString line; //declare list to be generated form file
	QFile file_abilities_id("app/native/assets/data/pokemon_abilities.csv");
	if (file_abilities_id.open(QIODevice::ReadOnly | QIODevice::Text)) //File opened sucessfully
	{
		QTextStream in(&file_abilities_id); //create a text from the file
		while (!in.atEnd()) //read to eof
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split line of text into comma separated elements and assign to list
			if (parsed_text.at(0).toInt()<1000 && parsed_text.at(0)!="pokemon_id")
			{
				if (all_pokemon[index_id].getId()!=parsed_text.at(0))
					index_id++;
				if (parsed_text.at(2)=="0" && parsed_text.at(3)=="1")
					all_pokemon[index_id].setAbilityId(parsed_text.at(1));
				if (parsed_text.at(2)=="0" && parsed_text.at(3)=="2")
					all_pokemon[index_id].setAbilityId2(parsed_text.at(1));
				if (parsed_text.at(2)=="1")
					all_pokemon[index_id].setHiddenAbilityId(parsed_text.at(1));
			}
		}
	}
	else
		std::cerr<<"Failed to load type_names.csv: "<<file_abilities_id.error()<<endl;
	file_abilities_id.close();
}

void PokemonList::assignAbilities(int index) {
	 //if slots have been filled with a string
	bool slot1 = false;
	bool slot2 = false;
	bool slot3 = false;
	QString line; //place holder for a single line of text unparsed text
	static QStringList parsed_text; //QString list to hold a line of parsed text

	QFile file("app/native/assets/data/ability_names.csv"); //open file
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) //if file is opened successfully
	{
		QTextStream in(&file); //create a text stream from file
		while (!in.atEnd()) //read until the end of file
		{
			line = in.readLine(); //read a line as a QString
			parsed_text = line.split(","); //split QString into QString list

			if (parsed_text.at(0)==all_pokemon[index].getAbilityId() && parsed_text.at(1)==m_language) //if id matches and selected language
			{
				all_pokemon[index].setAbilitySlot1(parsed_text.at(2)); //assign ability
				slot1 = true; //slot has been assigned already
			}
			if (parsed_text.at(0)==all_pokemon[index].getAbilityId() && parsed_text.at(1)==ENG && !slot1) // if id matches and slot has not been assigned, use english + [Eng]
			{
				slot1 = false;
				all_pokemon[index].setAbilitySlot1(parsed_text.at(2)+" "+"[Eng]");
			}

			if (parsed_text.at(0)==all_pokemon[index].getAbilityId2() && parsed_text.at(1)==m_language)
			{
				all_pokemon[index].setAbilitySlot2(parsed_text.at(2));
				slot2 = true;
			}
			if (parsed_text.at(0)==all_pokemon[index].getAbilityId2() && parsed_text.at(1)==ENG && !slot2) // if id matches and slot has not been assigned, use english + [Eng]
			{
				slot2 = false;
				all_pokemon[index].setAbilitySlot2(parsed_text.at(2)+" "+"[Eng]");
			}
			if (parsed_text.at(0)==all_pokemon[index].getHiddenAbilityId() && parsed_text.at(1)==m_language)
			{
				all_pokemon[index].setAbilitySlot3(parsed_text.at(2));
				slot3 = true;
			}
			if (parsed_text.at(0)==all_pokemon[index].getHiddenAbilityId() && parsed_text.at(1)==ENG && !slot3) // if id matches and slot has not been assigned, use english + [Eng]
			{
				slot3 = false;
				all_pokemon[index].setAbilitySlot3(parsed_text.at(2)+" "+"[Eng]");
			}
		}
	}
	else
		std::cerr<<"Failed to load ability_names.csv: "<<file.error()<<endl;
	file.close(); //close file
}

int PokemonList::initTempList() {
	int tmp(0);
	m_temp_list.clear(); //clear list
	for (int i(0); i<m_number_pokemon; i++)
	{
		if (all_pokemon[i].getTypeId().toInt()==m_type_id || all_pokemon[i].getTypeId2().toInt()==m_type_id || m_type_id==-1)//if types are matched or all types
		{
			m_temp_list.push_back(all_pokemon[i]); //add pokemon to the temp list
			tmp++; //another pokemon has been added
		}
	}
	return tmp; //return number of pokemon in list
}

void PokemonList::setType(int type) {
	m_type_id = type;
}

QString PokemonList::getLanguage()const {
	return m_language;
}

void PokemonList::setTypeId(int type) {
	m_type_id = type;
}

void PokemonList::setListInit(bool init) {
	m_list_init = init;
}

void PokemonList::setNumberPokemon(unsigned int number) {
	m_number_pokemon = number;
}

int PokemonList::getTypeId() const {
	return m_type_id;
}

void PokemonList::setLanguage(QString language) {
	m_language = language;
}

bool PokemonList::getListInit() const {
	return m_list_init;
}

unsigned int PokemonList::getNumberPokemon() {
	return m_number_pokemon;
}
