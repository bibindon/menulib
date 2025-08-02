#pragma once
#include <string>
#include <list>
#include <vector>
#include <map>

namespace NSMenulib
{
class ISprite
{
public:
    virtual void DrawImage(const int x, const int y, const int transparency = 255) = 0;
    virtual void Load(const std::wstring& filepath) = 0;
    virtual ~ISprite() {};
};

class IFont
{
public:
    virtual void DrawText_(const std::wstring& msg, const int x, const int y, const bool hcenter = false, const int transparency = 255) = 0;
    virtual void Init(const bool bEnglish) = 0;
    virtual ~IFont() {};
};

class ISoundEffect
{
public:
    virtual void PlayMove() = 0;
    virtual void PlayClick() = 0;
    virtual void PlayBack() = 0;
    virtual void Init() = 0;
    virtual ~ISoundEffect() {};
};

class ItemInfo
{
public:
    std::wstring GetId() const;
    void SetId(const std::wstring& arg);

    int GetSubId() const;
    void SetSubId(const int arg);

    std::wstring GetName() const;
    void SetName(const std::wstring& arg);

    int GetDurability() const;
    void SetDurability(const int arg);

    ISprite* GetSprite() const;
    void SetSprite(ISprite* const arg);

    std::wstring GetDetail() const;
    void SetDetail(const std::wstring& arg);

    int GetLevel() const;
    void SetLevel(const int arg);

    bool GetEquipEnable() const;
    void SetEquipEnable(const bool arg);

    bool GetEquip() const;
    void SetEquip(const bool arg);

    float GetWeight() const;
    void SetWeight(const float arg);

    int GetVolume() const;
    void SetVolume(const int arg);

private:

    std::wstring m_name;
    int m_durability = 0;
    ISprite* m_sprite = nullptr;
    std::wstring m_detail;
    int m_level = 0;

    // 画面表示に使用されない。
    // 耐久値が100の斧と、50の斧と50の斧を所持してインベントリに表示できる。
    // 耐久値50の斧を選択したときどちらを選択したのかわからないので
    // ID、SubIDを持つことができるようにする。IDは種別、SubIDは個別の番号
    std::wstring m_id;
    int m_subId = 0;

    bool m_equipEnable = false;
    bool m_equip = false;

    float m_weight = 0.f;
    int m_volume = 0;
};

class HumanInfo
{
public:

    std::wstring GetId();
    void SetId(const std::wstring& arg);

    std::wstring GetName();
    void SetName(const std::wstring& arg);

    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);

    std::wstring GetDetail();
    void SetDetail(const std::wstring& arg);

private:

    std::wstring m_id;
    std::wstring m_name;
    ISprite* m_sprite = nullptr;
    std::wstring m_detail;
};

class EnemyInfo
{
public:

    std::wstring GetId();
    void SetId(const std::wstring& arg);

    std::wstring GetName();
    void SetName(const std::wstring& arg);

    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);

    std::wstring GetDetail();
    void SetDetail(const std::wstring& arg);

private:

    std::wstring m_id;
    std::wstring m_name;
    ISprite* m_sprite = nullptr;
    std::wstring m_detail;
};

class SkillInfo
{
public:

    std::wstring GetId();
    void SetId(const std::wstring& arg);

    std::wstring GetName();
    void SetName(const std::wstring& arg);

    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);

    std::wstring GetDetail();
    void SetDetail(const std::wstring& arg);

private:

    std::wstring m_id;
    std::wstring m_name;
    ISprite* m_sprite = nullptr;
    std::wstring m_detail;
};

class StatusInfo
{
public:

    std::wstring GetId();
    void SetId(const std::wstring& arg);

    std::wstring GetName();
    void SetName(const std::wstring& arg);

    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);

    std::wstring GetDetail();
    void SetDetail(const std::wstring& arg);

private:

    std::wstring m_id;
    std::wstring m_name;
    ISprite* m_sprite = nullptr;
    std::wstring m_detail;
};

class MapInfo
{
public:

    std::wstring GetId();
    void SetId(const std::wstring& arg);

    std::wstring GetName();
    void SetName(const std::wstring& arg);

    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);

    std::wstring GetDetail();
    void SetDetail(const std::wstring& arg);

private:

    std::wstring m_id;
    std::wstring m_name;
    ISprite* m_sprite = nullptr;
    std::wstring m_detail;
};

class WeaponInfo
{
public:

    std::wstring GetId();
    void SetId(const std::wstring& arg);

    int GetSubId();
    void SetSubId(const int arg);

    std::wstring GetName();
    void SetName(const std::wstring& arg);

    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);

    std::wstring GetDetail();
    void SetDetail(const std::wstring& arg);

    int GetDurability();
    void SetDurability(const int arg);

    int GetLevel();
    void SetLevel(const int arg);

private:

    std::wstring m_name;
    ISprite* m_sprite = nullptr;
    std::wstring m_detail;
    int m_durability = 0;
    int m_level = 0;

    // 画面表示に使用されない。
    // 耐久値が100の斧と、50の斧と50の斧を所持してインベントリに表示できる。
    // 耐久値50の斧を選択したときどちらを選択したのかわからないので
    // ID、SubIDを持つことができるようにする。IDは種別、SubIDは個別の番号
    std::wstring m_id;
    int m_subId = 0;

};

class GuideInfo
{
public:

    std::wstring GetId();
    void SetId(const std::wstring& arg);

    std::wstring GetCategory();
    void SetCategory(const std::wstring& arg);

    std::wstring GetSubCategory();
    void SetSubCategory(const std::wstring& arg);

    std::wstring GetDetail();
    void SetDetail(const std::wstring& arg);

private:

    std::wstring m_id;
    std::wstring m_category;
    std::wstring m_subCategory;
    std::wstring m_detail;
};

class MenuLib
{
public:

    void Init(const std::wstring& csvfilepath,
              IFont* font,
              IFont* fontStatus,
              ISoundEffect* SE,
              ISprite* sprCursor, 
              ISprite* sprBackground,
              const bool bEnglish);

    void Finalize();

    void SetItem(const std::vector<ItemInfo>& items);
    void SetHuman(const std::vector<HumanInfo>& items);
    void SetEnemy(const std::vector<EnemyInfo>& items);
    void SetMap(const std::vector<MapInfo>& items);
    void SetSkill(const std::vector<SkillInfo>& items);
    void SetStatus(const std::vector<StatusInfo>& items);
    void SetGuide(const std::vector<GuideInfo>& items);
    void SetWeapon(const std::vector<WeaponInfo>& items);
    void Up();
    void Down();
    void Right();
    void Left();
    std::wstring Into();
    std::wstring Back();
    void Next();
    void Previous();
    void CursorOn(const int x, const int y);
    std::wstring Click(const int x, const int y);

    // 右クリックはキャンセル操作
    void RightClick();

    void Draw();
    
    // アイテム情報を後から変えたいとき
    void AddItem(const ItemInfo& itemInfo);
    void DeleteItem(const std::wstring& id, const int subId);
    void UpdateItem(const ItemInfo& itemInfo);

    // ステータス内容を後から変えたいとき
    void UpdateStatusText(const std::wstring& text);

    // 小数点以下の文字数を調節
    static std::wstring ToStringWithPrecision(const float value, const int precision);

    void SetWeightAll(const float arg);
    void SetVolumeAll(const int arg);
    void SetVolumeMax(const int arg);

private:
    enum class eFocus
    {
        TOP_BAR,
        ITEM,
        ITEM_SUB,
        WEAPON,
        WEAPON_SUB,
        GUIDE,
        GUIDE_SUB,
        MAP,
        HUMAN,
        ENEMY,
        SKILL,
        STATUS,
        QUIT,
        OPENING,
    };

    const int TOPBAR_ITEM = 0;
    const int TOPBAR_WEAPON = 1;
    const int TOPBAR_GUIDE = 2;
    const int TOPBAR_MAP = 3;
    const int TOPBAR_HUMAN = 4;
    const int TOPBAR_ENEMY = 5;
    const int TOPBAR_SKILL = 6;
    const int TOPBAR_STATUS = 7;
    const int TOPBAR_QUIT = 8;
    const int TOPBAR_OPENING = 9;
    const int TOPBAR_MAX = 10;

    const int TOPBAR_PADDINGX = 50;
    const int TOPBAR_PADDINGY = 8;

    const int TOPBAR_STARTX = 90;
    const int TOPBAR_STARTY = 80;
    const int TOPBAR_PANEL_WIDTH = 200;
    const int TOPBAR_PANEL_HEIGHT = 60;

    const int TOPBAR_COL_MAX = 7;

    const int LEFT_PANEL_PADDINGX = 50;
    const int LEFT_PANEL_PADDINGY = 13;

    const int LEFT_PANEL_WIDTH = 432;
    const int LEFT_PANEL_HEIGHT = 60;

    const int LEFT_PANEL_STARTX = 80;
    const int LEFT_PANEL_STARTY = 280;

    const int MIDDLE_PANEL_STARTX = 630;

    const int LEFT_PANEL_CURSORX = 100;
    const int LEFT_PANEL_CURSORY = 295;

    const int MIDDLE_PANEL_CURSORX = 600;
    const int MIDDLE_PANEL_CURSORY = 295;

    const int LEFT_PANEL_ROW_MAX = 10;

    ISprite* m_sprCursor = nullptr;
    ISprite* m_sprBackground = nullptr;
    IFont* m_font = nullptr;
    IFont* m_fontStatus = nullptr;
    ISoundEffect* m_SE = nullptr;
    eFocus m_eFocus = eFocus::TOP_BAR;
    int m_topBarIndex { 0 };

    int m_itemCursor { 0 };
    int m_itemSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_itemBegin { 0 };
    int m_itemSubCursor { 0 };

    int m_humanCursor { 0 };
    int m_humanSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_humanBegin { 0 };

    int m_guideCursor { 0 };
    int m_guideSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_guideBegin { 0 };

    int m_guideSubCursor { 0 };
    int m_guideSubSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_guideSubBegin { 0 };

    int m_enemyCursor { 0 };
    int m_enemySelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_enemyBegin { 0 };

    int m_mapCursor { 0 };
    int m_mapSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_mapBegin { 0 };

    int m_weaponCursor { 0 };
    int m_weaponSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_weaponBegin { 0 };
    int m_weaponSubCursor { 0 };

    int m_skillCursor { 0 };
    int m_skillSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_skillBegin { 0 };

    int m_statusCursor { 0 };
    int m_statusSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_statusBegin { 0 };

    int m_quitCursor = 0;
    int m_openingCursor = 0;

    std::vector<std::wstring> m_TopBarName;

    // Into関数とClick関数で選択結果を返すときに使う。英語
    std::vector<std::wstring> m_TopBarNameKey;

    std::vector<ItemInfo> m_itemInfoList;
    std::vector<HumanInfo> m_humanInfoList;
    std::vector<EnemyInfo> m_enemyInfoList;
    std::vector<MapInfo> m_mapInfoList;
    std::vector<SkillInfo> m_skillInfoList;
    std::vector<StatusInfo> m_statusInfoList;
    std::vector<GuideInfo> m_guideInfoList;
    std::vector<WeaponInfo> m_weaponInfoList;

    std::vector<std::wstring> m_guideCategory;
    std::map<std::wstring, std::vector<std::wstring>> m_guideSubCategory;

    float m_weightAll = 0.f;
    int m_volumeAll = 0;
    int m_volumeMax = 0;

    bool m_bEnglish = false;
};
}

