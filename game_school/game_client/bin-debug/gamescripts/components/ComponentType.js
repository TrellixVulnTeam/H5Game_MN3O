var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * Created by sjz on 2018-5-9.
 */
var ComponentType = (function () {
    function ComponentType() {
    }
    ComponentType.Avatar = "AvatarComponent";
    ComponentType.Move = "MoveComponent";
    ComponentType.Head = "HeadComponent";
    ComponentType.Skill = "SkillComponent";
    ComponentType.Buff = "BuffComponent";
    ComponentType.Dragon = "DragonComponent";
    ComponentType.AvatarEffect = "AvatarEffectComponent"; //所有的特效表现最后在这里处理
    return ComponentType;
}());
__reflect(ComponentType.prototype, "ComponentType");
//# sourceMappingURL=ComponentType.js.map