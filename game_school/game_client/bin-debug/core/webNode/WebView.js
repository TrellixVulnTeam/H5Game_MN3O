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
    var WebView = (function (_super) {
        __extends(WebView, _super);
        function WebView(src) {
            var _this = _super.call(this) || this;
            _this._iframe = document.createElement("iframe");
            _this.src = src;
            _this.bind(_this._iframe);
            return _this;
        }
        Object.defineProperty(WebView.prototype, "iframe", {
            get: function () {
                return this._iframe;
            },
            enumerable: true,
            configurable: true
        });
        Object.defineProperty(WebView.prototype, "src", {
            get: function () {
                return this._src;
            },
            set: function (v) {
                this._src = v;
                this.iframe.src = v;
            },
            enumerable: true,
            configurable: true
        });
        return WebView;
    }(OriginalWeb.WebNode));
    OriginalWeb.WebView = WebView;
    __reflect(WebView.prototype, "OriginalWeb.WebView");
})(OriginalWeb || (OriginalWeb = {}));
//# sourceMappingURL=WebView.js.map