#include "MenuLib.h"
#include <sstream>

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

void MenuLib::Init(
    const std::string& csvfilepath,
    IFont* font,
    ISoundEffect* SE,
    ISprite* sprCursor,
    ISprite* sprBackground,
    ISprite* sprPanel,
    ISprite* sprPanelLeft)
{
    m_font = font;
    m_SE = SE;
    m_sprCursor = sprCursor;
    m_sprBackground = sprBackground;
    m_sprPanel = sprPanel;
    m_sprPanelLeft = sprPanelLeft;

    m_TopBarName.push_back("アイテム");
    m_TopBarName.push_back("武器・防具");
    m_TopBarName.push_back("タスク");
    m_TopBarName.push_back("マップ");
    m_TopBarName.push_back("人物情報");
    m_TopBarName.push_back("敵情報");
    m_TopBarName.push_back("技・魔法");
    m_TopBarName.push_back("ステータス");
    m_TopBarName.push_back("タイトル");
    m_TopBarName.push_back("最初から");
}

void MenuLib::SetItem(const std::vector<ItemInfo>& items)
{
    m_itemInfoList = items;
}

std::string MenuLib::Up()
{
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex >= 7)
        {
            m_topBarIndex -= 7;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        if (m_itemCursorIndex >= 1)
        {
            m_itemCursorIndex--;
            m_SE->PlayMove();
        }
    }
     
    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Down()
{
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex <= 2)
        {
            m_topBarIndex += 7;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        if (m_itemCursorIndex <= (int)m_itemInfoList.size() - 2)
        {
            m_itemCursorIndex++;
            m_SE->PlayMove();
        }
    }
    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Right()
{
    if (m_topBarIndex <= 8)
    {
        m_topBarIndex++;
        m_SE->PlayMove();
    }
    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Left()
{
    if (1 <= m_topBarIndex)
    {
        m_topBarIndex--;
        m_SE->PlayMove();
    }
    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Into()
{
    m_SE->PlayClick();
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex == 0)
        {
            m_eFocus = eFocus::ITEM;
        }
    }
    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Back()
{
    if (m_eFocus == eFocus::ITEM)
    {
        m_eFocus = eFocus::TOP_BAR;
        m_SE->PlayBack();
    }
    return m_TopBarName.at(m_topBarIndex);
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
    const int PADDINGY = 8;

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

    const int LEFT_PANEL_PADDINGX = 50;
    const int LEFT_PANEL_PADDINGY = 13;
    const int LEFT_PANEL_HEIGHT = 60;

    if (m_topBarIndex == 0)
    {
        for (std::size_t i = 0; i < m_itemInfoList.size(); ++i)
        {
            if (i >= 10)
            {
                break;
            }
            m_sprPanelLeft->DrawImage(100, 200 + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                m_itemInfoList.at(i).GetName(),
                100 + LEFT_PANEL_PADDINGX,
                200 + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                std::to_string(m_itemInfoList.at(i).GetNum()),
                445 + LEFT_PANEL_PADDINGX,
                200 + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }

    // Show item detail

    if (m_eFocus == eFocus::ITEM)
    {
        m_itemInfoList.at(m_itemCursorIndex).GetSprite()->DrawImage(600, 300);

        std::string detail = m_itemInfoList.at(m_itemCursorIndex).GetDetail();
        std::vector<std::string> details = split(detail, '\n');

        for (std::size_t i = 0; i < details.size(); ++i)
        {
            m_font->DrawText_(
                details.at(i),
                1100,
                250 + i*40
                );
        }
    }

    // Show cursor
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex <= 6)
        {
            m_sprCursor->DrawImage(-30 + STARTX + PANEL_WIDTH * m_topBarIndex, STARTY);
        }
        else
        {
            m_sprCursor->DrawImage(-30 + STARTX + PANEL_WIDTH * (m_topBarIndex - 7), STARTY + PANEL_HEIGHT);
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        m_sprCursor->DrawImage(80, 205 + (m_itemCursorIndex * 60));
    }
}

