#include "MenuLib.h"

using namespace NSMenulib;

std::wstring ItemInfo::GetId() const
{
    return m_id;
}

void ItemInfo::SetId(const std::wstring& arg)
{
    m_id = arg;
}

std::wstring ItemInfo::GetName() const
{
    return m_name;
}

void ItemInfo::SetName(const std::wstring& arg)
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
    if (m_sprite != nullptr)
    {
        delete m_sprite;
        m_sprite = nullptr;
    }

    m_sprite = arg;
}

std::wstring ItemInfo::GetDetail() const
{
    return m_detail;
}

void ItemInfo::SetDetail(const std::wstring& arg)
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

float NSMenulib::ItemInfo::GetWeight() const
{
    return m_weight;
}

void NSMenulib::ItemInfo::SetWeight(const float arg)
{
    m_weight = arg;
}

int NSMenulib::ItemInfo::GetVolume() const
{
    return m_volume;
}

void NSMenulib::ItemInfo::SetVolume(const int arg)
{
    m_volume = arg;
}

