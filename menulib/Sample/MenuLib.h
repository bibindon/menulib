#pragma once
#include <string>

class ISprite
{
public:
    virtual void DrawImage(const int x, const int y, const int transparency = 255) = 0;
    virtual void DrawText_(const std::string& msg) = 0;
    virtual void Load(const std::string& filepath) = 0;
    virtual ~ISprite() {};
};

class MenuLib
{
public:

    void Init(const std::string& csvfilepath, ISprite* sprite[10]);
    void Step();
    void Draw();

private:

    ISprite* m_sprite[10];
    int m_i { 0 };
};

