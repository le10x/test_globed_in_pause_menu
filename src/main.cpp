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

        // 2. Crear el botón
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(MyPauseLayer::onGlobedButton)
        );

        // 3. Insertar en el menú izquierdo
        if (auto menu = this->getChildByID("left-button-menu")) {
            menu->addChild(button);
            button->setID("globed-pause-button"_spr);
            menu->updateLayout();
        }

        return true;
    }

    // Callback al presionar el botón
    void onGlobedButton(CCObject* sender) {
        // Obtenemos el mod de Globed de forma segura
        if (auto globedMod = Loader::get()->getLoadedMod("dankmeme.globed2")) {
            // Esta es la API universal de Geode para disparar acciones en otros mods por su ID
            // Le envía la orden directa de abrir su menú sin usar clases extrañas
            Loader::get()->dispatchEvent("dankmeme.globed2/open-menu", nullptr);
        }
    }
};
