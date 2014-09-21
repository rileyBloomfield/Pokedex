#include "applicationui.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/DropDown>
#include <bb/cascades/RadioGroup>
#include <bb/cascades/Label>
#include <bb/cascades/ListView>

#include <iostream>
#include "pokemonlist.h"

using namespace bb::cascades;

using std::cerr;
using std::endl;

const QString ENG = "9";
const QString JAP = "1";

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :QObject(app), m_pokemonList(0)
{
	// Create scene document from main.qml asset, the parent is set
	// to ensure the document gets destroyed properly at shut down.
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

	// Create root object for the UI
	m_root = qml->createRootObject<AbstractPane>();

	// Set the handle for the "pokedex" object from QML
	qml->setContextProperty("pokedex", this);

	// Create the "model" to store data about pokemon
	m_pokemonList = new PokemonList(this);
	qml->setContextProperty("pokemon_list", m_pokemonList);

	//Create array of pokemon the size of the number of pokemon in the pokemon types
	m_pokemonList->setNumberPokemon(m_pokemonList->assignPokemonNumber());
	m_pokemonList->all_pokemon = new Pokemon[m_pokemonList->getNumberPokemon()];

	// Populate radio buttons for language settings
	RadioGroup *radio(0);	// A pointer to hold the RadioGroup UI object
	// Search the root QML object for a control named "pokemon_types"
	radio = m_root->findChild<RadioGroup *>("pokedex_languages");
	//Access setPokedexLanguages function from PokemonList class to set languages on language menu
	m_pokemonList->assignPokedexLanguages();
	//Populate buttons
	if (radio) // did we succeed in getting a pointer to the radio button UI control?
	{
		for (int i(0); i<10; i++)
		{
			if (i==0 && m_pokemonList->getLanguage()==JAP) //if starting on japanese, make selected
				radio->add(Option::create().text(m_pokemonList->m_pokedex_languages.at(i)).value(1).selected(true));
			if (i==8 && m_pokemonList->getLanguage()==ENG) //if starting on english, make selected
				radio->add(Option::create().text("English").value(9).selected(true));
			if (i==7 && m_pokemonList->getLanguage()==JAP)
				radio->add(Option::create().text("English").value(9));
			else
				radio->add(Option::create().text(m_pokemonList->m_pokedex_languages.at(i)).value(i+1)); // Add another option
		}
	}
	// Set created root object as the application scene
	app->setScene(m_root);
}

void ApplicationUI::typeSelected(int type) {
	cerr << "In typeSelected() with " << "type=" << type << endl;

	ListView *pokeList(0);
	pokeList = m_root->findChild<ListView*>(); //Selects the Listview
	pokeList->resetDataModel(); //unloads the data
	m_pokemonList->setTypeId(type);
	pokeList->setDataModel(m_pokemonList); //reloads the data
	//m_pokemonList->m_list_size = m_pokemonList->m_temp_list.length();
	Label *status(0);	// A pointer to hold the Label UI object
	// Search the root QML object for a control named "status"
	status = m_root->findChild<Label *>("pokedex_status");
	if (status)
	{ // did we succeed in getting a pointer to the Label UI control?
		// Yes. Now set the text as appropriate
		status->setText( QString("Found %1 Pok").arg(m_pokemonList->childCount(QVariantList())) +QChar(0x0E9)+QString("mon") );
	}
	else
	{
		cerr << "failed to find status " << endl;
	}
}

void ApplicationUI::languageSelected(int language) {
	cerr << "In languageSelected() with " << "language=" << language << endl;

	QString out = QString::number(language); //convert language int to a string
	m_pokemonList->setLanguage(out); //assign to pokemonList language member variable
	ListView *pokeList(0);
	pokeList = m_root->findChild<ListView*>(); //Selects the Listview
	pokeList->resetDataModel(); //unloads the data
	m_pokemonList->setListInit(true); //assure complete repopulation
	pokeList->setDataModel(m_pokemonList); //reloads the data
	initDropdown(); //call to empty and repopulate dropdown
}

void ApplicationUI::initDropdown() {
	// Populate the dropdown list of types
	DropDown *dropDown(0);	// pointer to hold the DropDown UI object
	// Search the root QML object for a control named "pokemon_types"
	dropDown = m_root->findChild<DropDown *>("pokemon_types");
	//remove all elements from dropdown
	dropDown->removeAll();
	//call assignTypes function from PokemonList class to assign types with selected language
	m_pokemonList->assignPokedexTypes();
	//repopulate dropdown menu with chaged types
	if (dropDown)
	{
		if (m_pokemonList->getLanguage()==JAP) //if language is japanese
		{
			QString all_types = QString::fromLocal8Bit("すべてのタイプ")+" [All Types]";
			dropDown->add(Option::create().text(all_types).value(-1).selected(true)); //change all types to japanese
		}
		else
			dropDown->add(Option::create().text("All Types").value(-1).selected(true));
		for (int i(0); i<18; i++)
		{
				dropDown->add(Option::create().text(m_pokemonList->m_pokedex_types[i]).value(i+1));
		}
	}
}
