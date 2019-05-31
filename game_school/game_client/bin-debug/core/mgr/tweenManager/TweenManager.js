var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 *
 * 复用动画管理类 BY:LSJ
 */
var TweenManager = (function () {
    function TweenManager() {
    }
    /**
    * UI 从中心打开和关闭
    * @param com 你要操作的某个UI
    * @param view 这个UI隶属于那个view
    * @param toNum 打开还是关闭,0是关闭,1是打开
    * @param time 动画的时间
    * @param onComplete 动画的结束事件
    * @param isLoop 动画是否循环
    * 这个动画就是在操作 scale 的缩放来实现打开和关闭
    */
    TweenManager.scaleTween = function (com, view, toNum, time, onComplete, isLoop) {
        if (isLoop === void 0) { isLoop = false; }
        if (toNum == 0) {
            if (com.scaleY == 0 || com.scaleX == 0) {
                com.scaleY = 1;
                com.scaleX = 1;
            }
        }
        else if (toNum == 1) {
            if (com.scaleY == 1 || com.scaleX == 1) {
                com.scaleY = 0;
                com.scaleX = 0;
            }
        }
        //创建 Tween 对象
        egret.Tween.get(com, {
            loop: isLoop,
            //onChange: view,
            onChangeObj: view //更新函数作用域
        })
            .to({ scaleY: toNum, scaleX: toNum }, time) //设置500毫秒内 scaleY 属性变为 0     
            .call(function () {
            if (onComplete) {
                onComplete();
            }
        });
    };
    TweenManager.doAlpha = function (com, value, time, callback) {
        if (time === void 0) { time = 100; }
        if (value == 0)
            com.alpha = 1;
        else
            com.alpha = 0;
        egret.Tween.get(com)
            .to({ alpha: value }, time) //设置500毫秒内 scaleY 属性变为 0     
            .call(function () {
            com.alpha = 1;
            if (callback) {
                callback();
            }
        });
    };
    /**
    * 文本逐渐显示
    * @param com 你要操作的label组件
    * @param text 你要显示的文本
    * @param time 每个字出现的间隔时间
    * @param callback 结束之后的回调事件
    */
    TweenManager.doText = function (com, text, time, callback) {
        if (time === void 0) { time = 100; }
        var str = App.StringUtils.trimSpace(text);
        //let strIndex = App.StringUtils.getStringLength(str);
        var strIndex = str.length + 1;
        var count = 1;
        function oneByOne() {
            var screen = text.substr(0, count);
            com.text = screen;
            count++;
            if (count == strIndex) {
                if (callback != null)
                    callback();
                return;
            }
            TweenManager.index = setTimeout(oneByOne, time);
        }
        TweenManager.closeDoText();
        oneByOne();
    };
    /**
    * 外部调用关闭文本循环的方法
    */
    TweenManager.closeDoText = function () {
        if (TweenManager.index != null)
            clearTimeout(TweenManager.index);
    };
    //下面专用的,在启用 setTimeout 计时器的时候,缓存当前的计时器编号
    TweenManager.index = null;
    return TweenManager;
}());
__reflect(TweenManager.prototype, "TweenManager");
//# sourceMappingURL=TweenManager.js.map