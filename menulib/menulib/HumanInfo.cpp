#include "MenuLib.h"

using namespace NSMenulib;

std::string HumanInfo::GetName()
{
    return m_name;
}

void HumanInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

ISprite* HumanInfo::GetSprite()
{
    return m_sprite;
}

void HumanInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::string HumanInfo::GetDetail()
{
    return m_detail;
}

void HumanInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

