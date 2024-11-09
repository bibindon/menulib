#pragma once
#include <string>
#include <vector>

namespace NSMenulib
{
class ISprite
{
public:
    virtual void DrawImage(const int x, const int y, const int transparency = 255) = 0;
    virtual void Load(const std::string& filepath) = 0;
    virtual ~ISprite() {};
};

class IFont
{
public:
    virtual void DrawText_(const std::string& msg, const int x, const int y) = 0;
    virtual void Init() = 0;
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
    std::string GetName();
    void SetName(const std::string& arg);
    int GetNum();
    void SetNum(const int arg);
    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);
    std::string GetDetail();
    void SetDetail(const std::string& arg);
private:
    std::string m_name;
    int m_num;
    ISprite* m_sprite;
    std::string m_detail;
};

class HumanInfo
{
public:
    std::string GetName();
    void SetName(const std::string& arg);
    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);
    std::string GetDetail();
    void SetDetail(const std::string& arg);
private:
    std::string m_name;
    ISprite* m_sprite;
    std::string m_detail;
};

class EnemyInfo
{
public:
    std::string GetName();
    void SetName(const std::string& arg);
    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);
    std::string GetDetail();
    void SetDetail(const std::string& arg);
private:
    std::string m_name;
    ISprite* m_sprite;
    std::string m_detail;
};

class SkillInfo
{
public:
    std::string GetName();
    void SetName(const std::string& arg);
    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);
    std::string GetDetail();
    void SetDetail(const std::string& arg);
private:
    std::string m_name;
    ISprite* m_sprite;
    std::string m_detail;
};

class MapInfo
{
public:
    std::string GetName();
    void SetName(const std::string& arg);
    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);
    std::string GetDetail();
    void SetDetail(const std::string& arg);
private:
    std::string m_name;
    ISprite* m_sprite;
    std::string m_detail;
};

class WeaponInfo
{
public:
    std::string GetName();
    void SetName(const std::string& arg);
    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);
    std::string GetDetail();
    void SetDetail(const std::string& arg);
private:
    std::string m_name;
    ISprite* m_sprite;
    std::string m_detail;
};

class TaskInfo
{
public:
    std::string GetName();
    void SetName(const std::string& arg);
    ISprite* GetSprite();
    void SetSprite(ISprite* const arg);
    std::string GetDetail();
    void SetDetail(const std::string& arg);
private:
    std::string m_name;
    ISprite* m_sprite;
    std::string m_detail;
};

class MenuLib
{
public:

    void Init(
        const std::string& csvfilepath,
        IFont* font,
        ISoundEffect* SE,
        ISprite* sprCursor,
        ISprite* sprBackground,
        ISprite* sprPanel,
        ISprite* sprPanelLeft
    );

    void SetItem(const std::vector<ItemInfo>& items);
    void SetHuman(const std::vector<HumanInfo>& items);
    void SetEnemy(const std::vector<EnemyInfo>& items);
    void SetMap(const std::vector<MapInfo>& items);
    void SetSkill(const std::vector<SkillInfo>& items);
    void SetTask(const std::vector<TaskInfo>& items);
    void SetWeapon(const std::vector<WeaponInfo>& items);
    std::string Up();
    std::string Down();
    std::string Right();
    std::string Left();
    std::string Into();
    std::string Back();
    std::string Next();
    std::string Previous();
    void Click(const int x, const int y);
    void RightClick(const int x, const int y);
    void Draw();

private:
    enum class eFocus
    {
        TOP_BAR,
        ITEM,
        ITEM_SUB,
        WEAPON,
        TASK,
        MAP,
        HUMAN,
        ENEMY,
        SKILL,
        STATUS,
        TITLE,
        OPENING,
    };

    const int TOPBAR_ITEM = 0;
    const int TOPBAR_WEAPON = 1;
    const int TOPBAR_TASK = 2;
    const int TOPBAR_MAP = 3;
    const int TOPBAR_HUMAN = 4;
    const int TOPBAR_ENEMY = 5;
    const int TOPBAR_SKILL = 6;
    const int TOPBAR_STATUS = 7;
    const int TOPBAR_TITLE = 8;
    const int TOPBAR_OPENING = 9;
    const int TOPBAR_MAX = 10;

    const int TOPBAR_PADDINGX = 50;
    const int TOPBAR_PADDINGY = 8;

    const int TOPBAR_STARTX = 100;
    const int TOPBAR_STARTY = 80;
    const int TOPBAR_PANEL_WIDTH = 200;
    const int TOPBAR_PANEL_HEIGHT = 50;

    const int TOPBAR_COL_MAX = 7;

    const int LEFT_PANEL_PADDINGX = 50;
    const int LEFT_PANEL_PADDINGY = 13;

    const int LEFT_PANEL_WIDTH = 432;
    const int LEFT_PANEL_HEIGHT = 60;

    const int LEFT_PANEL_STARTX = 100;
    const int LEFT_PANEL_STARTY = 200;

    const int LEFT_PANEL_ROW_MAX = 10;

    ISprite* m_sprCursor;
    ISprite* m_sprBackground;
    ISprite* m_sprPanel;
    ISprite* m_sprPanelLeft;
    IFont* m_font;
    ISoundEffect* m_SE;
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

    int m_taskCursor { 0 };
    int m_taskSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_taskBegin { 0 };

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

    int m_skillCursor { 0 };
    int m_skillSelect { 0 };
    // 何番目のアイテムが一番上に表示されているか
    // スクロール可能なので一番上に表示されるアイテムはスクロールすると変わる。
    int m_skillBegin { 0 };

    std::vector<std::string> m_TopBarName;
    std::vector<ItemInfo> m_itemInfoList;
    std::vector<HumanInfo> m_humanInfoList;
    std::vector<EnemyInfo> m_enemyInfoList;
    std::vector<MapInfo> m_mapInfoList;
    std::vector<SkillInfo> m_skillInfoList;
    std::vector<TaskInfo> m_taskInfoList;
    std::vector<WeaponInfo> m_weaponInfoList;
};
}

