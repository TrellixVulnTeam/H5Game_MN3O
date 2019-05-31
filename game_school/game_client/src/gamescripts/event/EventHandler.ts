
interface _HandleEvent
{
    /**
     * @param ev 事件定义
     * @returns {} 无.
     */
    (ev:any,le:LogicEvent):void;
}
/**
 * @author sjz
 * @time 2018-8-13 5:21
 * @description 事件管理器
 */
class EventHandler{

	private mhandler:_HandleEvent = null;
	public RegisterEvent( ev:EventDef ):void
	{
		App.EventMgrHelper.RegisterEventHandler( ev, this );
	}
	
	public UnRegisterEvent( ev:EventDef ):void
	{
		App.EventMgrHelper.UnRegisterEventHandler( ev, this );
	}
	
	public HandleEvent( ev:EventDef, le:LogicEvent ):void
	{
		if ( this.mhandler != null )
		{
			this.mhandler( ev, le );
		}
	}

	public set Handler(value:any){
		this.mhandler=value;
	}
}