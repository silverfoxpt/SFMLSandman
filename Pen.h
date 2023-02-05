#ifndef H_PEN
#define H_PEN

#include "Drawboard.h"

class Pen {
    public:
        int size;
        int type;

        Pen(int size, int type, Drawboard *board);

        void setSize(int x);
        void setType(int x);

        void Draw(int posX, int posY);

    private:
        Drawboard *board;
};

#endif