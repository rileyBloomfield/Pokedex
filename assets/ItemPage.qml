import bb.cascades 1.2

Page {
    property alias b_name: titlebar.title //b_name_label.text
    property alias type1: type1_label.text // "type" property of this screen is mapped to the text field of the UI element with the id of "type_label"
    property alias type2: type2_label.text
    property alias hp: hp_label.text
    property alias z_attack: attack_label.text //added z_ to stop being displayed as name
    property alias defence: defence_label.text
    property alias spAttack: spAttack_label.text
    property alias spDefence: spDefence_label.text
    property alias speed: speed_label.text
    property alias totStat: totStat_label.text
    property alias height: height_label.text
    property alias weight: weight_label.text
    property alias description: description_label.text
    property alias version: version_label.text
    property alias abilitySlot1: abilitySlot1_label.text
    property alias abilitySlot2: abilitySlot2_label.text
    property alias abilitySlot3: abilitySlot3_label.text
    property alias stat1: stat1_label.text
    property alias stat2: stat2_label.text
    property alias stat3: stat3_label.text
    property alias stat4: stat4_label.text
    property alias stat5: stat5_label.text
    property alias stat6: stat6_label.text
    
    titleBar: TitleBar {
        id: titlebar
    }
    
    Container {
        
        Container { // Make a container to show pokemon type 1
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label{
                text: "Type: "
                textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            }
            Label {
                id: type1_label // Name this as type_label so that the property alias above can set the text property of this item
            } 
            Label {
                id: type2_label
            } 
        }
        Container { // Make a container to show pokemon hp
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                id: stat1_label
                textStyle.fontStyle: FontStyle.Italic
                //textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            } 
            Label {
                id: hp_label // Name this as type_label so that the property alias above can set the text property of this item
            } 
        }
        Container { // Make a container to show attack
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                id: stat2_label
                textStyle.fontStyle: FontStyle.Italic
               // textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            } 
            Label {
                id: attack_label // Name this as type_label so that the property alias above can set the text property of this item
            } 
        }
        Container { // Make a container to show pokemon defence
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                id: stat3_label
                textStyle.fontStyle: FontStyle.Italic
               // textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            } 
            Label {
                id: defence_label // Name this as type_label so that the property alias above can set the text property of this item
            } 
        }
        Container { // Make a container to show pokemon spattack
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                id: stat4_label
                textStyle.fontStyle: FontStyle.Italic
               // textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            } 
            Label {
                id: spAttack_label // Name this as type_label so that the property alias above can set the text property of this item
            } 
        }
        Container { // Make a container to show pokemon spDefence
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                id: stat5_label
                textStyle.fontStyle: FontStyle.Italic
               // textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            } 
            Label {
                id: spDefence_label // Name this as type_label so that the property alias above can set the text property of this item
            } 
        }
        Container { // Make a container to show pokemon speed
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                id: stat6_label
                textStyle.fontStyle: FontStyle.Italic
               // textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            } 
            Label {
                id: speed_label // Name this as type_label so that the property alias above can set the text property of this item
            } 
        }
        Container {
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                text: "Total: "
                textStyle.fontStyle: FontStyle.Italic
                textStyle.color: Color.Black // Show this text
                }
            Label {
               id: totStat_label
                
            }
    }
            Label{
                text: "Attributes: "
                textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            }
            Container {
                layout: StackLayout { // Lay out sub items left-to-right
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: "Version: "
                    textStyle.fontStyle: FontStyle.Italic
                    textStyle.color: Color.DarkRed // Show this text
                }
                Label {
                    id: version_label
                }
            }
        Container { // Make a container to show pokemon height
            layout: StackLayout { // Lay out sub items left-to-right
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                text: "Height(m): "
                textStyle.fontStyle: FontStyle.Italic
              //  textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            } 
            Label {
                id: height_label 
            } 
            Container { // Make a container to show pokemon weight
                layout: StackLayout { // Lay out sub items left-to-right
                    orientation: LayoutOrientation.LeftToRight
                }
                Label { 
                    text: "Weight(kg): "
                    textStyle.fontStyle: FontStyle.Italic
                   // textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.DarkRed // Show this text
                } 
                Label {
                    id: weight_label 
                } 
            }
        }
        Label{
            text: "Abilities: "
            textStyle.fontWeight: FontWeight.Bold
            textStyle.color: Color.DarkRed // Show this text
        }
    Container { // Make a container to show pokemon type 1
        layout: StackLayout { // Lay out sub items left-to-right
            orientation: LayoutOrientation.LeftToRight
        }
       
        Label {
            id: abilitySlot1_label // Name this as type_label so that the property alias above can set the text property of this item
        } 
        Label {
            id: abilitySlot2_label
        }
    }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
        Label {
            text: "Hidden: "
            textStyle.fontStyle: FontStyle.Italic
            textStyle.color: Color.DarkRed // Show this text
        }
        Label {
            id: abilitySlot3_label
        }
    }
    
    Label { 
        text: "Description: "
        textStyle.fontWeight: FontWeight.Bold
        textStyle.color: Color.DarkRed // Show this text
    } 
    Container { // Make a container to show pokemon description
        layout: StackLayout { // Lay out sub items left-to-right
            orientation: LayoutOrientation.LeftToRight
        }
        Label {
            multiline: true
            id: description_label
        } 
    }
}
}