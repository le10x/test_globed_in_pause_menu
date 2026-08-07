#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    // En GD 2.2081 init requiere el parámetro bool 'unfocused'
    bool init(bool unfocused) {
        // Pasar el argumento obligatoriamente a la inicialización original de RobTop
        if (!PauseLayer::init(unfocused)) return false;

        // 1. Verificación segura: Si el usuario no tiene Globed activo, no añadimos el botón
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 2. Crear el botón visual utilizando un Sprite Frame existente del juego
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(MyPauseLayer::onGlobedButton)
        );

        // 3. Buscar el contenedor usando la nomenclatura oficial de Node IDs
        if (auto menu = this->getChildByID("left-button-menu")) {
            // Añadir el botón al menú
            menu->addChild(button);
            
            // Asignarle un ID único propio con el sufijo del mod asignado por Geode
            button->setID("globed-pause-button"_spr);
            
            // Reordenar y actualizar el diseño de los botones automáticamente
            menu->updateLayout();
        }

        return true;
    }

    // Callback que se ejecuta cuando el jugador presiona tu nuevo botón
    void onGlobedButton(CCObject* sender) {
        // En Geode v5, para despachar hilos/eventos globales de texto se usa DispatchEvent
        // Esto envía de forma segura la orden que Globed escucha para desplegar su interfaz
        auto ev = DispatchEvent("dankmeme.globed2/open-menu", nullptr);
        ev.post();
        
        // Opcional: Descomenta la línea de abajo si quieres que se reanude el nivel al tocar el botón
        // this->onResume(sender);
    }
};
