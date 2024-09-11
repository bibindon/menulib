#include "MenuLib.h"

void MenuLib::Init(const std::string& csvfilepath, std::vector<ISprite*> sprite, IText* text)
{
    m_sprite = sprite;
    m_text = text;
}

void MenuLib::Next()
{
    m_topIndex++;
    if (3 <= m_topIndex)
    {
        m_topIndex = 3;
    }
}

void MenuLib::Previous()
{
    m_topIndex--;
    if ( m_topIndex <= 0)
    {
        m_topIndex = 0;
    }
}

void MenuLib::Into()
{
}

void MenuLib::Back()
{
}

void MenuLib::Click(const int x, const int y)
{
    if (50 < y && y <= 200)
    {
        if (x < 300)
        {
            m_topIndex = 0;
        }
        else if (300 <= x && x < 600)
        {
            m_topIndex = 1;
        }
        else if (600 <= x && x < 900)
        {
            m_topIndex = 2;
        }
        else if (900 <= x && x < 1200)
        {
            m_topIndex = 3;
        }
    }
}

void MenuLib::Draw()
{
    m_sprite.at(1)->DrawImage(0, 0);
    m_sprite.at(2)->DrawImage(100, 90);
    m_sprite.at(2)->DrawImage(400, 90);
    m_sprite.at(2)->DrawImage(700, 90);
    m_sprite.at(2)->DrawImage(1000, 90);

    m_text->DrawText_("aaa", 200, 100);
    m_text->DrawText_("bbb", 500, 100);
    m_text->DrawText_("ccc", 800, 100);
    m_text->DrawText_("ddd", 1100, 100);

    m_sprite.at(0)->DrawImage(300*m_topIndex, 90);
}
