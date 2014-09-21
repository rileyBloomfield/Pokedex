/*
 * pokemon.h
 *
 *  Created on: Nov 19, 2013
 *      Author: Riley
 */

#ifndef POKEMON_H_
#define POKEMON_H_

#include <QString>

class Pokemon {
public:
	Pokemon();
	virtual ~Pokemon();

	//Set methods
	void setId(QString id);
	void setName(QString name);
	void setEnglish(bool english);
	void setType1(QString type1);
	void setType2(QString type2);
	void setTypeId(QString type_id);
	void setTypeId2(QString typeId2);
	void setAbilityId(QString abilityId);
	void setAbilityId2(QString abilityId2);
	void setHiddenAbilityId(QString hiddenAbilityId);
	void setAbilitySlot1(QString slot1);
	void setAbilitySlot2(QString slot2);
	void setAbilitySlot3(QString slot3);
	void setHp(QString hp);
	void setAttack(QString Attack);
	void setDefence(QString Defence);
	void setSpAttack(QString spAttack);
	void setSpDefence(QString spDefence);
	void setSpeed(QString speed);
	void setVersion(QString version);
	void setHeight(QString height);
	void setWeight(QString weight);
	void setDescription(QString description);

	//Get methods
	QString getId()const;
	QString getName()const;
	QString getType1()const;
	QString getType2()const;
	QString getTypeId()const;
	QString getTypeId2()const;
	QString getAbilityId()const;
	QString getAbilityId2()const;
	QString getHiddenAbilityId()const;
	QString getAbilitySlot1()const;
	QString getAbilitySlot2()const;
	QString getAbilitySlot3()const;
	QString getHp()const;
	QString getAttack()const;
	QString getDefence()const;
	QString getSpAttack()const;
	QString getSpDefence()const;
	QString getSpeed()const;
	QString getVersion()const;
	QString getHeight()const;
	QString getWeight()const;
	QString getDescription()const;
	bool getEnglish()const;

	//Other methods
	QString nameDisplay(); //combines id, name and type into one QString to output on scroll list
	QString nameDisplayItem(); //combines required information for ItemPage header

private:
	QString m_id;
	QString m_name;
	bool m_english;
	QString m_type1;
	QString m_type2;
	QString m_type_id;
	QString m_type_id2;
	bool m_english_type;
	QString m_ability_id;
	QString m_ability_id2;
	QString m_hidden_ability_id;
	QString m_ability_slot1;
	QString m_ability_slot2;
	QString m_ability_slot3;
	QString m_hp;
	QString m_attack;
	QString m_defence;
	QString m_spAttack;
	QString m_spDefence;
	QString m_speed;
	QString m_version;
	QString m_height;
	QString m_weight;
	QString m_description;
};

#endif /* POKEMON_H_ */
