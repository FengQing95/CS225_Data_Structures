#pragma once
#include "Queen.h"
#include "Piece.h"
#include <string>

class Queen: public Piece {
public:
    std::string getType();
};
