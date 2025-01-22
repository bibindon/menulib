#include "MenuLib.h"

using namespace NSMenulib;

std::string ItemInfo::GetName() const
{
    return m_name;
}

void ItemInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

int ItemInfo::GetDurability() const
{
    return m_durability;
}

void ItemInfo::SetDurability(const int arg)
{
    m_durability = arg;
}

ISprite* ItemInfo::GetSprite() const
{
    return m_sprite;
}

void ItemInfo::SetSprite(ISprite * const arg)
{
    m_sprite = arg;
}

std::string ItemInfo::GetDetail() const
{
    return m_detail;
}

void ItemInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

int NSMenulib::ItemInfo::GetLevel() const
{
    return m_level;
}

void NSMenulib::ItemInfo::SetLevel(const int arg)
{
    m_level = arg;
}

int NSMenulib::ItemInfo::GetId() const
{
    return m_id;;
}

void NSMenulib::ItemInfo::SetId(const int arg)
{
    m_id = arg;
}

int NSMenulib::ItemInfo::GetSubId() const
{
    return m_subId;
}

void NSMenulib::ItemInfo::SetSubId(const int arg)
{
    m_subId = arg;
}

bool NSMenulib::ItemInfo::GetEquipEnable() const
{
    return m_equipEnable;
}

void NSMenulib::ItemInfo::SetEquipEnable(const bool arg)
{
    m_equipEnable = arg;
}

bool NSMenulib::ItemInfo::GetEquip() const
{
    return m_equip;
}

void NSMenulib::ItemInfo::SetEquip(const bool arg)
{
    m_equip = arg;
}

