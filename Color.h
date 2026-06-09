#ifndef COLOR_H
#define COLOR_H

#include <QString>
#include <QColor>
#include <map>

enum Color {
    Red,
    Yellow,
    Green,
    Blue,
    Orange,
    Purple,
    White
};

static const std::map<Color, QString> colors = {
    {Red,    "Red"},
    {Yellow, "Yellow"},
    {Green,  "Green"},
    {Blue,   "Blue"},
    {Orange, "Orange"},
    {Purple, "Purple"},
};

static const std::map<Color, QColor> colorValues = {
    {Red,    QColor(252, 35, 23)},
    {Yellow, QColor(255, 255, 38)},
    {Green, QColor(60, 230, 14)},
    {Blue, QColor(45, 83, 247)},
    {Orange, QColor(255, 161, 66)},
    {Purple, QColor(153, 45, 247)},
    {White, QColor(255, 255, 255)}
};

#endif // COLOR_H
