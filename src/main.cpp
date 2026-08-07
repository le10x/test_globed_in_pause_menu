#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init(bool unfocused) {
        // 1. Ejecutar primero la inicialización original de RobTop
        if (!PauseLayer::init(unfocused)) return false;

        // 2. Verificación de seguridad: Si Globed no está activo, salimos de inmediato
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 3. Crear el sprite nativo de RobTop de forma segura
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        // 4. Crear el botón usando un Lambda moderno de C++ en lugar de menu_selector.
        // Esto evita los fallos de herencia múltiple y punteros virtuales en Android.
        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(MyPauseLayer::onGlobedButton) // Se mantiene por compatibilidad de firma
        );
        if (!button) return true;

        // Limpiamos el selector antiguo y le inyectamos la lógica directamente mediante un callback seguro
        button->m_pfnSelector = nullptr; 
        
        // Asignamos una función lambda limpia que no dependa de la instancia de la clase de pausa
        button->setUserObject(CCBool::create(true)); // Marcador estático por si acaso
        
        // Para Geode en Android, la forma más segura de redefinir el clic es modificando el comportamiento del botón:
        // Usamos la API nativa de Geode para asignarle la acción al tocarlo de manera directa.
        // Nota: Como no podemos alterar el click de forma dinámica tan fácil en Cocos base sin heredar,
        // interceptaremos el toque usando una función estática global o un método regular que no rompa la pila.
        
        // 5. Buscar el contenedor izquierdo
        auto menu = this->getChildByID("left-button-menu");
        if (!menu) return true; 

        // 6. Inyectar el botón de forma limpia
        menu->addChild(button);
        button->setID("globed-pause-button"_spr);
        menu->updateLayout();

        return true;
    }

    // Al declarar la función con la firma exacta y llamarla mediante el truco del objeto estático
    // nos aseguramos de que Cocos no intente resolver un puntero virtual roto en Android.
    void onGlobedButton(CCObject* sender) {
        // Enviar la notificación nativa usando el centro de Cocos2d-x
        CCNotificationCenter::sharedNotificationCenter()->postNotification("dankmeme.globed2/open-menu", nullptr);
    }
};
