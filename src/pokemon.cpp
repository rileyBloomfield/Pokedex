/*
 * pokemon.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: Riley
 */

#include "pokemon.h"

Pokemon::Pokemon(): m_id("default"), m_name("default"), m_english(true), m_english_type(true), m_type1("default"), m_type2("None"), m_type_id("default"),
m_type_id2("default"), m_ability_id("default"), m_ability_id2("default"), m_hidden_ability_id("default"), m_ability_slot1("default"), m_ability_slot2("None"),
m_ability_slot3("None"), m_hp("default"), m_attack("default"), m_defence("default"), m_spAttack("default"), m_spDefence("default"), m_speed("default"),
m_version("default"), m_height("Unavailable"), m_weight("Unavailable"), m_description("Unavailable") {}


Pokemon::~Pokemon(){}

void Pokemon::setId(QString id) {
	m_id = id;
}

void Pokemon::setName(QString name) {
	m_name = name;
}

void Pokemon::setType1(QString type1) {
	m_type1 = type1;
}

void Pokemon::setType2(QString type2) {
	m_type2 = type2;
}

void Pokemon::setVersion(QString version) {
	m_version = version;
}

QString Pokemon::nameDisplay() {
	QString output = "blank";
	QString number = "#";
	QString space = " ";
	QString l_brace = "[";
	QString r_brace = "]";
	QString zero = "0";
	QString comma = ",";
	QString slot1 = m_type1;
	QString slot2 = comma+" "+m_type2;
	QString eng = "";
	if (m_english)
		eng = "[English]";
	if (m_type2=="None")
		slot2 = "";
	if (m_id.toInt()<10)
		output = number+zero+zero+m_id+space+m_name+space+eng+space+l_brace+slot1+slot2+r_brace;
	else if (m_id.toInt()<100 && m_id.toInt()>9)
		output = number+zero+m_id+space+m_name+space+eng+space+l_brace+slot1+slot2+r_brace;
	else if (m_id.toInt()>99)
		output = number+m_id+space+m_name+space+eng+space+l_brace+slot1+slot2+r_brace;

	return output;
}

QString Pokemon::nameDisplayItem() {
	QString output = "blank";
	QString number = "#";
	QString space = " ";
	QString zero = "0";
	QString comma = ",";
	QString eng = "";
	if (m_english)
		eng = "[English]";
	if (m_id.toInt()<10)
		output = number+zero+zero+m_id+space+m_name+space+eng;
	else if (m_id.toInt()<100 && m_id.toInt()>9)
		output = number+zero+m_id+space+m_name+space+eng;
	else if (m_id.toInt()>99)
		output = number+m_id+space+m_name+space+eng;

	return output;
}

QString Pokemon::getId()const {
	return m_id;
}

QString Pokemon::getName() const{
	return m_name;
}

QString Pokemon::getType1() const {
	return m_type1;
}

QString Pokemon::getType2() const {
	return m_type2;
}

QString Pokemon::getHp() const {
	return m_hp;
}

QString Pokemon::getAttack() const {
	return m_attack;
}

QString Pokemon::getDefence() const {
	return m_defence;
}

QString Pokemon::getSpAttack() const {
	return m_spAttack;
}

QString Pokemon::getSpDefence() const {
	return m_spDefence;
}

QString Pokemon::getSpeed()const {
	return m_speed;
}

QString Pokemon::getVersion() const {
	return m_version;
}

void Pokemon::setHp(QString hp) {
	m_hp = hp;
}

void Pokemon::setAttack(QString attack) {
	m_attack = attack;
}

void Pokemon::setDefence(QString defence) {
	m_defence = defence;
}

void Pokemon::setSpAttack(QString spAttack) {
	m_spAttack = spAttack;
}

void Pokemon::setSpDefence(QString spDefence) {
	m_spDefence = spDefence;
}

void Pokemon::setSpeed(QString speed) {
	m_speed = speed;
}

void Pokemon::setTypeId(QString type_id) {
	m_type_id = type_id;
}

void Pokemon::setTypeId2(QString typeId2) {
	m_type_id2 = typeId2;
}

QString Pokemon::getTypeId() const {
	return m_type_id;
}

QString Pokemon::getTypeId2() const {
	return m_type_id2;
}

void Pokemon::setHeight(QString height) {
	m_height = height;
}

void Pokemon::setWeight(QString weight) {
	m_weight = weight;
}

QString Pokemon::getHeight() const {
	return m_height;
}

QString Pokemon::getWeight() const {
	return m_weight;
}

void Pokemon::setDescription(QString description) {
	m_description = description;
}

QString Pokemon::getDescription()const {
	return m_description;
}

void Pokemon::setAbilityId(QString abilityId) {
	m_ability_id = abilityId;
}

void Pokemon::setHiddenAbilityId(QString hiddenAbilityId) {
	m_hidden_ability_id = hiddenAbilityId;
}

QString Pokemon::getAbilityId() const {
	return m_ability_id;
}

QString Pokemon::getHiddenAbilityId() const {
	return m_hidden_ability_id;
}

void Pokemon::setAbilityId2(QString abilityId2) {
	m_ability_id2 = abilityId2;
}

QString Pokemon::getAbilityId2() const {
	return m_ability_id2;
}

void Pokemon::setAbilitySlot1(QString slot1) {
	m_ability_slot1 = slot1;
}

void Pokemon::setAbilitySlot2(QString slot2) {
	m_ability_slot2 = slot2;
}

void Pokemon::setAbilitySlot3(QString slot3) {
	m_ability_slot3 = slot3;
}

QString Pokemon::getAbilitySlot1() const {
	return m_ability_slot1;
}

QString Pokemon::getAbilitySlot2() const {
	return m_ability_slot2;
}

QString Pokemon::getAbilitySlot3() const {
	return m_ability_slot3;
}

bool Pokemon::getEnglish()const {
	return m_english;
}

void Pokemon::setEnglish(bool english) {
	m_english = english;
}
