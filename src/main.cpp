#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init(bool unfocused) {
        if (!PauseLayer::init(unfocused)) return false;

        // 1. Verificar si Globed está activo
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 2. Crear el botón utilizando el sprite nativo de RobTop
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(MyPauseLayer::onGlobedButton)
        );

        // 3. Colocar el botón dentro del menú izquierdo
        if (auto menu = this->getChildByID("left-button-menu")) {
            menu->addChild(button);
            button->setID("globed-pause-button"_spr);
            menu->updateLayout();
        }

        return true;
    }

    // Callback al presionar el botón
    void onGlobedButton(CCObject* sender) {
        // Usar el centro de notificaciones nativo de Cocos2d-x para despachar el evento string.
        // Esto envía la cadena "dankmeme.globed2/open-menu" que Globed escucha globalmente.
        CCNotificationCenter::sharedNotificationCenter()->postNotification("dankmeme.globed2/open-menu", nullptr);
    }
};
