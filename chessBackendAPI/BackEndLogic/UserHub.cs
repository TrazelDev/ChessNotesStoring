using ChessMessages;
using Microsoft.AspNetCore.SignalR;

namespace BackEndLogic
{
    public class UserHub : Hub
    {
        public async Task<bool> signup(byte[] msg)
        {
            SingupMsg signupMsg = SingupMsg.Parser.ParseFrom(msg);
            try
            {
                UserHandler.getInstance().signup(signupMsg);
            }
            // if there is a catch that means that It failed to write into the database
            // and there is already username like this in the system
            catch (Exception e) 
            {
                return false;
            }

            return true;
        }

        public async Task<bool> checkRightPassword(byte[] msg)
        {


            return true;
        }
    }
}