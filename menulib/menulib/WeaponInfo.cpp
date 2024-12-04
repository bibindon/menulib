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

int NSMenulib::WeaponInfo::GetLevel()
{
    return m_level;
}

void NSMenulib::WeaponInfo::SetLevel(const int arg)
{
    m_level = arg;
}

int NSMenulib::WeaponInfo::GetId()
{
    return m_id;
}

void NSMenulib::WeaponInfo::SetId(const int arg)
{
    m_id = arg;
}

int NSMenulib::WeaponInfo::GetSubId()
{
    return m_subId;
}

void NSMenulib::WeaponInfo::SetSubId(const int arg)
{
    m_subId = arg;
}

