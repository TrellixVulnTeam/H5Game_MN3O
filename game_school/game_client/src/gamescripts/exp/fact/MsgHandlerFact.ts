namespace game
{
	export class MsgHandlerFact
	{
		public static Build():void
		{
			App.MessageCenter.addListener(MsgDef.msgid_SCCharacterRevert.toString(), SCCharacterRevertHandler.HandleMsg, this );
			App.MessageCenter.addListener(MsgDef.msgid_SCDroppedHumanHint.toString(), SCDroppedHumanHintHandler.HandleMsg, this );
			App.MessageCenter.addListener(MsgDef.msgid_SCCharacterDelete.toString(), SCCharacterDeleteHandler.HandleMsg, this );
			App.MessageCenter.addListener(MsgDef.msgid_SCCharacterCreate.toString(), SCCharacterCreateHandler.HandleMsg, this );
			App.MessageCenter.addListener(MsgDef.msgid_SCCharacterLogin.toString(), SCCharacterLoginHandler.HandleMsg, this );
			App.MessageCenter.addListener(MsgDef.msgid_SCLoginGate.toString(), SCLoginGateHandler.HandleMsg, this );
		}
	}
}