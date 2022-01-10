

#include <InnovaS_Dactilar.h>

#include <SoftwareSerial.h>

// pin #2 - Entrada desde el Sensor  (cable verde)
// pin #3 - Salida de desde Arduino  (cable blanco)

SoftwareSerial MySerial(2, 3);

uint32_t ClaveSensorHuella = 0;
InnovaS_Dactilar MySensorDactilar = InnovaS_Dactilar(&MySerial, ClaveSensorHuella);

void setup()
{ 
    Serial.begin(9600);
    Serial.println("Sensor de Huella");
  
    //Setea la velocidad de comunicacion con el sensor de huella
    //Iniciar verificando los valores de 9600 y 57600
    MySensorDactilar.begin(9600);
    
    if (MySensorDactilar.VerificarClave()) {
      Serial.println("Sensor de Huella Encontrado :)  :) ");
    } else {
      Serial.println("No fue posible encontrar al sensor de Huella  :(  :( ");
      while (1);
    }

    byte TotalRegistrados = (byte)MySensorDactilar.ContarRegistrados();
    Serial.print("El sensor tiene "); Serial.print(TotalRegistrados); Serial.println(" usuarios registrados");

    EliminarBaseDatos();
}

void loop()                     
{ 
  delay(500);
}

void EliminarBaseDatos (void)
{
    uint8_t p = MySensorDactilar.VaciarBaseDatos();

    switch (p) {
    case SDACTILAR_BD_OK:
      Serial.println("Exito - Base de Datos Eliminada");
      break;
    case SDACTILAR_BD_PAQUETE_ERROR:
      Serial.print("Error al recibir el paquete");
      break;
    case SDACTILAR_BD_ERROR:
      Serial.print("Error al eliminar");
      break;
    default:
      Serial.print("Error Desconocido: 0x"); Serial.println(p, HEX);
      break;
    }
}
