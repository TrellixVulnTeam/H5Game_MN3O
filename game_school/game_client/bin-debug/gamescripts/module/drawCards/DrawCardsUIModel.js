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
var DrawCardsUIModel = (function (_super) {
    __extends(DrawCardsUIModel, _super);
    function DrawCardsUIModel($controller) {
        return _super.call(this, $controller) || this;
    }
    return DrawCardsUIModel;
}(BaseModel));
__reflect(DrawCardsUIModel.prototype, "DrawCardsUIModel");
//# sourceMappingURL=DrawCardsUIModel.js.map