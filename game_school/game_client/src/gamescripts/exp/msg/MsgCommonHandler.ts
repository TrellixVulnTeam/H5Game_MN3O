namespace game
{
	export class SCCharacterRevertHandler
	{
		public static HandleMsg(_msg:any):void
		{
			let msg:GeneralMes.SCCharacterRevert = _msg as GeneralMes.SCCharacterRevert
			ClientSCCharacterRevertHandler.HandleMsg(msg);
		}
	}

	export class SCDroppedHumanHintHandler
	{
		public static HandleMsg(_msg:any):void
		{
			let msg:GeneralMes.SCDroppedHumanHint = _msg as GeneralMes.SCDroppedHumanHint
			ClientSCDroppedHumanHintHandler.HandleMsg(msg);
		}
	}

	export class SCCharacterDeleteHandler
	{
		public static HandleMsg(_msg:any):void
		{
			let msg:GeneralMes.SCCharacterDelete = _msg as GeneralMes.SCCharacterDelete
			ClientSCCharacterDeleteHandler.HandleMsg(msg);
		}
	}

	export class SCCharacterCreateHandler
	{
		public static HandleMsg(_msg:any):void
		{
			let msg:GeneralMes.SCCharacterCreate = _msg as GeneralMes.SCCharacterCreate
			ClientSCCharacterCreateHandler.HandleMsg(msg);
		}
	}

	export class SCCharacterLoginHandler
	{
		public static HandleMsg(_msg:any):void
		{
			let msg:GeneralMes.SCCharacterLogin = _msg as GeneralMes.SCCharacterLogin
			ClientSCCharacterLoginHandler.HandleMsg(msg);
		}
	}

	export class SCLoginGateHandler
	{
		public static HandleMsg(_msg:any):void
		{
			let msg:GeneralMes.SCLoginGate = _msg as GeneralMes.SCLoginGate
			ClientSCLoginGateHandler.HandleMsg(msg);
		}
	}


}
