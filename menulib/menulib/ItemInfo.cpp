#include "MenuLib.h"

using namespace NSMenulib;

std::string ItemInfo::GetName()
{
    return m_name;
}

void ItemInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

int ItemInfo::GetDurability()
{
    return m_durability;
}

void ItemInfo::SetDurability(const int arg)
{
    m_durability = arg;
}

ISprite* ItemInfo::GetSprite()
{
    return m_sprite;
}

void ItemInfo::SetSprite(ISprite * const arg)
{
    m_sprite = arg;
}

std::string ItemInfo::GetDetail()
{
    return m_detail;
}

void ItemInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

