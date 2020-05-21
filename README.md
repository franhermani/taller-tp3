# Nombre: Francisco Hermani

# Padrón: 98223

Link GitHub: https://github.com/franhermani/taller-tp3

# Resolución del TP

1. Reutilización del TDA Socket implementado en el TP1. Esto implicó
   una transformación del código C a C++, y de struct a Class.
   Tuve que hacer ciertas modificaciones. Por ejemplo, la función accept
   ahora crea el socket internamente y lo devuelve (antes lo recibía y
   le seteaba el sd). A su vez, apliqué RAII en el destructor del socket

2. Definición de las constantes en los defines.h

3. Resolución de la lógica del juego en un único ejecutable

4. Agregado de excepciones en la lógica del juego

5. Creación de la clase File para aplicar RAII con archivos

6. Validación de comandos del lado del cliente

7. Creación de la clase SocketError y uso de ella en la clase Socket


# Puntos de interés

# Aclaraciones

- El servidor lee el archivo de números completo y lo valida antes de
  comenzar a escuchar por conexiones entrantes de clientes