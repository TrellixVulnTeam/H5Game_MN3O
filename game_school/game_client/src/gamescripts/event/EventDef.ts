
/**
 * @author sjz
 * @time 2018-8-13 17:33
 * @description 事件定义
 */

enum EventDef{
    NONE,

    /**zsy */

    /**朋友圈 */
    announceInfo,//发布消息//
    commentInfo,//留言//
    updateFriendsInfo,//刷新朋友圈消息//
    updateCommentInfo,//刷新留言回复//

    /**聊天 */
    InquireChatInfo,//查询聊天信息
    OpenListByType,//打开列表通过类型
    OpendialogView,//打开聊天
    BackDialogListView,//返回聊天列表
    ActivationChatGroup,//激活聊天组
    OpendialogViewByChatId,//打开聊天

     /**通讯录 */
    OpenAddressBookList,//打开通讯录
    OpenGirlInfoView,//打开信息页面
    CloseGirlInfoView,//关闭信息页面
    OpenHistoryView,//打开聊天记录

    /**战斗页面 */
    GameInit, //初始化战斗信息
    GameResize,//游戏重置
    GameStart,//战斗开始
    UpdateRound,//更新回合数
    InitUI,//初始化ui
    UpdateTimer,//更新时间
    UpdateHpBar,//更新血条
    OpenSkill,//打开技能
    SwitchingFight,//切换战斗方式
    FightAni,//战斗动画
    FightConvert,//转换下场战斗
    FightMaskViableTrue,//战斗表现
    FightMaskViableFalse,//战斗表现
    SetBackMainBtnVis,//返回主页按钮显隐

    /**战斗立绘 */
    SKILLPICTURE_C2C,//战斗放大招的立绘
    HPPICTURE_C2C, //战斗残血出现的破损立绘

    /**战斗编队 */
    UpdateArrayList,//更新英雄列表
	ChangeTeam,//切换队伍
	ShowHeroList,//显示英雄列表
	AddHero,//添加英雄
	SetAddState,//设置添加按钮
	CheckCollision,//检测碰撞
	InitArray,//初始化队伍信息
	StartFightByArray,//从编队开启战斗

    /**商城 */
    UPDATADATA_C2S,
    SELECTMAIL_C2S,

    /**item提示框 */
    SHOWHINTITEMUI,
    

     //--------lsj----------------
    SelectChapter,              //点击选择章节事件
    SelectCheckPoint,           //点击选择关卡事件
    NextCheckPoint,             //检查下一关是够开启,属于临时代码

    PlayPlotGroup,              //播放对话组
    SelectDialogOption,         //选择对话选项

    DialogSkip,                 //跳过对话
    //--------------------------


    ActivityReward_dailySign,//签到活动,刷新当前累签奖励
    Friendliness_tips,//朋友圈提示
    LoadingRes_progress,//加载资源进度
    LoadingConfig_progress,//加载config进度
    Setdrift_world,//飘字提示
}

