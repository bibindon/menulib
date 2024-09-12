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

class IFont
{
public:
    virtual void DrawText_(const std::string& msg, const int x, const int y) = 0;
    virtual void Init() = 0;
    virtual ~IFont() {};
};

class ISoundEffect
{
public:
    virtual void PlaySE(const std::string& msg) = 0;
    virtual void Init() = 0;
    virtual ~ISoundEffect() {};
};

class MenuLib
{
public:

    void Init(
        const std::string& csvfilepath,
        IFont* font,
        ISprite* sprCursor,
        ISprite* sprBackground,
        ISprite* sprPanel
        );
    std::string Up();
    std::string Down();
    std::string Right();
    std::string Left();
    std::string Into();
    std::string Back();
    void Click(const int x, const int y);
    void Draw();

private:

    ISprite* m_sprCursor;
    ISprite* m_sprBackground;
    ISprite* m_sprPanel;
    IFont* m_font;
    int m_topBarIndex { 0 };
};

