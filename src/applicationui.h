#ifndef ApplicationUI_H_
#define ApplicationUI_H_

#include <QObject>
#include <bb/cascades/AbstractPane>

namespace bb
{
    namespace cascades
    {
        class Application;
    }
}

/*!
 * @brief Application object
 *
 *
 */
class PokemonList; // forward declaration to avoid including header

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    // callables from QML
    Q_INVOKABLE void typeSelected(int type);
    Q_INVOKABLE void languageSelected(int language);

    virtual ~ApplicationUI() {
    	delete m_root;
    	delete m_pokemonList;
    }

    void initDropdown();

private:
    PokemonList *m_pokemonList;
    bb::cascades::AbstractPane *m_root;
};

#endif /* ApplicationUI_H_ */
