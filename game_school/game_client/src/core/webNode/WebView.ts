module OriginalWeb {
	export class WebView extends WebNode {

		private _iframe:HTMLIFrameElement;

		public get iframe(): HTMLIFrameElement {
		    return this._iframe;
		}
		public constructor(src:string) {
			super();

			this._iframe = document.createElement("iframe");
			this.src = src;

			this.bind(this._iframe);
		}

		private _src : string;
		public get src() : string {
			return this._src;
		}
		public set src(v : string) {
			this._src = v;

			this.iframe.src = v;
		}


		
	}
}