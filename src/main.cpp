#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

// Definimos una estructura limpia para estructurar nuestro evento inter-mod personalizado
struct GlobedMenuEvent : public Event {
    GlobedMenuEvent() {}
};

class $modify(MyPauseLayer, PauseLayer) {
    bool init(bool unfocused) {
        if (!PauseLayer::init(unfocused)) return false;

        // 1. Verificar de forma segura si Globed está activo
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 2. Crear el botón utilizando un sprite nativo de RobTop
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(MyPauseLayer::onGlobedButton)
        );

        // 3. Insertar el botón en el menú de la izquierda del PauseLayer
        if (auto menu = this->getChildByID("left-button-menu")) {
            menu->addChild(button);
            button->setID("globed-pause-button"_spr);
            menu->updateLayout();
        }

        return true;
    }

    // Callback que se ejecuta cuando el jugador pulsa el botón
    void onGlobedButton(CCObject* sender) {
        // En Geode, disparar un evento estructurado con una ID de cadena se realiza publicando
        // su disparador correspondiente hacia la red global del Loader
        GlobedMenuEvent ev;
        ev.post();

        // Opcional: Descomenta la línea de abajo si prefieres que el menú de pausa se cierre solo
        // this->onResume(sender);
    }
};
