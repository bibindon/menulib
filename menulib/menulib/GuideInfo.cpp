#include "MenuLib.h"

using namespace NSMenulib;

std::wstring NSMenulib::GuideInfo::GetId()
{
    return m_id;
}

void NSMenulib::GuideInfo::SetId(const std::wstring& arg)
{
    m_id = arg;
}

std::wstring NSMenulib::GuideInfo::GetCategory()
{
    return m_category;
}

void NSMenulib::GuideInfo::SetCategory(const std::wstring& arg)
{
    m_category = arg;
}

std::wstring NSMenulib::GuideInfo::GetSubCategory()
{
    return m_subCategory;
}

void NSMenulib::GuideInfo::SetSubCategory(const std::wstring& arg)
{
    m_subCategory = arg;
}

std::wstring GuideInfo::GetDetail()
{
    return m_detail;
}

void GuideInfo::SetDetail(const std::wstring& arg)
{
    m_detail = arg;
}

