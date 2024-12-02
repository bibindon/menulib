#include "MenuLib.h"

using namespace NSMenulib;

std::string WeaponInfo::GetName()
{
    return m_name;
}

void WeaponInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

ISprite* WeaponInfo::GetSprite()
{
    return m_sprite;
}

void WeaponInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::string WeaponInfo::GetDetail()
{
    return m_detail;
}

void WeaponInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

int WeaponInfo::GetDurability()
{
    return m_durability;
}

void WeaponInfo::SetDurability(const int arg)
{
    m_durability = arg;
}

