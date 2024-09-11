#include "MenuLib.h"

void MenuLib::Init(const std::string& csvfilepath, ISprite* sprite[10])
{
    for (int i = 0; i < 10; ++i)
    {
        m_sprite[i] = sprite[i];
    }
}

void MenuLib::Step()
{
    m_i++;
}

void MenuLib::Draw()
{
    m_sprite[m_i]->DrawImage(0, 0);
}
