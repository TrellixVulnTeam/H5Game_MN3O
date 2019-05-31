
/**
 * created by sjz on 2018-5-9.
 * 场景背景类
 */
class CCG_SceneBackGround extends egret.DisplayObjectContainer
{
    private mapId: number;
    private miniBg: egret.Bitmap;
    public mapWidth:number;
    public mapHeight:number;

    public constructor() {
        super();
    }

    public init(mapId: number,view:egret.DisplayObjectContainer) {
        this.mapId = mapId;
        var config:BattleConfig=BattleConfig.GetConfig(mapId);
        // var mapData: any = RES.getRes("map_" + mapId + "_data.json");//等待修改
        // this.mapWidth = mapData.width;
        // this.mapHeight = mapData.height;

        this.miniBg = new egret.Bitmap();
        this.miniBg.texture = RES.getRes( config. battle_bg);//等待修改
        this.miniBg.width = 750 ;
        this.miniBg.height = 1334;
    
        this.addChild(this.miniBg);
        view.addChildAt( this, 0 );
    }

}