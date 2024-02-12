using ChessMessages;

namespace BackEndLogic
{
    public class UserHandler : SignedUsersDB
    {
        public static UserHandler getInstance()
        {
            if(userHandler == null)
            {
                userHandler = new UserHandler();
            }
            return userHandler;
        }


        public void signup(SingupMsg signupMsg)
        {
            Signup signup = new Signup { _id = signupMsg.Name, password = signupMsg.Password};
            base.signup(signup);
        }

        private UserHandler() : base(dbConnectionString, dbName) 
        {
            
        }

        

        private static UserHandler userHandler; // the only instance of this class 
        const string dbConnectionString = "mongodb://localhost:27017";
        const string dbName = "chess_db";
    }
}
