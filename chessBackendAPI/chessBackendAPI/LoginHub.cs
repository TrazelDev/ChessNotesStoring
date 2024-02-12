using chessBackendAPI;
using ChessMessages;
using Google.Protobuf;
using Microsoft.AspNetCore.SignalR;
using Microsoft.AspNetCore.SignalR.Client;
using System.Reflection;
using System.Threading.Tasks;


namespace AspNetCoreSignalR_React.Server
{

    
    public class LoginHub : Hub
    {
        public async Task<bool> signup(byte[] signupMsgBytes)
        {
            using (StreamWriter writer = new StreamWriter("file.txt"))
            {
                writer.WriteLine("value");
            }

            SingupMsg loginMsg = SingupMsg.Parser.ParseFrom(signupMsgBytes);

            // bool isValid = !string.IsNullOrWhiteSpace(loginMsg.Name);
            // Create a LoginMsg instance
            /*var loginMsg = new SingupMsg
            {
                Id = 1,
                Name = "hi world"
            };

            byte[] loginMsgBytes = loginMsg.ToByteArray();*/ 

            ServerCommunication serverCommunication = await ServerCommunication.getInstance();
            if(await serverCommunication.sendMsg<bool>(signupMsgBytes, SignupFunction))
            {
                await login(signupMsgBytes);
                return true;
            }

            return false;
        }
        
        public async Task<bool> login(byte[] loginMsgBytes)
        {
            LoginMsg loginMsg = LoginMsg.Parser.ParseFrom(loginMsgBytes);
            
            return true;
        }

        public static readonly string SignupFunction = "signup";
    }
}
