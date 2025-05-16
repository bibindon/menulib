#include "MenuLib.h"

using namespace NSMenulib;

std::string NSMenulib::GuideInfo::GetCategory()
{
    return m_category;
}

void NSMenulib::GuideInfo::SetCategory(const std::string& arg)
{
    m_category = arg;
}

std::string NSMenulib::GuideInfo::GetSubCategory()
{
    return m_subCategory;
}

void NSMenulib::GuideInfo::SetSubCategory(const std::string& arg)
{
    m_subCategory = arg;
}

std::string GuideInfo::GetDetail()
{
    return m_detail;
}

void GuideInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

