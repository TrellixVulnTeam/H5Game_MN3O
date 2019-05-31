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
var OriginalWeb;
(function (OriginalWeb) {
    /**
     * 显示到 egret 中的 DOM 元件
     */
    var WebNode = (function (_super) {
        __extends(WebNode, _super);
        function WebNode() {
            var _this = _super.call(this) || this;
            _this.domNode = new OriginalWeb.DOMNode();
            _this.domNode.mapDisplayObject(_this);
            _this.addEventListener(egret.Event.ADDED_TO_STAGE, _this.addToStage, _this);
            _this.addEventListener(egret.Event.REMOVED_FROM_STAGE, _this.removeFromStage, _this);
            _this.$renderNode = new egret.sys.RenderNode();
            return _this;
        }
        /**
         * 绑定一个 DOM 元件
         * @element DOM 元件，不要修改此元件的 style 的位置、旋转、缩放、边框等属性
         */
        WebNode.prototype.bind = function (element) {
            this.domNode.bind(element);
        };
        /**
         * 解绑 DOM 元件
         */
        WebNode.prototype.unbind = function () {
            this.domNode.unbind();
        };
        WebNode.prototype.addToStage = function () {
            if (egret.Capabilities.runtimeType == egret.RuntimeType.WEB) {
                this.domNode.show();
                this.domNode.updatePosition();
                this.tempStage = this.stage;
                this.tempStage.addEventListener(egret.Event.RESIZE, this.onResize, this);
                this.addEventListener(egret.Event.ENTER_FRAME, this.onResize, this);
            }
        };
        WebNode.prototype.removeFromStage = function () {
            this.removeEventListener(egret.Event.ENTER_FRAME, this.onResize, this);
            // this.tempStage.removeEventListener(egret.Event.RESIZE, this.onResize, this);
            this.domNode.hide();
            this.tempStage = null;
        };
        WebNode.prototype.onResize = function () {
            if (this.domNode) {
                this.domNode.updatePosition();
            }
        };
        return WebNode;
    }(egret.DisplayObject));
    OriginalWeb.WebNode = WebNode;
    __reflect(WebNode.prototype, "OriginalWeb.WebNode");
})(OriginalWeb || (OriginalWeb = {}));
//# sourceMappingURL=WebNode.js.map