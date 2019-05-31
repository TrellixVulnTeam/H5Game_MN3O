var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var ConfFact = (function () {
    function ConfFact() {
    }
    ConfFact.ConfigCount = function () {
        if (!this.arrayName || this.arrayName.length < 1) {
            this.arrayName = [];
            this.arrayName.push("ActivityClientConfig");
            this.arrayName.push("AttributeFormatConfig");
            this.arrayName.push("BattleConfig");
            this.arrayName.push("BlackScreenConfig");
            this.arrayName.push("BuffConfig");
            this.arrayName.push("BuffEffectConfig");
            this.arrayName.push("BuffGroupConfig");
            this.arrayName.push("ChapterConfig");
            this.arrayName.push("ChatConfig");
            this.arrayName.push("ChatGroupConfig");
            this.arrayName.push("ChatGroupNumConfig");
            this.arrayName.push("ChatOptionConfig");
            this.arrayName.push("CheckPointConfig");
            this.arrayName.push("CheckPointRequestConfig");
            this.arrayName.push("ClientConstConfig");
            this.arrayName.push("CreatureAbilityConfig");
            this.arrayName.push("CreatureAttrForceConfig");
            this.arrayName.push("CreatureAttrTypeConfig");
            this.arrayName.push("CreatureSpawnConfig");
            this.arrayName.push("CreatureTempletConfig");
            this.arrayName.push("DailySignMonthRewardConfig");
            this.arrayName.push("DailySignTotalRewardConfig");
            this.arrayName.push("DialogConfig");
            this.arrayName.push("DialogOptionConfig");
            this.arrayName.push("DrawAnimationConfig");
            this.arrayName.push("DrawConfig");
            this.arrayName.push("EffectConfig");
            this.arrayName.push("FaceConfig");
            this.arrayName.push("FilterNameConfig");
            this.arrayName.push("GirlConfig");
            this.arrayName.push("GuiConfig");
            this.arrayName.push("GuideConfig");
            this.arrayName.push("HeroGetConfig");
            this.arrayName.push("ItemCommonConfig");
            this.arrayName.push("MagicConfig");
            this.arrayName.push("MagicEffectConfig");
            this.arrayName.push("ModelConfig");
            this.arrayName.push("PlotGroupConfig");
            this.arrayName.push("PreloadReourceConfig");
            this.arrayName.push("PublicConstConfig");
            this.arrayName.push("RandomPoolConfig");
            this.arrayName.push("RoleNameConfig");
            this.arrayName.push("SceneEffectConfig");
            this.arrayName.push("StrConfig");
            this.arrayName.push("UIHintConfig");
            this.arrayName.push("WechatConfig");
            this.arrayName.push("WechatContentConfig");
        }
        return this.arrayName.length;
    };
    ConfFact.Register = function () {
        ActivityClientConfig.Init();
        AttributeFormatConfig.Init();
        BattleConfig.Init();
        BlackScreenConfig.Init();
        BuffConfig.Init();
        BuffEffectConfig.Init();
        BuffGroupConfig.Init();
        ChapterConfig.Init();
        ChatConfig.Init();
        ChatGroupConfig.Init();
        ChatGroupNumConfig.Init();
        ChatOptionConfig.Init();
        CheckPointConfig.Init();
        CheckPointRequestConfig.Init();
        ClientConstConfig.Init();
        CreatureAbilityConfig.Init();
        CreatureAttrForceConfig.Init();
        CreatureAttrTypeConfig.Init();
        CreatureSpawnConfig.Init();
        CreatureTempletConfig.Init();
        DailySignMonthRewardConfig.Init();
        DailySignTotalRewardConfig.Init();
        DialogConfig.Init();
        DialogOptionConfig.Init();
        DrawAnimationConfig.Init();
        DrawConfig.Init();
        EffectConfig.Init();
        FaceConfig.Init();
        FilterNameConfig.Init();
        GirlConfig.Init();
        GuiConfig.Init();
        GuideConfig.Init();
        HeroGetConfig.Init();
        ItemCommonConfig.Init();
        MagicConfig.Init();
        MagicEffectConfig.Init();
        ModelConfig.Init();
        PlotGroupConfig.Init();
        PreloadReourceConfig.Init();
        PublicConstConfig.Init();
        RandomPoolConfig.Init();
        RoleNameConfig.Init();
        SceneEffectConfig.Init();
        StrConfig.Init();
        UIHintConfig.Init();
        WechatConfig.Init();
        WechatContentConfig.Init();
    };
    ConfFact.ResLoaded = function () {
        if (!ActivityClientConfig.resLoaded)
            return false;
        if (!AttributeFormatConfig.resLoaded)
            return false;
        if (!BattleConfig.resLoaded)
            return false;
        if (!BlackScreenConfig.resLoaded)
            return false;
        if (!BuffConfig.resLoaded)
            return false;
        if (!BuffEffectConfig.resLoaded)
            return false;
        if (!BuffGroupConfig.resLoaded)
            return false;
        if (!ChapterConfig.resLoaded)
            return false;
        if (!ChatConfig.resLoaded)
            return false;
        if (!ChatGroupConfig.resLoaded)
            return false;
        if (!ChatGroupNumConfig.resLoaded)
            return false;
        if (!ChatOptionConfig.resLoaded)
            return false;
        if (!CheckPointConfig.resLoaded)
            return false;
        if (!CheckPointRequestConfig.resLoaded)
            return false;
        if (!ClientConstConfig.resLoaded)
            return false;
        if (!CreatureAbilityConfig.resLoaded)
            return false;
        if (!CreatureAttrForceConfig.resLoaded)
            return false;
        if (!CreatureAttrTypeConfig.resLoaded)
            return false;
        if (!CreatureSpawnConfig.resLoaded)
            return false;
        if (!CreatureTempletConfig.resLoaded)
            return false;
        if (!DailySignMonthRewardConfig.resLoaded)
            return false;
        if (!DailySignTotalRewardConfig.resLoaded)
            return false;
        if (!DialogConfig.resLoaded)
            return false;
        if (!DialogOptionConfig.resLoaded)
            return false;
        if (!DrawAnimationConfig.resLoaded)
            return false;
        if (!DrawConfig.resLoaded)
            return false;
        if (!EffectConfig.resLoaded)
            return false;
        if (!FaceConfig.resLoaded)
            return false;
        if (!FilterNameConfig.resLoaded)
            return false;
        if (!GirlConfig.resLoaded)
            return false;
        if (!GuiConfig.resLoaded)
            return false;
        if (!GuideConfig.resLoaded)
            return false;
        if (!HeroGetConfig.resLoaded)
            return false;
        if (!ItemCommonConfig.resLoaded)
            return false;
        if (!MagicConfig.resLoaded)
            return false;
        if (!MagicEffectConfig.resLoaded)
            return false;
        if (!ModelConfig.resLoaded)
            return false;
        if (!PlotGroupConfig.resLoaded)
            return false;
        if (!PreloadReourceConfig.resLoaded)
            return false;
        if (!PublicConstConfig.resLoaded)
            return false;
        if (!RandomPoolConfig.resLoaded)
            return false;
        if (!RoleNameConfig.resLoaded)
            return false;
        if (!SceneEffectConfig.resLoaded)
            return false;
        if (!StrConfig.resLoaded)
            return false;
        if (!UIHintConfig.resLoaded)
            return false;
        if (!WechatConfig.resLoaded)
            return false;
        if (!WechatContentConfig.resLoaded)
            return false;
        return true;
    };
    ConfFact.SetResLoad = function (name) {
        this.loadedName.push(name);
    };
    ConfFact.GetLoadedConfigName = function () {
        return this.loadedName;
    };
    ConfFact.arrayName = [];
    ConfFact.loadedName = [];
    return ConfFact;
}());
__reflect(ConfFact.prototype, "ConfFact");
//# sourceMappingURL=ConfFact.js.map