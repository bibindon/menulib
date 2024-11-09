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

int ItemInfo::GetNum()
{
    return m_num;
}

void ItemInfo::SetNum(const int arg)
{
    m_num = arg;
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

