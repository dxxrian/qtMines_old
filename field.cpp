#include "field.h"
#include <stdlib.h>
#include <random>
#include <QDebug>

Field::Field()
{}

Field::Field(int i_width, int i_height, int i_diff)
{
    qDebug() << "Starting new Game";
    height = i_height;
    width = i_width;
    diff = i_diff;
    size = width * height; //total amount of tiles
    //data = new a
    //data = static_cast<int*>( malloc( sizeof(int) * size ) );  //data array. top left to bottom right.
    mines = calculateMines(size, diff);
    qDebug().nospace() << "with params: width=" << width << " height=" << height << " size=" << size << " difficulty=" << diff << " mines=" << mines;
}

Field::~Field(){
    //data.clear();
}

int Field::getWidth(){
    return width;
}

int Field::getHeight(){
    return height;
}

int Field::getMines(){
    return mines;
}

int Field::getSize(){
    return size;
}

int Field::calculateMines(int size, int diff){
    return ( size / 30 ) * diff;
};

int Field::generateField(){

    data.resize(size);  //fills data with zeros

    std::random_device rdev;
    std::mt19937 rng(rdev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,getSize()-1);

    //generate Mines: -1 in data arr
    int potential_mine;
    bool success = false;
    for(int mine = 0; mine < getMines(); mine++){
        success = false;
        int trycount = 0;
        while(success == false){
            potential_mine = dist(rng);
            if(data.at(potential_mine) != -1){
                data.at(potential_mine) = -1;
                success = true;
                //Generate Mine-nearby numbers
                if(potential_mine % width < width-1){ //right
                    if(data.at(potential_mine + 1) != -1){
                        data.at(potential_mine + 1)++;
                    } else {}
                } else {}
                if(potential_mine % width != 0){ //left
                    if(data.at(potential_mine - 1) != -1){
                        data.at(potential_mine - 1)++;
                    } else {}
                } else {}
                if(potential_mine >= width){ //up
                    if(data.at(potential_mine - width) != -1){
                        data.at(potential_mine - width)++;
                    } else {}
                } else {}
                if(potential_mine < ((height - 1) * width)){ //down
                    if(data.at(potential_mine + width) != -1){
                        data.at(potential_mine + width)++;
                    } else {}
                } else {}
                if((potential_mine % width < width-1) && (potential_mine >= width)){ //up-right
                    if(data.at(potential_mine - width + 1) != -1){
                        data.at(potential_mine - width + 1)++;
                    } else {}
                } else {}
                if((potential_mine % width != 0) && (potential_mine >= width)){ //up-left
                    if(data.at(potential_mine - width - 1) != -1){
                        data.at(potential_mine - width - 1)++;
                    } else {}
                } else {}
                if((potential_mine % width < width-1) && (potential_mine < ((height - 1) * width))){ //down-right
                    if(data.at(potential_mine + width + 1) != -1){
                        data.at(potential_mine + width + 1)++;
                    } else {}
                } else {}
                if((potential_mine % width != 0) && (potential_mine < ((height - 1) * width))){ //down-left
                    if(data.at(potential_mine + width - 1) != -1){
                        data.at(potential_mine + width - 1)++;
                    } else {}
                } else {}

            }else{
                if(trycount > getSize() * 10){
                    return -1; //failure
                }else{}
            }
            trycount++;
        }
    }

    return 0; //success
};

void Field::simpledraw(){
    QDebug deb = qDebug();
    for(int i=0; i<getSize(); i++){
        deb << data.at(i);
        if(i%width==height){
            deb << "\n";
        }
    }
}
