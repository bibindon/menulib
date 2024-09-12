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

class ItemInfo
{
public:
    std::string GetName();
    void SetName(const std::string& arg);
    int GetNum();
    void SetNum(const int arg);
    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);
    std::string GetDetail();
    void SetDetail(const std::string& arg);
private:
    std::string m_name;
    int m_num;
    ISprite* m_sprite;
    std::string m_detail;
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

    void SetItem(const std::vector<ItemInfo>& items);
    std::string Up();
    std::string Down();
    std::string Right();
    std::string Left();
    std::string Into();
    std::string Back();
    void Click(const int x, const int y);
    void Draw();

private:
    enum class eFocus
    {
        TOP_BAR,
        ITEM,
        WEAPON,
        TASK,
        MAP,
        HUMAN,
        ENEMY,
        SKILL,
        STATUS,
        TITLE,
        OPENING,
    };

    ISprite* m_sprCursor;
    ISprite* m_sprBackground;
    ISprite* m_sprPanel;
    ISprite* m_sprPanelLeft;
    IFont* m_font;
    ISoundEffect* m_SE;
    eFocus m_eFocus = eFocus::TOP_BAR;
    int m_topBarIndex { 0 };
    int m_itemCursorIndex { 0 };
    std::vector<std::string> m_TopBarName;
    std::vector<ItemInfo> m_itemInfoList;
};

