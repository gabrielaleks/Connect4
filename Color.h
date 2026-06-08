#ifndef COLOR_H
#define COLOR_H

#include <QString>
#include <map>

enum Color {
    Red,
    Yellow,
    Green,
    Blue,
    Orange,
    Purple
};

static const std::map<Color, QString> colors = {
    {Red,    "Red"},
    {Yellow, "Yellow"},
    {Green,  "Green"},
    {Blue,   "Blue"},
    {Orange, "Orange"},
    {Purple, "Purple"}
};

#endif // COLOR_H
