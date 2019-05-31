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
    var WebInput = (function (_super) {
        __extends(WebInput, _super);
        function WebInput() {
            var _this = _super.call(this) || this;
            /**
             * @private
             */
            _this._styleInfoes = {};
            var div = document.createElement("div");
            _this.inputElement = document.createElement("input");
            _this.inputElement.type = "text";
            _this.inputElement.style.outline = "thin";
            _this.inputElement.style.background = "none";
            _this.inputElement.style.overflow = "hidden";
            _this.inputElement.style.wordBreak = "break-all";
            _this.inputElement.style.border = "1px solid #000000";
            _this.inputElement.setAttribute("tabindex", "-1");
            div.appendChild(_this.inputElement);
            _this.webNode = new OriginalWeb.WebNode();
            _this.webNode.bind(div);
            _this.textField = new egret.TextField();
            _this.addChild(_this.textField);
            _this.textField.size = 50;
            _this.textField.width = 300;
            _this.textField.height = 50;
            _this.textField.text = "输入框";
            _this.textField.textColor = 0xff0000;
            _this.textField.multiline = false;
            _this.init();
            return _this;
        }
        WebInput.prototype.init = function () {
            var _this = this;
            this.touchEnabled = true;
            this.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onTap, this);
            this.inputElement.oninput = function (e) {
                _this.textField.text = _this.inputElement.value;
            };
            this.inputElement.onfocus = function (e) {
                egret.log("focus");
                _this.textField.visible = false;
            };
            this.inputElement.onblur = function () {
                var player = document.getElementsByClassName("egret-player")[0];
                var canvas = player.getElementsByTagName("canvas")[0];
                // canvas["userTyping"] = false;
                egret.log("blur");
                _this.textField.visible = true;
                _this.removeChild(_this.webNode);
            };
            this.inputElement.onkeypress = function (e) {
                egret.log(e.keyCode);
            };
        };
        WebInput.prototype.onTap = function (e) {
            var player = document.getElementsByClassName("egret-player")[0];
            var canvas = player.getElementsByTagName("canvas")[0];
            // canvas["userTyping"] = true;
            e.stopImmediatePropagation();
            this.addChild(this.webNode);
            this.updateInput();
            this.inputElement.focus();
            egret.log("tap");
        };
        WebInput.prototype.updateInput = function () {
            var textfield = this.textField;
            this.setElementStyle("fontFamily", textfield.fontFamily);
            this.setElementStyle("fontStyle", textfield.italic ? "italic" : "normal");
            this.setElementStyle("fontWeight", textfield.bold ? "bold" : "normal");
            this.setElementStyle("textAlign", textfield.textAlign);
            this.setElementStyle("fontSize", textfield.size + "px");
            // this.setElementStyle("color", egret.toColorString(0x000000));
            this.setElementStyle("color", egret.toColorString(textfield.textColor));
            this.inputElement.value = textfield.text;
            var tw;
            if (textfield.stage) {
                tw = textfield.localToGlobal(0, 0).x;
                tw = Math.min(textfield.width, textfield.stage.stageWidth - tw);
            }
            else {
                tw = textfield.width;
            }
            this.setElementStyle("width", tw + "px");
            this.setElementStyle("verticalAlign", textfield.verticalAlign);
            this.setElementStyle("lineHeight", (textfield.size) + "px");
            if (textfield.height < textfield.size) {
                this.setElementStyle("height", (textfield.size) + "px");
                var bottom = (textfield.size / 2);
                this.setElementStyle("padding", "0px 0px " + bottom + "px 0px");
            }
            else {
                this.setElementStyle("height", (textfield.size) + "px");
                var rap = (textfield.height - textfield.size);
                var valign = egret.TextFieldUtils.$getValign(textfield);
                var top_1 = rap * valign;
                var bottom = rap - top_1;
                if (bottom < textfield.size / 2) {
                    bottom = textfield.size / 2;
                }
                this.setElementStyle("padding", top_1 + "px 0px " + bottom + "px 0px");
            }
            if (textfield.maxChars > 0) {
                this.inputElement.setAttribute("maxlength", textfield.maxChars + "");
            }
            else {
                this.inputElement.removeAttribute("maxlength");
            }
            this.inputElement.selectionStart = this.inputElement.value.length;
            this.inputElement.selectionEnd = this.inputElement.value.length;
        };
        /**
         * @private
         *
         * @param style
         * @param value
         */
        WebInput.prototype.setElementStyle = function (style, value) {
            if (this.inputElement) {
                if (this._styleInfoes[style] != value) {
                    this.inputElement.style[style] = value;
                    //this._styleInfoes[style] = value;
                }
            }
        };
        return WebInput;
    }(egret.DisplayObjectContainer));
    OriginalWeb.WebInput = WebInput;
    __reflect(WebInput.prototype, "OriginalWeb.WebInput");
})(OriginalWeb || (OriginalWeb = {}));
//# sourceMappingURL=WebInput.js.map