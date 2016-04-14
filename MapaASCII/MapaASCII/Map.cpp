#include "Map.h"

const Tile Tile::defaults[256] = {
	{ TILE_SHAPE_POLYGON,	'm', "manzana",				"Elemento básico en la definición de un mapa de ciudad, permite ubicar edificaciones, parques y árboles en el mapa."},
	{ TILE_SHAPE_POLYGON,	'b', "boulevard",			"Se encuentra en distintas calles como divisor entre carriles pudiendo contener"},
	{ TILE_SHAPE_POLYGON,	'e', "edificio-privado",	"Contempla una estructura edilicia privada o pública. No se posee información sobre los interiores de la edificación sino sobre los límites inscriptos en el catastro local.Los edificios públicos tienen una particularidad : poseen nombre que debe ser impreso al usuario a modo de leyenda para su ubicación."},
	{ TILE_SHAPE_POLYGON,	'A', "edificio-­publico",	"Contempla una estructura edilicia privada o pública. No se posee información sobre los interiores de la edificación sino sobre los límites inscriptos en el catastro local.Los edificios públicos tienen una particularidad : poseen nombre que debe ser impreso al usuario a modo de leyenda para su ubicación."},
	{ TILE_SHAPE_CIRCLE,	'@', "arbol",				"Representa distintos elementos de vegetación que se pueden encontrar en las manzanas o boulevares."},
	{ TILE_SHAPE_CIRCLE ,	'#', "semaforo",			"Descripción: Se trata de los señalizadores de tránsito que se pueden encontrar tanto en manzanas como en boulevares o colgantes en las calles."},
	{ TILE_SHAPE_POLYGON,	'-', "agua",				"Representa mares, ríos, arroyos, lagunas o cualquier afluente que merezca ser tratado por los mapas en desarrollo.No puede coexistir en una misma ubicación con ningún otro tipo de elemento."},
	{ TILE_SHAPE_NONE,		' ', "No definido",			"Se asume que es el elemento base para definir un mapa. No es necesario indicarlo en la estructura de objetos de una ciudad sino que se asumirá que todo punto del mapa que no tuviera algún elemento posicionado se trata de una calle.No será necesario agregar nombres a las calles ni ningún caracter particular ya que se imprimirán como espacios."},
};
