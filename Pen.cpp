#include "Pen.h"

Pen::Pen(int size, Block::BlockID type, Drawboard *board) {
    this->board = board;
    this->size = size;
    this->type = type;
}

void Pen::setSize(int x) {
    this->size = x;
}

void Pen::setType(Block::BlockID x) {
    this->type = x;
}


void Pen::Draw(int x, int y) {
    int rows = this->board->rows;
    int cols = this->board->cols;

    for (int i = x - this->size; i <= x + this->size; i++) {
        for (int j = y - this->size; j <= y + this->size; j++) {
            if (i < 0 || j < 0 || i >= rows || j >= cols) {continue;}

            std::shared_ptr<Element> ptr = BlockCreator::CreateElement(i, j, this->type, this->board);
            this->board->setElement(i, j, ptr);
        }
    } 
}