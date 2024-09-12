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
    virtual void PlayMove() = 0;
    virtual void PlayClick() = 0;
    virtual void PlayBack() = 0;
    virtual void Init() = 0;
    virtual ~ISoundEffect() {};
};

class MenuLib
{
public:

    void Init(
        const std::string& csvfilepath,
        IFont* font,
        ISoundEffect* SE,
        ISprite* sprCursor,
        ISprite* sprBackground,
        ISprite* sprPanel,
        ISprite* sprPanelLeft
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

    const int PADDINGX = 50;
    const int PADDINGY = 10;

    const int STARTX = 100;
    const int STARTY = 80;
    const int PANEL_WIDTH = 200;
    const int PANEL_HEIGHT = 50;

    ISprite* m_sprCursor;
    ISprite* m_sprBackground;
    ISprite* m_sprPanel;
    ISprite* m_sprPanelLeft;
    IFont* m_font;
    ISoundEffect* m_SE;
    int m_topBarIndex { 0 };
};

