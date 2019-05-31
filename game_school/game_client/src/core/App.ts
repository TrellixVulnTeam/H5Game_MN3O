enum LoadSetp{
    FIRST=1,
    SECOND=2,
    THIRD=3,
}

/**
 * Created by yangsong on 2014/11/22.
 */
class App {
    /**
     * 请求服务器使用的用户标识
     * @type {string}
     */
    public static ProxyUserFlag: string = "";
    /**
     * 全局配置数据
     * @type {null}
     */
    public static GlobalData: any = null;
    /**
     * ProtoConfig
     * @type {null}
     */
    public static ProtoConfig: any = null;

    /**
     * Http请求
     * @type {Http}
     */
    public static get Http(): Http {
        return Http.getInstance();
    }

    /**
     * Socket请求
     * @type {null}
     */
    public static get Socket(): Socket {
        return Socket.getInstance();
    }

    /**
     * 模块管理类
     * @type {ControllerManager}
     */
    public static get ControllerManager(): ControllerManager {
        return ControllerManager.getInstance();
    }

    /**
     * View管理类
     * @type {ViewManager}
     */
    public static get ViewManager(): ViewManager {
        return ViewManager.getInstance();
    }

    /**
     * 场景管理类
     * @type {SceneManager}
     */
    public static get SceneManager(): SceneManager {
        return SceneManager.getInstance();
    }

    /**
     * 调试工具
     * @type {DebugUtils}
     */
    public static get DebugUtils(): DebugUtils {
        return DebugUtils.getInstance();
    }

    /**
     * 服务器返回的消息处理中心
     * @type {MessageCenter}
     */
    public static get MessageCenter(): MessageCenter {
        return MessageCenter.getInstance(0);
    }

    /**
     * 统一的计时器和帧刷管理类
     * @type {TimerManager}
     */
    public static get TimerManager(): TimerManager {
        return TimerManager.getInstance();
    }

    /**
     * 日期工具类
     * @type {DateUtils}
     */
    public static get DateUtils(): DateUtils {
        return DateUtils.getInstance();
    }

    /**
     * 数学计算工具类
     * @type {MathUtils}
     */
    public static get MathUtils(): MathUtils {
        return MathUtils.getInstance();
    }

    /**
     * 随机数工具类
     * @type {RandomUtils}
     */
    public static get RandomUtils(): RandomUtils {
        return RandomUtils.getInstance();
    }

    /**
     * 显示对象工具类
     * @type {DisplayUtils}
     */
    public static get DisplayUtils(): DisplayUtils {
        return DisplayUtils.getInstance();
    }

    /*
     * 图片合成数字工具类
     * */
    public static get BitmapNumber(): BitmapNumber {
        return BitmapNumber.getInstance();
    }

    /**
     * 引导工具类
     */
    public static get GuideUtils(): GuideUtils {
        return GuideUtils.getInstance();
    }

    /**
     * 指引管理
     */
    public static get GuideManager(): GuideManager {
        return GuideManager.getInstance();
    }

    /**
     * Stage操作相关工具类
     */
    public static get StageUtils(): StageUtils {
        return StageUtils.getInstance();
    }

    /**
     * Effect工具类
     */
    public static get EffectUtils(): EffectUtils {
        return EffectUtils.getInstance();
    }

    /**
     * 字符串工具类
     */
    public static get StringUtils(): StringUtils {
        return StringUtils.getInstance();
    }

    /**
     * 通过工具类
     */
    public static get CommonUtils(): CommonUtils {
        return CommonUtils.getInstance();
    }

    /**
     * 音乐管理类
     */
    public static get SoundManager(): SoundManager {
        return SoundManager.getInstance();
    }

    
    /**
     * 签到管理类
     */
    public static get DailySignManager(): DailySignManager {
        return DailySignManager.getInstance();
    }

    /**
     * 设置本地数据管理类
     */
    public static get SettingDataManager(): SettingDataManager {
        return SettingDataManager.getInstance();
    }

    /**
     * 设备工具类
     */
    public static get DeviceUtils(): DeviceUtils {
        return DeviceUtils.getInstance();
    }

    /**
     * 引擎扩展类
     */
    public static get EgretExpandUtils(): EgretExpandUtils {
        return EgretExpandUtils.getInstance();
    }

    /**
     * 键盘操作工具类
     */
    public static get KeyboardUtils(): KeyboardUtils {
        return KeyboardUtils.getInstance();
    }

    /**
     * 摇杆操作工具类
     */
    public static get RockerUtils(): RockerUtils {
        return RockerUtils.getInstance();
    }

    /**
     * 震动类
     */
    public static get ShockUtils(): ShockUtils {
        return ShockUtils.getInstance();
    }

    /**
     * 资源加载工具类
     */
    public static get ResourceUtils(): ResourceUtils {
        return ResourceUtils.getInstance();
    }

    /**
     * RenderTextureManager
     */
    public static get RenderTextureManager(): RenderTextureManager {
        return RenderTextureManager.getInstance();
    }

    /**
     * TextFlow
     */
    public static get TextFlowMaker(): TextFlowMaker {
        return TextFlowMaker.getInstance();
    }

    /**
     * 消息通知中心
     */
    private static _notificationCenter: MessageCenter;

    public static get NotificationCenter(): MessageCenter {
        if (App._notificationCenter == null) {
            App._notificationCenter = new MessageCenter(1);
        }
        return App._notificationCenter;
    }


    /**
     * 分帧处理类
     * @returns {any}
     * @constructor
     */
    public static get DelayOptManager(): DelayOptManager {
        return DelayOptManager.getInstance();
    }

    /**
     * 数组工具类
     * @returns {any}
     * @constructor
     */
    public static get ArrayUtils(): ArrayUtils {
        return ArrayUtils.getInstance();
    }

    /**
     * 通用Loading动画
     * @returns {any}
     * @constructor
     */
    public static get EasyLoading(): EasyLoading {
        return EasyLoading.getInstance();
    }

    /**
     * 界面进度条Loading
     * @returns {any}
     * @constructor
     */
    public static get SimpleLoading(): SimpleLoading {
        return SimpleLoading.getInstance();
    }

    /**
     * DragonBones工厂类
     * @returns {any}
     * @constructor
     */
    public static get DragonBonesFactory(): DragonBonesFactory {
        return DragonBonesFactory.getInstance();
    }

    /**
     * StarlingSwf工厂类
     * @returns {StarlingSwfFactory}
     * @constructor
     */
    public static get StarlingSwfFactory(): StarlingSwfFactory {
        return StarlingSwfFactory.getInstance();
    }
 
    /**战斗管理 */
    public static get FightManager():FightManager{
        return FightManager.getInstance();
    }

     /**行动管理 */ 
     public static  get ActionManager():ActionManager
     {
         return ActionManager.getInstance();
     }

    /**玩家信息 */
    public static get PlayerManager():PlayerManager
    {
        return PlayerManager.getInstance(); 
    }

    /**视频播放工具类 */
    public static get VideoUtils():VideoUtils{
        return VideoUtils.getInstance();
    }

    public static get EventMgrHelper():EventMgrHelper{
        return EventMgrHelper.getInstance();
    }

    /**
     * 通信管理类
    */
    public static get WechatManager():WechatManager{
        return WechatManager.getInstance();
    }
    
    public static LoadReourcesSetp:LoadSetp= LoadSetp.FIRST;
    public static PreLoad_GroupName: string = "preload_main";
    public static EnterNextLoad(){
        App.LoadReourcesSetp+=1;
    }

    public static GetLoadResourceGroup(idx:number):Array<string>
    {
        let subGroups:Array<string>=[];
        let preload_conf=PreloadReourceConfig.GetConfig(idx);
        if(preload_conf!=null){
            subGroups = preload_conf.name;
        }
        return subGroups;
    }

    /**
     * 初始化函数
     * @constructor
     */
    public static Init(): void {
        App.GlobalData = RES.getRes("global");                  //全局配置数据
        App.DebugUtils.isOpen(App.GlobalData.IsDebug);          //开启调试
        App.DebugUtils.setThreshold(5);
        App.EgretExpandUtils.init();                            //扩展功能初始化
        
        //实例化ProtoBuf和Socket请求
        App.ProtoConfig = RES.getRes(App.GlobalData.ProtoConfig);
        App.Socket.initServer(App.GlobalData.SocketServer, App.GlobalData.SocketPort, new ByteArrayMsgByProtobuf());
        game.MsgHandlerFact.Build();

        function send(){
            let aa = new game.CSLoginGateHelper();
            aa.Send();
            
        }
        //App.Socket.connect();
        App.MessageCenter.addListener(SocketConst.SOCKET_CONNECT, () => {
            Log.trace("与服务器连接上");
            send();
        }, this);
        App.MessageCenter.addListener(SocketConst.SOCKET_RECONNECT, () => {
            Log.trace("与服务器重新连接上");
        }, this);
        App.MessageCenter.addListener(SocketConst.SOCKET_START_RECONNECT, () => {
            Log.trace("开始与服务器重新连接");
        }, this);
        App.MessageCenter.addListener(SocketConst.SOCKET_CLOSE, () => {
            Log.trace("与服务器断开连接");
        }, this);
        App.MessageCenter.addListener(SocketConst.SOCKET_NOCONNECT, () => {
            Log.trace("服务器连接不上");
        }, this);
    }
}
