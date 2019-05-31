/**
 * @author sjz
 * @time 2018-8-13 17:33
 * @description 事件定义
 */
var EventDef;
(function (EventDef) {
    EventDef[EventDef["NONE"] = 0] = "NONE";
    /**zsy */
    /**朋友圈 */
    EventDef[EventDef["announceInfo"] = 1] = "announceInfo";
    EventDef[EventDef["commentInfo"] = 2] = "commentInfo";
    EventDef[EventDef["updateFriendsInfo"] = 3] = "updateFriendsInfo";
    EventDef[EventDef["updateCommentInfo"] = 4] = "updateCommentInfo";
    /**聊天 */
    EventDef[EventDef["InquireChatInfo"] = 5] = "InquireChatInfo";
    EventDef[EventDef["OpenListByType"] = 6] = "OpenListByType";
    EventDef[EventDef["OpendialogView"] = 7] = "OpendialogView";
    EventDef[EventDef["BackDialogListView"] = 8] = "BackDialogListView";
    EventDef[EventDef["ActivationChatGroup"] = 9] = "ActivationChatGroup";
    EventDef[EventDef["OpendialogViewByChatId"] = 10] = "OpendialogViewByChatId";
    /**通讯录 */
    EventDef[EventDef["OpenAddressBookList"] = 11] = "OpenAddressBookList";
    EventDef[EventDef["OpenGirlInfoView"] = 12] = "OpenGirlInfoView";
    EventDef[EventDef["CloseGirlInfoView"] = 13] = "CloseGirlInfoView";
    EventDef[EventDef["OpenHistoryView"] = 14] = "OpenHistoryView";
    /**战斗页面 */
    EventDef[EventDef["GameInit"] = 15] = "GameInit";
    EventDef[EventDef["GameResize"] = 16] = "GameResize";
    EventDef[EventDef["GameStart"] = 17] = "GameStart";
    EventDef[EventDef["UpdateRound"] = 18] = "UpdateRound";
    EventDef[EventDef["InitUI"] = 19] = "InitUI";
    EventDef[EventDef["UpdateTimer"] = 20] = "UpdateTimer";
    EventDef[EventDef["UpdateHpBar"] = 21] = "UpdateHpBar";
    EventDef[EventDef["OpenSkill"] = 22] = "OpenSkill";
    EventDef[EventDef["SwitchingFight"] = 23] = "SwitchingFight";
    EventDef[EventDef["FightAni"] = 24] = "FightAni";
    EventDef[EventDef["FightConvert"] = 25] = "FightConvert";
    EventDef[EventDef["FightMaskViableTrue"] = 26] = "FightMaskViableTrue";
    EventDef[EventDef["FightMaskViableFalse"] = 27] = "FightMaskViableFalse";
    EventDef[EventDef["SetBackMainBtnVis"] = 28] = "SetBackMainBtnVis";
    /**战斗立绘 */
    EventDef[EventDef["SKILLPICTURE_C2C"] = 29] = "SKILLPICTURE_C2C";
    EventDef[EventDef["HPPICTURE_C2C"] = 30] = "HPPICTURE_C2C";
    /**战斗编队 */
    EventDef[EventDef["UpdateArrayList"] = 31] = "UpdateArrayList";
    EventDef[EventDef["ChangeTeam"] = 32] = "ChangeTeam";
    EventDef[EventDef["ShowHeroList"] = 33] = "ShowHeroList";
    EventDef[EventDef["AddHero"] = 34] = "AddHero";
    EventDef[EventDef["SetAddState"] = 35] = "SetAddState";
    EventDef[EventDef["CheckCollision"] = 36] = "CheckCollision";
    EventDef[EventDef["InitArray"] = 37] = "InitArray";
    EventDef[EventDef["StartFightByArray"] = 38] = "StartFightByArray";
    /**商城 */
    EventDef[EventDef["UPDATADATA_C2S"] = 39] = "UPDATADATA_C2S";
    EventDef[EventDef["SELECTMAIL_C2S"] = 40] = "SELECTMAIL_C2S";
    /**item提示框 */
    EventDef[EventDef["SHOWHINTITEMUI"] = 41] = "SHOWHINTITEMUI";
    //--------lsj----------------
    EventDef[EventDef["SelectChapter"] = 42] = "SelectChapter";
    EventDef[EventDef["SelectCheckPoint"] = 43] = "SelectCheckPoint";
    EventDef[EventDef["NextCheckPoint"] = 44] = "NextCheckPoint";
    EventDef[EventDef["PlayPlotGroup"] = 45] = "PlayPlotGroup";
    EventDef[EventDef["SelectDialogOption"] = 46] = "SelectDialogOption";
    EventDef[EventDef["DialogSkip"] = 47] = "DialogSkip";
    //--------------------------
    EventDef[EventDef["ActivityReward_dailySign"] = 48] = "ActivityReward_dailySign";
    EventDef[EventDef["Friendliness_tips"] = 49] = "Friendliness_tips";
    EventDef[EventDef["LoadingRes_progress"] = 50] = "LoadingRes_progress";
    EventDef[EventDef["LoadingConfig_progress"] = 51] = "LoadingConfig_progress";
    EventDef[EventDef["Setdrift_world"] = 52] = "Setdrift_world";
})(EventDef || (EventDef = {}));
//# sourceMappingURL=EventDef.js.map