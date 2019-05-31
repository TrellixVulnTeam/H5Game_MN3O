/**
 * Created by Administrator on 2014/11/23.
 */

/**
 * Guiconfig
 * 枚举==guiconfig皮肤id
*/
enum ViewConst {
    Loading = 1017,
    Login = 1019,
    //Home, //废弃
    Friend,

    /*LSJ*/
    MainUI = 1001,    //主UI页面
    Chapter = 1009,   //关卡页面
    ChapterChoose = 1010,  //章节页面
    ChapterMseeag = 1014, //出战页面
    BattleResult = 1006,   //战斗结算

    BattlePicture = 1008,   //战斗立绘
    Dialog = 1021,                  //对话
    DialogOption = 1023,            //对话选择页面
    Hint = 1025,                 //提示框界面
    
    MailMain = 1031, //邮箱主页面
    MailDetail = 1032, //邮箱附件页面 

    MainActivity = 1035,  //活动主页面
    MainActivityItem = 1036,  //活动item

    TestSpine = 3000,

    /*ZSY */
    BattleMain = 1117,//战斗主界面
    BattleArray = 1002,//布阵
    ArrayItem = 1003,//布阵item
    BattleEdit = 1004,//战斗编辑
    HeroInfoItem = 1005,//人物信息
    Dialogue = 1029,//聊天
    GrilInfo=1037,//信息页面
    historyView=1038,//聊天记录

    

    /* */
    CCG_GameFight = 1018,//战斗

    SettingUI = 1020,//设置界面

    FightStartUI = 100000,//战斗开始界面(暂时不用)

    WechatUI = 1022,//通信功能

    DrawCardsUI = 100000,//抽卡(暂无)

    FriendMCommentUI = 1024,//朋友圈留言

    FriendlinessTipsUI = 1026,//友好度提示

    CreatureRoleUI = 1027,//角色创建

    VideoPlayUI = 1028,//视频播放UI

    WorldDriftTipsUI = 1030,//飄字提示界面

    ActivityRewardUI = 1033,//奖励活动界面

    HintCommonItemUI = 1034,//item提示框界面
}
