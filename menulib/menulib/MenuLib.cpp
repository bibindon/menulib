#include "MenuLib.h"

void MenuLib::Init(
    const std::string& csvfilepath,
    IFont* font,
    ISprite* sprCursor,
    ISprite* sprBackground,
    ISprite* sprPanel)
{
    m_font = font;
    m_sprCursor = sprCursor;
    m_sprBackground = sprBackground;
    m_sprPanel = sprPanel;
}

std::string MenuLib::Up()
{
    if (m_topBarIndex >= 7)
    {
        m_topBarIndex -= 7;
    }
    return std::string();
}

std::string MenuLib::Down()
{
    if (m_topBarIndex <= 2)
    {
        m_topBarIndex += 7;
    }
    return std::string();
}

std::string MenuLib::Right()
{
    if (m_topBarIndex <= 8)
    {
        m_topBarIndex++;
    }
    return std::string();
}

std::string MenuLib::Left()
{
    if (1 <= m_topBarIndex)
    {
        m_topBarIndex--;
    }
    return std::string();
}

std::string MenuLib::Into()
{
    return std::string();
}

std::string MenuLib::Back()
{
    return std::string();
}


void MenuLib::Click(const int x, const int y)
{
    if (50 < y && y <= 200)
    {
        if (x < 300)
        {
            m_topBarIndex = 0;
        }
        else if (300 <= x && x < 600)
        {
            m_topBarIndex = 1;
        }
        else if (600 <= x && x < 900)
        {
            m_topBarIndex = 2;
        }
        else if (900 <= x && x < 1200)
        {
            m_topBarIndex = 3;
        }
    }
}

void MenuLib::Draw()
{
    m_sprBackground->DrawImage(0, 0);

    const int PADDINGX = 50;
    const int PADDINGY = 10;

    const int STARTX = 100;
    const int STARTY = 80;
    const int PANEL_WIDTH = 200;
    const int PANEL_HEIGHT = 50;



    for (int i = 0; i < 7; ++i)
    {
        m_sprPanel->DrawImage(STARTX + (PANEL_WIDTH * i), STARTY);
    }
    for (int i = 0; i < 7; ++i)
    {
        m_sprPanel->DrawImage(STARTX + (PANEL_WIDTH * i), STARTY + PANEL_HEIGHT);
    }

    m_font->DrawText_("アイテム", STARTX + (PANEL_WIDTH * 0) + PADDINGX, STARTY + PADDINGY);
    m_font->DrawText_("武器・防具", STARTX + (PANEL_WIDTH * 1) + PADDINGX, STARTY + PADDINGY);
    m_font->DrawText_("タスク", STARTX + (PANEL_WIDTH * 2) + PADDINGX, STARTY + PADDINGY);
    m_font->DrawText_("マップ", STARTX + (PANEL_WIDTH * 3) + PADDINGX, STARTY + PADDINGY);
    m_font->DrawText_("人物情報", STARTX + (PANEL_WIDTH * 4) + PADDINGX, STARTY + PADDINGY);
    m_font->DrawText_("敵情報", STARTX + (PANEL_WIDTH * 5) + PADDINGX, STARTY + PADDINGY);
    m_font->DrawText_("技・魔法", STARTX + (PANEL_WIDTH * 6) + PADDINGX, STARTY + PADDINGY);
    m_font->DrawText_("ステータス", STARTX + (PANEL_WIDTH * 0) + PADDINGX, STARTY + PANEL_HEIGHT + PADDINGY);
    m_font->DrawText_("タイトル", STARTX + (PANEL_WIDTH * 1) + PADDINGX, STARTY + PANEL_HEIGHT + PADDINGY);
    m_font->DrawText_("最初から", STARTX + (PANEL_WIDTH * 2) + PADDINGX, STARTY + PANEL_HEIGHT + PADDINGY);

    if (m_topBarIndex <= 6)
    {
        m_sprCursor->DrawImage(-30 + STARTX+ PANEL_WIDTH*m_topBarIndex, STARTY);
    }
    else
    {
        m_sprCursor->DrawImage(-30 + STARTX+ PANEL_WIDTH*(m_topBarIndex-7), STARTY+PANEL_HEIGHT);
    }
}
