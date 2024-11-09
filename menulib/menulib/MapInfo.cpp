#include "MenuLib.h"

using namespace NSMenulib;

std::string MapInfo::GetName()
{
    return m_name;
}

void MapInfo::SetName(const std::string& arg)
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

std::string MapInfo::GetDetail()
{
    return m_detail;
}

void MapInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

