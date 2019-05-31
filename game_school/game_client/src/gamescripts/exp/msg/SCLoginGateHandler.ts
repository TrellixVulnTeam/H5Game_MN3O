namespace game

{

	export class ClientSCLoginGateHandler

	{

		public static HandleMsg( msg:GeneralMes.SCLoginGate ):void

		{

			Log.trace("msgtest:"+msg.result);

		}

	}

}