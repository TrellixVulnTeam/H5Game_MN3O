namespace game
{
	export class MsgHandlerFact
	{
		public static Build():void
		{
			% for cls in class_list:
			App.MessageCenter.addListener(MsgDef.msgid_${cls}.toString(), ${cls}Handler.HandleMsg, this );
			% endfor
		}
	}
}