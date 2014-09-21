import bb.cascades 1.2
NavigationPane {
    id: nav
    Menu.definition: MenuDefinition {
        actions: [
            ActionItem {
                title: "Language"
                onTriggered: {
                    nav.push(languageSelection)
                }            
            }
        ]
    }
    
    Page {
        Container {
            Container {
                background: Color.create("#B40404")
                horizontalAlignment: HorizontalAlignment.Fill
                Label {
                    id: title
                    text: "SE 2250 Project - Pokédex"
                    textStyle.fontSize: FontSize.Medium
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                    horizontalAlignment: HorizontalAlignment.Center
                    objectName: "title"
                }
            }
            DropDown {
                id: pokemon_types
                title: "Pokémon Type"
                onSelectedIndexChanged: {
                    pokedex.typeSelected(selectedValue)
                }
                options: Option {
                    text: "All Types"
                    value: -1
                    selected: true
                }
                objectName: "pokemon_types"
            }
            Label { // status text
                id: status
                text: ""
                objectName: "pokedex_status"
                textStyle.fontSize: FontSize.Small
                textStyle.color: Color.create("#B40404")
                horizontalAlignment: HorizontalAlignment.Center
            }
            ListView { // This is the 'view' part of the model-view-controller
                //dataModel: pokemon_list // Connect 'pokemon_list' as the 'model' for this view
                onTriggered: { // What to do when user selects an item
                    if (indexPath.length == 1) { // this is a first level item
                        var chosenItem = dataModel.data(indexPath);	// Get the data from dataModel
                        var contentpage = itemPageDefinition.createObject(); // create the sub-page
                    
                        contentpage.b_name = chosenItem.b_name;
                        contentpage.type1 = chosenItem.type1
                        contentpage.type2 = chosenItem.type2
                        contentpage.hp = chosenItem.hp
                        contentpage.z_attack = chosenItem.z_attack
                        contentpage.defence = chosenItem.defence
                        contentpage.spAttack = chosenItem.spAttack
                        contentpage.spDefence = chosenItem.spDefence
                        contentpage.speed = chosenItem.speed
                        contentpage.totStat = chosenItem.totStat
                        contentpage.height = chosenItem.height
                        contentpage.weight = chosenItem.weight
                        contentpage.description = chosenItem.description
                        contentpage.version = chosenItem.version
                        contentpage.abilitySlot1 = chosenItem.abilitySlot1
                        contentpage.abilitySlot2 = chosenItem.abilitySlot2
                        contentpage.abilitySlot3 = chosenItem.abilitySlot3
                        contentpage.stat1 = chosenItem.stat1
                        contentpage.stat2 = chosenItem.stat2
                        contentpage.stat3 = chosenItem.stat3
                        contentpage.stat4 = chosenItem.stat4
                        contentpage.stat5 = chosenItem.stat5
                        contentpage.stat6 = chosenItem.stat6
                        
                        nav.push(contentpage); // Show the page
                    }
                }
            }
        }
    }
    attachedObjects: [
        ComponentDefinition {
            id: itemPageDefinition
            source: "ItemPage.qml"
        },
        Page {
            id: languageSelection
            titleBar: TitleBar {
                title: "Select Language"
            }
            RadioGroup {
                id: pokedex_languages
                objectName: "pokedex_languages"
                onSelectedIndexChanged: {
                    pokedex.languageSelected(selectedValue)
                }
            }
        }
    ]
    onPopTransitionEnded: {
        if (page.id == itemPageDefinition)
            page.destroy();
    }
}
