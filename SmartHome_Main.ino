
#include "config.h"
#include "buttonManager.h"
#include "ledController.h"
#include "modeManager.h"

// Instanciar objetos
ButtonManager buttonManager;
LedController ledController;
ModeManager modeManager;

void setup() {
  Serial.begin(9600);
  Serial.println("=== SISTEMA DE CONTROL POR BOTÓN ===");
  Serial.println("Pulsaciones del botón:");
  Serial.println("1x: Modo Normal (Verde)");
  Serial.println("2x: Modo Alerta (Rojo parpadeante)");
  Serial.println("3x: Modo Fiesta (Ciclo RGB)");
  Serial.println("4x: Modo Demo (Respiración azul)");
  Serial.println("=====================================");

  buttonManager.initialize();
  ledController.initialize();
  modeManager.initialize();
}

void loop() {
  // Actualizar gestor de botón
  buttonManager.update();
  
  // Verificar si hay nuevas pulsaciones disponibles
  if (buttonManager.isNewPressAvailable()) {
    int pressCount = buttonManager.getPressCount();
    
    Serial.print("Procesando ");
    Serial.print(pressCount);
    Serial.println(" pulsaciones");
    
    // Actualizar modo basado en las pulsaciones
    modeManager.update(pressCount);
    
    // Reiniciar contador de pulsaciones
    buttonManager.resetPressCount();
  }
  
  // Actualizar el modo actual (para animaciones continuas)
  modeManager.update(0); // 0 indica que no hay cambio de modo
  
  delay(MAIN_LOOP_DELAY);
}