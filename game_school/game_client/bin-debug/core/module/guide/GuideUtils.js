var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var __extends = this && this.__extends || function __extends(t, e) { 
 function r() { 
 this.constructor = t;
}
for (var i in e) e.hasOwnProperty(i) && (t[i] = e[i]);
r.prototype = e.prototype, t.prototype = new r();
};
/**
 *
 * 引导工具类，根据每个项目重写实现可重写实现
 */
var GuideUtils = (function (_super) {
    __extends(GuideUtils, _super);
    function GuideUtils() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        //handDir  1:下面 2:上面
        //txtdir  箭头指向: 1:背景左箭头下 2:背景左箭头上 3:背景右箭头下 4:背景右箭头上
        _this.configData = {
            "1": {
                "1": {
                    "txt": "点击这里，去设置宠物出战",
                    "txtdir": 1,
                    "handDir": 1
                },
                "2": {
                    "txt": "点击选择一个宠物出战",
                    "txtdir": 3,
                    "handDir": 1
                },
                "3": {
                    "txt": "点击宠物出战",
                    "txtdir": 3,
                    "handDir": 1
                }
            },
            "2": {
                "1": {
                    "txt": "更多宠物，可以抽取获得哦！",
                    "txtdir": 1,
                    "handDir": 2
                },
                "2": {
                    "txt": "点击抽取宠物",
                    "txtdir": 1,
                    "handDir": 1
                }
            },
            "3": {
                "1": {
                    "txt": "点击选择另一个宠物",
                    "txtdir": 1,
                    "handDir": 1
                },
                "2": {
                    "txt": "点击宠物出战",
                    "txtdir": 3,
                    "handDir": 1
                }
            },
            "4": {
                "1": {
                    "txt": "点击查看宠物属性",
                    "txtdir": 4,
                    "handDir": 1
                },
                "2": {
                    "txt": "点击宠物升级",
                    "txtdir": 1,
                    "handDir": 2
                },
                "3": {
                    "txt": "点击选择升级材料",
                    "txtdir": 3,
                    "handDir": 1
                },
                "4": {
                    "txt": "选择一个宠物或卡牌作为材料",
                    "txtdir": 3,
                    "handDir": 1
                },
                "5": {
                    "txt": "选择材料后点击确定回到升级界面",
                    "txtdir": 1,
                    "handDir": 2
                },
                "6": {
                    "txt": "点击完成升级",
                    "txtdir": 1,
                    "handDir": 2
                }
            },
            "5": {
                "1": {
                    "txt": "现在立刻享受\n炫酷的飞行吧",
                    "txtdir": 1,
                    "handDir": 2
                },
                "2": {
                    "txt": "每天前3次购买免费",
                    "txtdir": 1,
                    "handDir": 1
                },
                "3": {
                    "txt": "开始战斗吧",
                    "txtdir": 1,
                    "handDir": 2
                }
            },
            "6": {
                "1": {
                    "txt": "点击这里查看战机",
                    "txtdir": 1,
                    "handDir": 1
                },
                "2": {
                    "txt": "点击升级战机，\n可以提高战力",
                    "txtdir": 1,
                    "handDir": 2
                }
            }
        };
        /**
         * 大步骤
         * @type {number}
         */
        _this.currPart = 0;
        /**
         * 小步骤
         * @type {number}
         */
        _this.currStep = 0;
        return _this;
    }
    /**
     * 下一步
     */
    GuideUtils.prototype.next = function () {
        if (this.view == null || this.view.parent == null) {
            return;
        }
        this.currStep++;
        if (!this.configData[this.currPart][this.currStep]) {
            //下一部分
            this.currPart++;
            this.currStep = 1;
            //通知服务端
            //TODO
        }
        if (!this.configData[this.currPart]) {
            //所有引导结束
            this.currPart = 0;
            this.currStep = 0;
        }
        this.hide();
    };
    /**
     * 显示
     */
    GuideUtils.prototype.show = function (obj, targetPart, targetStep) {
        if (this.currPart == targetPart && this.currStep == targetStep) {
            if (this.view == null) {
                this.view = new GuideView();
            }
            this.view.setData(obj, this.configData[this.currPart][this.currStep]);
            egret.MainContext.instance.stage.addChild(this.view);
        }
    };
    /**
     * 隐藏
     */
    GuideUtils.prototype.hide = function () {
        App.DisplayUtils.removeFromParent(this.view);
    };
    /**
     * 引导是否显示
     */
    GuideUtils.prototype.isShow = function () {
        return this.view != null && this.view.parent != null;
    };
    return GuideUtils;
}(BaseClass));
__reflect(GuideUtils.prototype, "GuideUtils");
//# sourceMappingURL=GuideUtils.js.map