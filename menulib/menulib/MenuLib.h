#pragma once
#include <string>
#include <vector>

class ISprite
{
public:
    virtual void DrawImage(const int x, const int y, const int transparency = 255) = 0;
    virtual void Load(const std::string& filepath) = 0;
    virtual ~ISprite() {};
};

class IText
{
public:
    virtual void DrawText_(const std::string& msg, const int x, const int y) = 0;
    virtual void Init() = 0;
    virtual ~IText() {};
};

class MenuLib
{
public:

    void Init(const std::string& csvfilepath, std::vector<ISprite*> sprite, IText* text);
    void Next();
    void Previous();
    void Into();
    void Back();
    void Click(const int x, const int y);
    void Draw();

private:

    std::vector<ISprite*> m_sprite;
    IText* m_text;
    int m_topIndex { 0 };
};

