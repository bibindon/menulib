#include "MenuLib.h"

std::string EnemyInfo::GetName()
{
    return m_name;
}

void EnemyInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

ISprite* EnemyInfo::GetSprite()
{
    return m_sprite;
}

void EnemyInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::string EnemyInfo::GetDetail()
{
    return m_detail;
}

void EnemyInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

