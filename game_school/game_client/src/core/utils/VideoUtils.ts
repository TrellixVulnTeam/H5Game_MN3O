
class VideoUtils extends BaseClass{
    private video:egret.Video;

    public PlayVideo(loadimg:string,videourl:string,callback?:Function){
        // if(App.DeviceUtils.IsMobile){
        //     // let video = document.getElementById("SVideo");
        //     // window["PlayVideo"](true,null,null,videourl,callback);
        //     window["PlayeVideoOnMobile"]("resource/assets/video/"+videourl,"resource/assets/video/"+loadimg,callback);移动端QQ浏览器会有bug
        // }
        // else
        {
            //http://res.w360.jygs.yx-g.com/school
            let webview= new WebView("http://res.w360.jygs.yx-g.com/school/video.html");
            webview.x = 0;
            webview.y = 0;
            webview.height= 1334;
            webview.width= 750;
            webview.show();
            App.TimerManager.doTimer(1000,1,function(){
                let all = webview.iframe.contentWindow.document.all;
                let video;
                for(let i=0;i<all.length;i++){
                    if(all[i].nodeName=="VIDEO"){
                        video= all[i];
                    }
                }
                if(video){
                    window["PlayVideo"](video,"resource/assets/video/"+loadimg,"resource/assets/video/"+videourl,function(){
                        if(callback){
                            callback();
                        }
                        webview.destroy();
                    });
                }
            },this);
        }
    }
}