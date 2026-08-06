#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init() {
        // Ejecutar primero la inicialización original de RobTop
        if (!PauseLayer::init()) return false;

        // 1. Verificación segura: Si el usuario no tiene Globed activo, no añadimos el botón
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 2. Crear el botón visual utilizando un Sprite Frame existente del juego
        // "GJ_chatBtn_001.png" es el ícono estándar de burbuja de diálogo/multiplayer
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; // Resguardo por si el sprite falla

        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(MyPauseLayer::onGlobedButton)
        );

        // 3. Buscar el contenedor usando la nomenclatura oficial de Node IDs
        // "left-button-menu" es el ID estándar para la fila vertical de botones a la izquierda
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
        auto globedMod = Loader::get()->getLoadedMod("dankmeme.globed2");
        
        if (globedMod) {
            // El sistema de Geode permite despachar eventos hacia otros mods de forma segura
            // Enviamos un evento genérico al Mod para invocar la apertura de su UI
            geode::AttributeEvent("open-menu", globedMod).post();
            
            // Alternativa visual: Si deseas cerrar el menú de pausa al tocar el botón, descomenta la línea de abajo:
            // this->onResume(sender);
        }
    }
};
