To Do:

Las imágenes del sprite no se cargan en orden, sino como las da readdir()

El punto rojo del jugador no se mueve

Al salir da segmentation fault

Se clava un poco en los muros

El color del mapa no es el que debería. Yo estoy convencido de que la MLX no maneja siempre bien la endianness, pero tampoco es tan importante. Lo vemos un rato, pero se puede quedar así.

Habría que duplicar el proyecto y hacer uno normal y otro bonus, ¿no? (no vale clonarlos, e que no tiene bonus no puede tener muchas funciones que utilizamos para el bonus).


In Progress:



	Definir la funcion de parseo teniendo en cuenta el bonus
	

Done:

	Definir la funcion de inicio para la ventana y los datos de inicio

	* 	OK: Parsear las texturas para cada orientacion  
	
	*	OK: movimiento con teclas: asdw y flechas.

	* 	OK: Parsear el mapa viendo los posibles errores (mapa no cerrado, simbolos no reconocidos)

	OK: Implementar eventos de ratón (PERO se "clava" en los muros y se queda pillado) <<<<< ******** !!!!
		Eventos del ratón:
		 * botón izq y arrastrar: te mueves al arrastrar el ratón
		 * botón der: te deslizas hacia el ratón, aunque no lo arrastres.

	OK: implementar minimap

	OK: Añadida una sombra en los bordes horizontales de los muros.

To be Checked:


Closed:


./text_north 