#include "Drawboard.h"

Drawboard::Drawboard() {
    for (int i = 0; i < this->rows; i++) {
        this->modBox.push_back(std::vector<std::shared_ptr<Element>>());
        for (int j = 0; j < this->cols; j++) {
            this->modBox[i].push_back(nullptr);
        }
    }
}

std::shared_ptr<Element> Drawboard::getElement(int x, int y) {
    if (x < 0 || y < 0 || x >= this->rows || y >= this->cols) {return nullptr;}

    return this->modBox[x][y];   
}

void Drawboard::setElement(int x, int y, std::shared_ptr<Element> sh) {
    if (x < 0 || y < 0 || x >= this->rows || y >= this->cols) {return;}

    this->modBox[x][y] = sh;
}

void Drawboard::Test() {
    srand (static_cast <unsigned> (time(0)));

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(100, 200);
    std::uniform_int_distribution<std::mt19937::result_type> dist7(220, 255);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j % 8 == 0 || j % 8 == 3 || j % 8 == 2 || j % 8 == 1) {
                //rand
                this->pixels[i][j*4]    = dist6(rng);
                this->pixels[i][j*4+1]  = dist6(rng);
                this->pixels[i][j*4+2]  = dist6(rng);
            } else {
                //rand
                this->pixels[i][j*4]    = dist7(rng);
                this->pixels[i][j*4+1]  = dist7(rng);
                this->pixels[i][j*4+2]  = dist7(rng);
            }

            this->pixels[i][j*4+3] = 255;
        }
    }
}

void Drawboard::Convert2DPointerTo2DArray() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            auto inf = this->getElement(i, j).get(); 
            if (inf == nullptr) {
                this->pixels[i][j*4]        = 0;
                this->pixels[i][j*4+1]      = 0;
                this->pixels[i][j*4+2]      = 0;
                this->pixels[i][j*4+3]      = 0;
                continue;
            }
            this->pixels[i][j*4]        = inf->color.r;
            this->pixels[i][j*4+1]      = inf->color.g;
            this->pixels[i][j*4+2]      = inf->color.b;
            this->pixels[i][j*4+3]      = inf->color.a;
        }
    }
}

void Drawboard::Convert2DArrayTo1DArray() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int x = cols * 4 * i + j * 4;
            this->apply[x]      = this->pixels[i][j*4];
            this->apply[x+1]    = this->pixels[i][j*4+1];
            this->apply[x+2]    = this->pixels[i][j*4+2];
            this->apply[x+3]    = this->pixels[i][j*4+3];
        }
    }
}

sf::Sprite Drawboard::ConvertToSprite() {
    sf::Image img; img.create(this->cols, this->rows, this->apply);
    this->tmpTex.loadFromImage(img);
    sf::Sprite spr; spr.setTexture(this->tmpTex);
    
    return spr;
}

bool Drawboard::isLastRow(int x) {
    return x == this->rows-1;
}

bool Drawboard::isFirstRow(int x) {
    return x == 0;
}

bool Drawboard::isLastCol(int y) {
    return y == this->cols-1;
}

bool Drawboard::isFirstCol(int y) {
    return y == 0;
}

void Drawboard::StepAll() {
    for (int i = this->rows - 1; i >= 0; i--) {
        //int j = 0; j < this->cols; j++
        if (i%2==0) {
            for (int j = this->cols - 1; j >= 0; j--) {
                std::shared_ptr<Element> ptr = this->getElement(i, j);
                if (ptr == nullptr) { continue;}
                
                ptr.get()->step();
            }
        } else {
            for (int j = 0; j < this->cols; j++) {
                std::shared_ptr<Element> ptr = this->getElement(i, j);
                if (ptr == nullptr) { continue;}
                
                ptr.get()->step();
            }
        }
    }
}

void Drawboard::Swap(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {return;}
    std::shared_ptr<Element> first  = getElement(x1, y1);
    std::shared_ptr<Element> sec    = getElement(x2, y2);

    //swap info
    if (first != nullptr) {
        Element* tmp = first.get();
        tmp->x = x2;
        tmp->y = y2;
    }
    if (sec != nullptr) {
        Element* tmp = sec.get();
        tmp->x = x1;
        tmp->y = y1;
    }

    //swap stuff
    setElement(x1, y1, sec);
    setElement(x2, y2, first);
}

void Drawboard::Override(int x1, int y1, sf::Vector2i overrideCoords) {
    if (x1 == overrideCoords.x && y1 == overrideCoords.y) {return;}

    std::shared_ptr<Element> first  = getElement(x1, y1);
    if (first != nullptr) {
        Element* tmp = first.get();
        tmp->x = overrideCoords.x;
        tmp->y = overrideCoords.y;
    }

    this->setElement(overrideCoords.x, overrideCoords.y, first); //override anything in overrideCoords coords
    this->setElement(x1, y1, nullptr); //clear original coords
}

sf::Vector2i Drawboard::convertPhysicToMatrix(int physX, int physY) {
    if (physX < 1 || physY < 1 || physX > this->cols || physY > this->rows) {
        return sf::Vector2i(-9999, -9999); //default
    }
    return sf::Vector2i(this->rows - physY, physX - 1);
}

void Drawboard::SwapPhysic(int physX1, int physY1, int physX2, int physY2) {
    if (physX1 == physX2 && physY1 == physY2) {return;}

    sf::Vector2i firstCoord     = this->convertPhysicToMatrix(physX1, physY1);
    sf::Vector2i secCoord       = this->convertPhysicToMatrix(physX2, physY2);
    if (firstCoord.x == -9999 || secCoord.x == -9999) {
        //std::cout << "Matrix coordinates not found. Warning - SwapPhysic : ";
        return;
    }

    this->Swap(firstCoord.x, firstCoord.y, secCoord.x, secCoord.y);
}

void Drawboard::OverridePhysic(int physX1, int physY1, int physX2, int physY2) {
    if (physX1 == physX2 && physY1 == physY2) {return;}
    
    sf::Vector2i firstCoord     = this->convertPhysicToMatrix(physX1, physY1);
    sf::Vector2i secCoord       = this->convertPhysicToMatrix(physX2, physY2);
    if (firstCoord.x == -9999 || secCoord.x == -9999) {
        //std::cout << "Matrix coordinates not found. Warning - OverridePhysic\n";
        return;
    }

    this->Override(firstCoord.x, firstCoord.y, sf::Vector2i(secCoord.x, secCoord.y));
}

std::shared_ptr<Element> Drawboard::GetByPhysic(int physX1, int physY1) {
    sf::Vector2i coords = this->convertPhysicToMatrix(physX1, physY1);
    if (coords.x == -9999) {
        //std::cout << "Matrix coordinates not found. Warning - GetByPhysic\n";
        return nullptr;
    }

    return this->getElement(coords.x, coords.y);
}

void Drawboard::SwapPhysicTriple(int physX1, int physY1, int physX2, int physY2, int physX3, int physY3) {
    //coord1 to coord 2, coord 2 to coord 3, coord 3 to coord 1
    this->SwapPhysic(physX1, physY1, physX2, physY2);
    this->SwapPhysic(physX1, physY1, physX3, physY3);
}

bool Drawboard::isPhysicBlockAir(int physX, int physY) {
    sf::Vector2i coords = this->convertPhysicToMatrix(physX, physY);
    if (coords.x == -9999) { //out of bounds
        return false;
    }

    //if it's 1. inbound and 2. is nullptr then it's an empty cell!
    return (this->GetByPhysic(physX, physY) == nullptr); 
}

bool Drawboard::isPhysicBlockWithinBound(int physX, int physY) {
    sf::Vector2i coords = this->convertPhysicToMatrix(physX, physY);
    if (coords.x == -9999) { //out of bounds
        return false;
    }

    return true;
}