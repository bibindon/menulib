#include "MenuLib.h"

using namespace NSMenulib;

std::string StatusInfo::GetName()
{
    return m_name;
}

void StatusInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

ISprite* StatusInfo::GetSprite()
{
    return m_sprite;
}

void StatusInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::string StatusInfo::GetDetail()
{
    return m_detail;
}

void StatusInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

