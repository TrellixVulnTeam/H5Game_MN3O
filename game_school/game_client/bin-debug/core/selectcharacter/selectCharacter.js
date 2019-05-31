var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 *
 * 选择角色
 */
var selectCharacter = (function () {
    function selectCharacter() {
    }
    selectCharacter.onSelectImg = function (parent, camp) {
        var img = parent.getChildByName("selectImg");
        if (img == null) {
            var selectImg = void 0;
            selectImg = ObjectPool.pop("eui.Image");
            if (camp == Camp.Friendly)
                selectImg.source = "battle_di2_png";
            else if (camp == Camp.Hostility)
                selectImg.source = "battle_di_png";
            selectImg.x = -75;
            selectImg.y = -25;
            selectImg.name = "selectImg";
            parent.addChildAt(selectImg, 0);
            selectCharacter.playEffect(selectImg, false);
        }
    };
    selectCharacter.playEffect = function (obj, isPlayEffectPlay) {
        if (isPlayEffectPlay) {
            return;
        }
        isPlayEffectPlay = true;
        var onComplete2 = function () {
            this.isPlayEffectPlay = false;
        };
        var onComplete1 = function () {
            egret.Tween.get(obj, { loop: true }).to({ scaleX: 1, scaleY: 1, x: obj.x - obj.width / 4, y: obj.y - obj.height / 4 }, 500, egret.Ease.backOut).call(onComplete2, this);
        };
        egret.Tween.get(obj).to({ scaleX: 0.5, scaleY: 0.5, x: obj.x + obj.width / 4, y: obj.y + obj.height / 4 }, 100, egret.Ease.sineIn).call(onComplete1, this);
    };
    selectCharacter.unSelectImg = function (parent) {
        var img = parent.getChildByName("selectImg");
        if (img != null) {
            App.DisplayUtils.removeFromParent(img);
            ObjectPool.push(img);
        }
    };
    return selectCharacter;
}());
__reflect(selectCharacter.prototype, "selectCharacter");
//# sourceMappingURL=selectCharacter.js.map