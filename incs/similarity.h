#ifndef SIMILARITY
#define SIMILARITY

#include "libs.h"
#include "tokenizer.h"

// Calcula la similitud entre dos listas de tokens
// Parámetros:
// - a: primera lista de tokens
// - b: segunda lista de tokens
// Retorna un valor flotante que representa el grado de similitud
float calculate_similarity(TokenList a, TokenList b);

#endif
//*