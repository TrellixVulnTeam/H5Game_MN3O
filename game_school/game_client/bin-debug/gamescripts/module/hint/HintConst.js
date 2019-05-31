var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 *
 */
var HintConst = (function () {
    function HintConst() {
    }
    //剧情跳过确认
    //public static DIALOGSKIP_C2C: number = 10001;
    // //选择选项
    // public static SELECTOPTION_C2C: number = 10002;
    // Hint
    HintConst.HINT_OK = 10002;
    HintConst.HINT_OK_NOT_REPEAT = 10003;
    HintConst.HINT_OK_CANCEL = 10004;
    HintConst.HINT_OK_COUNTDOWN = 10005; //显示倒计时
    HintConst.MUTIL_HINT_OK_CANCEL = 10006;
    HintConst.HINT_AUTO_CANCEL = 10007;
    HintConst.HINT_AUTO_CANCEL_NEW = 10008;
    HintConst.HINT_NOT_REPEAT = 10009;
    HintConst.HINT_ALL_HIDE = 10010;
    HintConst.HINT_NUMBER_OK_CANCEL = 10011;
    HintConst.HINT_AUTO_OK_CANCEL = 10012;
    HintConst.HINT_NOT_REPEAT_WITH_OPTION = 10012;
    HintConst.HINT_ITEM_NUMBER_OK_CANCEL = 10013;
    HintConst.SHOW_MESSAGE = 10014;
    return HintConst;
}());
__reflect(HintConst.prototype, "HintConst");
//# sourceMappingURL=HintConst.js.map