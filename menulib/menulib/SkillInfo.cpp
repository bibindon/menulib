#include "MenuLib.h"

using namespace NSMenulib;

std::string SkillInfo::GetName()
{
    return m_name;
}

void SkillInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

ISprite* SkillInfo::GetSprite()
{
    return m_sprite;
}

void SkillInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::string SkillInfo::GetDetail()
{
    return m_detail;
}

void SkillInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

