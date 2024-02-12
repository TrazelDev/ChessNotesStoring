using DnsClient;
using MongoDB.Bson;
using MongoDB.Driver;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace BackEndLogic
{
    
    public abstract class SignedUsersDB
    {
        public SignedUsersDB(string connectionString, string databaseName)
        {
            MongoClient client = new MongoClient(connectionString);
            IMongoDatabase database = client.GetDatabase(databaseName);
            m_signups = database.GetCollection<Signup>("signup");
        }

        public List<Signup> getAllUsers()
        {
            return m_signups.Find(Builders<Signup>.Filter.Empty).ToList();
        }
        
        public string getPassword(string userName)
        {
            FilterDefinition<Signup> filter = Builders<Signup>.Filter.Eq("_id", ObjectId.Parse(userName));
            return m_signups.Find(filter).FirstOrDefault().password;
        }

        public void DeleteAllLogins()
        {
            var deleteFilter = Builders<Signup>.Filter.Empty;
            m_signups.DeleteMany(deleteFilter);

#if DEBUG
            logAllUser();
#endif
        }

        protected void signup(Signup newSignup)
        {
            m_signups.InsertOne(newSignup);
#if DEBUG
            logAllUser();
#endif
        }
#if DEBUG
        private void logAllUser()
        {
            List<Signup> signups = m_signups.Find(Builders<Signup>.Filter.Empty).ToList();
            string msg = "";
            for (int i = 0; i < signups.Count; i++)
            {
                msg += signups[i]._id + "," + signups[i].password + "\n";
            }
            using (StreamWriter writer = new StreamWriter("log.txt"))
            {
                writer.WriteLine(msg);
            }
        }
#endif
        
        private readonly IMongoCollection<Signup> m_signups;
    }
}
