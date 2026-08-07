#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init(bool unfocused) {
        // 1. Ejecutar primero la inicialización original de RobTop
        if (!PauseLayer::init(unfocused)) return false;

        // 2. Verificación segura: Si Globed no está activo, salimos de inmediato
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 3. Crear el botón utilizando el sprite nativo de RobTop
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(MyPauseLayer::onGlobedButton)
        );
        if (!button) return true; // Resguardo extra de memoria

        // 4. Buscar el contenedor izquierdo de forma totalmente segura
        auto menu = this->getChildByID("left-button-menu");
        
        // ¡CRÍTICO PARA ANDROID!: Si por un retraso de carga el menú es un puntero nulo, 
        // salimos de la función silenciosamente para evitar que el juego se crashee.
        if (!menu) {
            return true; 
        }

        // 5. Inyectar el botón de forma limpia solo si el menú es válido
        menu->addChild(button);
        button->setID("globed-pause-button"_spr);
        menu->updateLayout();

        return true;
    }

    // Callback al presionar el botón
    void onGlobedButton(CCObject* sender) {
        // Enviar la notificación nativa usando el centro de Cocos2d-x
        CCNotificationCenter::sharedNotificationCenter()->postNotification("dankmeme.globed2/open-menu", nullptr);
    }
};
