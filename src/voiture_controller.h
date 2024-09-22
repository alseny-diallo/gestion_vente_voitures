#ifndef VOITURE_CONTROLLER_H
#define VOITURE_CONTROLLER_H

#include "database.h"
#include "crow.h"

crow::response getAllVoitures();
crow::response getVoitureById(int id);

#endif 
