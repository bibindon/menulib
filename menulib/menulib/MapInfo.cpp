#include "MenuLib.h"

using namespace NSMenulib;

std::wstring MapInfo::GetId()
{
    return m_id;
}

void MapInfo::SetId(const std::wstring& arg)
{
    m_id = arg;
}

std::wstring MapInfo::GetName()
{
    return m_name;
}

void MapInfo::SetName(const std::wstring& arg)
{
    m_name = arg;
}

ISprite* MapInfo::GetSprite()
{
    return m_sprite;
}

void MapInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::wstring MapInfo::GetDetail()
{
    return m_detail;
}

void MapInfo::SetDetail(const std::wstring& arg)
{
    m_detail = arg;
}

